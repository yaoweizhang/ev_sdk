/*
 * @Author: gang.fan
 * @Date: 2022-09-13 14:26:51
 * @LastEditTime: 2022-09-13 18:29:25
 * @LastEditors: gang.fan
 * @Description: 
 * Copyright (c) 2022 Extreme Vision Co., Ltd.
 */
#ifndef __LICENSE_H__
#define __LICENSE_H__

#include "define.h"

//算法基础模型鉴权 0 表示成功,非0表示失败
EVResult CheckModelAuth();

//算法SDK鉴权 0 表示成功,非0表示失败
EVResult CheckAlgoSdkAuth();

//////////////////////////////////////////////////
//以下是VAS中心授权相关
/////////////////////////////////////////////////

//设置授权参数
EVResult SetCenterAuthParams(const char* szParam, AuthMsgCallback pAuthMsgCB, void* pContext);

//更新运行路数或者QPS值,同时开始授权 0 表示成功,非0表示失败
EVResult UpdateAuth(int nCount);

#endif // __LICENSE_H__