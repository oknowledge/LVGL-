#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"
#include <stdio.h>
 

#define DHT11_Data(a)    (a?\
                        HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_SET):\
                        HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_RESET))
#define Check_DHT11()  	(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin))
 
void DHT11_PIN_OUT(void);
void DHT11_PIN_IN(void);
void DHT11_Rst(void);//函数声明
void DHT11_Show_Data(DHT11_TYPE *Dht11Type);
uint8_t DHT11_Check(void);
//void Control(void);
uint8_t DHT11_Init(void);
uint8_t DHT11_Read_Bit(void);
#endif

