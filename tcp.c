#include "tcp.h"
#include "usart.h"
#include "esp8266.h"
 
#include "stdio.h"
#include "string.h"
#include "main.h"

volatile uint8_t TcpClosedFlag = 0;
Weather_Result WX_Res;
 
 
void ESP8266_STA_TCPClient_Test(void)
{
    //uint8_t res;
	
    char str[300]={0};
    ESP8266_AT_Test();
		printf("正在配置ESP8266\r\n");
    ESP8266_Net_Mode_Choose(STA);
    while(!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD));
    ESP8266_Enable_MultipleId ( DISABLE );
    while(!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0));
    while(!ESP8266_UnvarnishSend());
		printf("\r\n配置完成");
		   sprintf(str,"GET https://api.seniverse.com/v3/weather/now.json?key=So_zet-BfPn_Q5QIP&location=wuxi&language=zh-Hans&unit=c");
    ESP8266_SendString ( ENABLE, str, strlen(str), Single_ID_0 );
		    ESP8266_ReqRes_DataParsing(ESP8266_Fram_Record_Struct .Data_RX_BUF, "name",WX_Res.city);
        ESP8266_ReqRes_DataParsing(ESP8266_Fram_Record_Struct .Data_RX_BUF, "text",WX_Res.text);
        ESP8266_ReqRes_DataParsing(ESP8266_Fram_Record_Struct .Data_RX_BUF, "temperature",WX_Res.temperature);
        ESP8266_ReqRes_DataParsing(ESP8266_Fram_Record_Struct .Data_RX_BUF, "last_update",WX_Res.date);
        printf("%s,%s,%s,%s",WX_Res.city,WX_Res.text,WX_Res.temperature,WX_Res.date);
//    while ( 1 )
//    {       
//			  sprintf (str,"深圳市安信可科技有限公司" );//格式化发送字符串到TCP服务器
//        ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );
//        HAL_Delay(3000);
//        if(TcpClosedFlag) //判断是否失去连接
//        {
//            ESP8266_ExitUnvarnishSend(); //退出透传模式
//            do
//            {
//                res = ESP8266_Get_LinkStatus();     //获取连接状态
//            }   
//            while(!res);

//            if(res == 4)                     //确认失去连接，重连
//            {
//                
//                
//                while (!ESP8266_JoinAP(User_ESP8266_SSID, User_ESP8266_PWD ) );
//                while (!ESP8266_Link_Server(enumTCP, User_ESP8266_TCPServer_IP, User_ESP8266_TCPServer_PORT, Single_ID_0 ) );        
//            } 
//            while(!ESP8266_UnvarnishSend());                    
//        }
    
}
uint8_t ESP8266_ReqRes_DataParsing(char *reqRes, char *keywords, char *result)
{
    char *p1 = NULL;
    char *p2 = NULL;
    
    if(strstr(reqRes, "last_update"))   //判断请求响应的数据是否正确
    {
        p1 = strstr(reqRes, keywords);  //查找关键词
        if(p1)
        {
            p1 += strlen(keywords) + 3;
            p2 = strstr(p1, "\"");      //查找末端的 " 
            strncpy(result, p1, p2 - p1); //拷贝数据
            return 0;
        }
    }
    return 1;

}
