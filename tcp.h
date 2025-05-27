#ifndef __TCP_H
#define __TCP_H 			   
#include "main.h"


/*
*以下参数需要用户自行修改才能测试用过
*/

#define User_ESP8266_SSID     "501"          //wifi名
#define User_ESP8266_PWD      "27402730"      //wifi密码

#define User_ESP8266_TCPServer_IP     "api.seniverse.com"     //服务器IP
#define User_ESP8266_TCPServer_PORT   "80"      //服务器端口号


extern volatile uint8_t TcpClosedFlag;  //连接状态标志
uint8_t ESP8266_ReqRes_DataParsing(char *reqRes, char *keywords, char *result);

typedef struct  //数据帧结构体
{
    char city[10];
    char text[10];
    char temperature[5];
    char date[10];
}Weather_Result;
void ESP8266_STA_TCPClient_Test(void);

#endif
