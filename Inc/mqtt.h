#ifndef __MQTT_H
#define __MQTT_H 			   
#include "main.h"


/*
*以下参数需要用户自行修改才能测试用过
*/


#define User_ESP8266_SSID     "501"    //wifi名
#define User_ESP8266_PWD      "27402730"      //wifi密码

#define User_ESP8266_client_id    "k2719oFu78O.MK54|securemode=2\\,signmethod=hmacsha256\\,timestamp=1747632693154|"    //MQTTclientID 用于标志client身份  最长256字节
#define User_ESP8266_username     "MK54&k2719oFu78O"						//用于登录 MQTT 服务器 的 username, 最长 64 字节	
#define User_ESP8266_password			"3bccf3f2d0c34436da1b4c901432880fb85b6485bf04837ea474adb50dd4ee36"          //用于登录 MQTT 服务器 的 password, 最长 64 字节
#define User_ESP8266_MQTTServer_IP     "iot-06z00c7q37g8kbb.mqtt.iothub.aliyuncs.com"     //MQTT本地服务器IP
#define User_ESP8266_MQTTServer_PORT   1883     //服务器端口号
#define User_ESP8266_MQTTServer_Topic  "{\"id\":\"MK54\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"   //订阅MQTT主题
 
void ESP8266_STA_MQTTClient_Test(void);
 
#endif
