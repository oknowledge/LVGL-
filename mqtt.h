#ifndef __MQTT_H
#define __MQTT_H 			   
#include "main.h"


/*
*���²�����Ҫ�û������޸Ĳ��ܲ����ù�
*/


#define User_ESP8266_SSID     "501"    //wifi��
#define User_ESP8266_PWD      "27402730"      //wifi����

#define User_ESP8266_client_id    "k2719oFu78O.MK54|securemode=2\\,signmethod=hmacsha256\\,timestamp=1747632693154|"    //MQTTclientID ���ڱ�־client���  �256�ֽ�
#define User_ESP8266_username     "MK54&k2719oFu78O"						//���ڵ�¼ MQTT ������ �� username, � 64 �ֽ�	
#define User_ESP8266_password			"3bccf3f2d0c34436da1b4c901432880fb85b6485bf04837ea474adb50dd4ee36"          //���ڵ�¼ MQTT ������ �� password, � 64 �ֽ�
#define User_ESP8266_MQTTServer_IP     "iot-06z00c7q37g8kbb.mqtt.iothub.aliyuncs.com"     //MQTT���ط�����IP
#define User_ESP8266_MQTTServer_PORT   1883     //�������˿ں�
#define User_ESP8266_MQTTServer_Topic  "{\"id\":\"MK54\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"   //����MQTT����
 
void ESP8266_STA_MQTTClient_Test(void);
 
#endif
