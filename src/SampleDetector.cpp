#include <sys/stat.h>
#include <fstream>
#include <glog/logging.h>

#include "SampleDetector.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "ji_utils.h"
#include "./logging.h"
#define INPUT_NAME "images"
#define OUTPUT_NAME "output"
using namespace nvinfer1;


static bool ifFileExists(const char *FileName)
{
    struct stat my_stat;
    return (stat(FileName, &my_stat) == 0);
}

SampleDetector::SampleDetector()
{
    
}

void SampleDetector::loadOnnx(const std::string strModelName)
{
    Logger gLogger;
    //根据tensorrt pipeline 构建网络
    IBuilder* builder = createInferBuilder(gLogger);
    builder->setMaxBatchSize(1);
    //builder->setFp16Mode(true);
    const auto explicitBatch = 1U << static_cast<uint32_t>(NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);  
    INetworkDefinition* network = builder->createNetworkV2(explicitBatch);
    nvonnxparser::IParser* parser = nvonnxparser::createParser(*network, gLogger);
    parser->parseFromFile(strModelName.c_str(), static_cast<int>(ILogger::Severity::kWARNING));
    IBuilderConfig* config = builder->createBuilderConfig();
    config->setMaxWorkspaceSize(1ULL << 30);    
    config->setFlag(BuilderFlag::kFP16);
    //config->setFlag(BuilderFlag::kINT8);
    m_CudaEngine = builder->buildEngineWithConfig(*network, *config);    

    std::string strTrtName = strModelName;
    size_t sep_pos = strTrtName.find_last_of(".");
    strTrtName = strTrtName.substr(0, sep_pos) + ".trt";
    IHostMemory *gieModelStream = m_CudaEngine->serialize();
    std::string serialize_str;
    std::ofstream serialize_output_stream;
    serialize_str.resize(gieModelStream->size());   
    memcpy((void*)serialize_str.data(),gieModelStream->data(),gieModelStream->size());
    serialize_output_stream.open(strTrtName.c_str());
    serialize_output_stream<<serialize_str;
    serialize_output_stream.close();
    m_CudaContext = m_CudaEngine->createExecutionContext();
    parser->destroy();
    network->destroy();
    config->destroy();
    builder->destroy();
}

void SampleDetector::loadTrt(const std::string strName)
{
    Logger gLogger;
    IRuntime* runtime = createInferRuntime(gLogger);    
    std::ifstream fin(strName);
    std::string cached_engine = "";
    while (fin.peek() != EOF)
    { 
        std::stringstream buffer;
        buffer << fin.rdbuf();
        cached_engine.append(buffer.str());
    }
    fin.close();
    m_CudaEngine = runtime->deserializeCudaEngine(cached_engine.data(), cached_engine.size(), nullptr);
    m_CudaContext = m_CudaEngine->createExecutionContext();
    runtime->destroy();
}

