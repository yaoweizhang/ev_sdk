/*
 * @Author: gang.fan
 * @Date: 2022-09-14 08:36:04
 * @LastEditTime: 2022-09-14 09:15:48
 * @LastEditors: gang.fan
 * @Description: 
 * Copyright (c) 2022 Extreme Vision Co., Ltd.
 */
#include "license.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <glog/logging.h>

EVResult authMsgCallbackFunction(const char* szMsgType, const char* szData, void* pContext)
{
	LOG(INFO) << "message callback szMsgType " << szMsgType << " szData " << szData;
    return 0;
}

static void signal_handle(const char* data, int size)
{
	std::ofstream fs("core_dump.log", std::ios::app);
	std::string str = std::string(data, size);

	fs << str;
	LOG(ERROR) << str;

	fs.close();
}

//"rtmp://192.168.2.228:1935/live/80432"
// rtmp://192.168.58.115:1935/echostream/1234  rtsp://admin:Hyc19950423@192.168.1.217:554/h264/ch1/main/av_stream
int main()
{
	google::InitGoogleLogging("licenseAuth");
	FLAGS_minloglevel = google::GLOG_INFO;      
	FLAGS_stderrthreshold = google::FATAL;
    
    FLAGS_logtostderr = false; 
    
    FLAGS_alsologtostderr = true;   
    FLAGS_colorlogtostderr = true;  
    FLAGS_log_prefix = true;  
    FLAGS_logbufsecs = 0;  
    FLAGS_max_log_size = 10;  
    FLAGS_stop_logging_if_full_disk = true;   

	google::SetLogDestination(google::GLOG_INFO /*设置输出到日志的打印级别*/, "dump.log");

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&signal_handle);

    //基础模型授权
    EVResult ret = CheckModelAuth();
    if(ret!=0) {
        LOG(ERROR) << "CheckModelAuth failed,and ret is " << ret ;
    } else {
        LOG(INFO) << "CheckModelAuth sucessfully! " ;
    }

    //算法SDK授权
    ret = CheckAlgoSdkAuth();
    if(ret!=0) {
        LOG(ERROR) << "CheckAlgoSdkAuth failed,and ret is " << ret ;
    } else {
        LOG(INFO) << "CheckAlgoSdkAuth sucessfully! " ;
    }

    //中心授权
    const char* jsonVal= 
	"{\"ip\":\"192.168.2.19\",  \"uuid\":\"ecffc532-f17a-4178-9cc9-00b78ec99def\", \"algoId\":\"9709\",  \"mode\":\"qps\",  \"port\":4001,   \"timeout\":134,   \"interval\":5}";  //json对象

	SetCenterAuthParams(jsonVal, authMsgCallbackFunction, nullptr);
	ret = UpdateAuth(5);
    LOG(INFO) << "UpdateAuth ret " << ret ;
    std::this_thread::sleep_for(std::chrono::seconds(10000));
 
	google::ShutdownGoogleLogging();
}