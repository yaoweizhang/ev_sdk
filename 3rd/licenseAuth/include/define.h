/*
 * @Author: gang.fan
 * @Date: 2022-09-13 14:27:45
 * @LastEditTime: 2022-09-14 09:03:44
 * @LastEditors: gang.fan
 * @Description: 
 * Copyright (c) 2022 Extreme Vision Co., Ltd.
 */
#ifndef __DEFINE_H__
#define __DEFINE_H__


//错误码定义
#define EV_AUTH_RET_SUCCESS          (0)             // 成功
#define EV_AUTH_RET_ERROR            (2000)          // 通用错误
#define EV_AUTH_RET_UNCONNECTED     (2001)           // 连接中心授权服务器失败
#define EV_AUTH_RET_UNAUTHORIZED    (2002)           // 未授权
#define EV_AUTH_RET_NETWORK_ERROR   (2003)           // 网络错误，包括网络无法连接、超时等网络问题


//回调类型定义
#define EV_AUTH_CB_AUTHORIZED      "authorized"
#define EV_AUTH_CB_UNAUTHORIZED    "unauthorized"
#define EV_AUTH_CB_NETWORK_ERROR   "network error"

typedef  int  EVResult;


#define  VERSION    "v1.1.0"
#define EV_MESSAGE_MAXLEN   (4096)
#define EV_ID_MAXLEN        (1024)


#define HTTP_CODE_SUCCESS             (200)
#define HTTP_CODE_PARAM_ERROR         (400)
#define HTTP_CODE_PERMISSION_ERROR    (403)
#define HTTP_CODE_TIME_ERROR          (501)
#define HTTP_CODE_LIMIT_OUT           (502)
#define HTTP_CODE_EXPIRED             (503)
#define HTTP_CODE_VERIFY              (504)
#define HTTP_CODE_NETWORK_ERROR       (510)


#define EV_AUTH_RET_PARAM_ERROR         HTTP_CODE_PARAM_ERROR
#define EV_AUTH_RET_PERMISSION_ERROR    HTTP_CODE_PERMISSION_ERROR
#define EV_AUTH_RET_TIME_ERROR          HTTP_CODE_TIME_ERROR
#define EV_AUTH_RET_EXPIRED             HTTP_CODE_EXPIRED
#define EV_AUTH_RET_VERIFY              HTTP_CODE_VERIFY
#define EV_AUTH_RET_LIMIT_OUT           HTTP_CODE_LIMIT_OUT


// 503	过期	跨0点后,有些算法会到期, 授权校验接口会返回过期
// 504	重新授权	跨0点后,一些算法的路数会被扣掉, 每天0点后需要重新请求授权进行资源申请, 如果未申请, 心跳接口会返回重新授权,防止运行超限
// 502	超限	超过允许路数或者QPS限制是返回
// 501	时间不同步	当请求vas服务器时间和中心授权服务器时间相差30分钟以上,认为服务器时间机制有问题,心跳不通过, 授权校验也不通过
// 200	通过	
// 999	系统错误	
// 400	参数异常	
// 403	无权限访问

#define VERIFY_INTERVAL   10

typedef EVResult (*AuthMsgCallback)(const char* szMsgType, const char* szData, void* pContext);

#endif // __DEFINE_H__