bool SampleDetector::Init(const std::string& strModelName, float thresh)
{
    mThresh = thresh;
    std::string strTrtName = strModelName;
    size_t sep_pos = strTrtName.find_last_of(".");
    strTrtName = strTrtName.substr(0, sep_pos) + ".trt";
    if(ifFileExists(strTrtName.c_str()))
    {        
        SDKLOG(INFO) << "Load model path: " <<strTrtName;
        loadTrt(strTrtName);
    }
    else
    {
        SDKLOG(INFO) << "Load model path: " <<strModelName;
        loadOnnx(strModelName);
    }    
    // 分配输入输出的空间,DEVICE侧和HOST侧
    m_iInputIndex = m_CudaEngine->getBindingIndex(INPUT_NAME);
    m_iOutputIndex = m_CudaEngine->getBindingIndex(OUTPUT_NAME);     

    Dims dims_i = m_CudaEngine->getBindingDimensions(m_iInputIndex);
    SDKLOG(INFO) << "input dims " << dims_i.d[0] << " " << dims_i.d[1] << " " << dims_i.d[2] << " " << dims_i.d[3];
    int size = dims_i.d[0] * dims_i.d[1] * dims_i.d[2] * dims_i.d[3];
    
    m_InputSize = cv::Size(dims_i.d[3], dims_i.d[2]);

    cudaMalloc(&m_ArrayDevMemory[m_iInputIndex], size * sizeof(float));
    m_ArrayHostMemory[m_iInputIndex] = malloc(size * sizeof(float));
    //方便NHWC到NCHW的预处理
    m_InputWrappers.emplace_back(dims_i.d[2], dims_i.d[3], CV_32FC1, m_ArrayHostMemory[m_iInputIndex]);
    m_InputWrappers.emplace_back(dims_i.d[2], dims_i.d[3], CV_32FC1, m_ArrayHostMemory[m_iInputIndex] + sizeof(float) * dims_i.d[2] * dims_i.d[3] );
    m_InputWrappers.emplace_back(dims_i.d[2], dims_i.d[3], CV_32FC1, m_ArrayHostMemory[m_iInputIndex] + 2 * sizeof(float) * dims_i.d[2] * dims_i.d[3]);
    m_ArraySize[m_iInputIndex] = size *sizeof(float);
    dims_i = m_CudaEngine->getBindingDimensions(m_iOutputIndex);
    SDKLOG(INFO) << "output dims "<< dims_i.nbDims << " " << dims_i.d[0] << " " << dims_i.d[1] << " " << dims_i.d[2];    
    size = dims_i.d[0] * dims_i.d[1] * dims_i.d[2];
    m_iClassNums = dims_i.d[2] - 5;
    m_iBoxNums = dims_i.d[1];
    cudaMalloc(&m_ArrayDevMemory[m_iOutputIndex], size * sizeof(float));
    m_ArrayHostMemory[m_iOutputIndex] = malloc( size * sizeof(float));
    m_ArraySize[m_iOutputIndex] = size *sizeof(float);
    cudaStreamCreate(&m_CudaStream);    
    m_bUninit = false;
}

bool SampleDetector::UnInit()
{
    if(m_bUninit == true)
    {
        return false;
    }
    for(auto &p: m_ArrayDevMemory)
    {      
        cudaFree(p);
        p = nullptr;            
    }        
    for(auto &p: m_ArrayHostMemory)
    {        
        free(p);
        p = nullptr;        
    }        
    cudaStreamDestroy(m_CudaStream);
    m_CudaContext->destroy();
    m_CudaEngine->destroy();
    m_bUninit = true;
}

SampleDetector::~SampleDetector()
{
    UnInit();   
}

bool SampleDetector::ProcessImage(const cv::Mat& img, std::vector<BoxInfo>& DetObjs, float thresh, bool in)
{
    mThresh = thresh;
    DetObjs.clear();  
    //float r = std::min(m_InputSize.width / static_cast<float>(img.rows), m_InputSize.width / static_cast<float>(img.cols));
    float r = std::min(m_InputSize.height / static_cast<float>(img.rows), m_InputSize.width / static_cast<float>(img.cols));
    cv::Size new_size = cv::Size{std::min(int(img.cols * r),m_InputSize.width), std::min(int(img.rows * r), m_InputSize.height)};    
    int dw = int((m_InputSize.width - new_size.width)/2.0);
    int dh = int((m_InputSize.height - new_size.height)/2.0);
    int stride = 32;
    dw -= (dw % stride);
    dh -= (dh % stride);
    cv::Mat tmp_resized;    
    
    cv::resize(img, tmp_resized, new_size);
    cv::cvtColor(tmp_resized, tmp_resized, cv::COLOR_BGR2RGB);
    if(m_Resized.empty())
    {
        m_Resized = cv::Mat( cv::Size(m_InputSize.width, m_InputSize.height), CV_8UC3, cv::Scalar(114, 114, 114));    
    }
    
    tmp_resized.copyTo(m_Resized(cv::Rect{0+dw, 0+dh, tmp_resized.cols, tmp_resized.rows}));
    
    m_Resized.convertTo(m_Normalized, CV_32FC3, 1/255.);
    m_Resized = cv::Mat();
    cv::split(m_Normalized, m_InputWrappers); 

    auto ret = cudaMemcpyAsync(m_ArrayDevMemory[m_iInputIndex], m_ArrayHostMemory[m_iInputIndex], m_ArraySize[m_iInputIndex], cudaMemcpyHostToDevice, m_CudaStream);
    auto ret1 = m_CudaContext->enqueueV2(m_ArrayDevMemory, m_CudaStream, nullptr);    
    ret = cudaMemcpyAsync(m_ArrayHostMemory[m_iOutputIndex], m_ArrayDevMemory[m_iOutputIndex], m_ArraySize[m_iOutputIndex], cudaMemcpyDeviceToHost, m_CudaStream);
    ret = cudaStreamSynchronize(m_CudaStream);    
    float scale = std::min(m_InputSize.width / (img.cols * 1.0), m_InputSize.height / (img.rows * 1.0));
    decode_outputs((float*)m_ArrayHostMemory[m_iOutputIndex], mThresh, DetObjs, scale, img.cols, img.rows, dw, dh);
    runNms(DetObjs, in ? 0.3: 0.45, in);
}




void SampleDetector::runNms(std::vector<BoxInfo>& objects, float thresh, bool in)   //原本的
{
    auto cmp_lammda = [](const BoxInfo& b1, const BoxInfo& b2){return b1.score < b2.score;};
    std::sort(objects.begin(), objects.end(), cmp_lammda);
    for(int i = 0; i < objects.size(); ++i)
    {
        if( objects[i].score < 0.1 )
        {
            continue;
        }
        for(int j = i + 1; j < objects.size(); ++j)
        {
            if( objects[i].label != objects[j].label) {
                continue;
            }
            cv::Rect rect1 = cv::Rect{int(objects[i].x1), int(objects[i].y1), int(objects[i].x2 - objects[i].x1), int(objects[i].y2 - objects[i].y1)};
            cv::Rect rect2 = cv::Rect{int(objects[j].x1), int(objects[j].y1), int(objects[j].x2 - objects[i].x1), int(objects[j].y2 - objects[j].y1)};
            if(IOU(rect1, rect2) > thresh)   
            {
                objects[i].score = 0.f;
            }
        }
    }
    auto iter = objects.begin();
    while( iter != objects.end() )
    {
        if(iter->score < 0.1)
        {
            iter = objects.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}



void SampleDetector::decode_outputs(float* prob, float thresh, std::vector<BoxInfo>& objects, float scale, const int img_w, const int img_h, int dw, int dh) 
{    
    std::vector<BoxInfo> proposals;
    for(int i = 0; i < m_iBoxNums; ++i)
    {
        int index = i * (m_iClassNums + 5);            
        if(prob[index + 4] > mThresh)
        {            
            
            float x = prob[index] - dw;
            float y = prob[index + 1] - dh;
            float w = prob[index + 2];
            float h = prob[index + 3];            
            if (x <=0 || y <=0) {
                    continue;
            }
            x/=scale;
            y/=scale;
            w/=scale;
            h/=scale;
            float* max_cls_pos = std::max_element(prob + index + 5, prob + index + 5 + m_iClassNums);           
            if((*max_cls_pos) * prob[index+4] > mThresh)
            {
                
                cv::Rect box{int(x- w / 2), int(y - h / 2), int(w), int(h)};
                box = box & cv::Rect(0, 0, img_w-1, img_h-1);
                if( box.area() > 0)
                {
                    BoxInfo box_info = { float(box.x), float(box.y), float(box.x + box.width), float(box.y + box.height), (*max_cls_pos) * prob[index+4], max_cls_pos - (prob + index + 5)};
                    objects.push_back(box_info);
                }
            }
        }
    }    
}
