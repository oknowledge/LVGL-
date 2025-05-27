#include "dht11.h"
DHT11_TYPE Dht11Type;
#define Delay_T  100

 void Delay_us(uint32_t t)
{
	uint8_t i = 0;
	 while(t--)
	 {
		 i=40;
		 while(i--);
	 }
 }

void DHT11_PIN_OUT(void)//端口配置为输出
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DHT11_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = DHT11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void DHT11_PIN_IN(void)//端口配置为输入
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DHT11_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = DHT11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void DHT11_Rst(void)//DHT11起始信号
{
	DHT11_PIN_OUT();	//设置DHT11引脚为通用输出模式
	DHT11_Data(0);			//拉低DAT总线
	HAL_Delay(20);		//拉低至少18ms
	DHT11_Data(1);			//拉高DAT总线
	Delay_us(30);		//主机拉高20~40us
}

uint8_t DHT11_Check(void)//等待DHT11回应，返回1 未检测到DHT11，返回0３晒
{
	uint8_t retry = 0;
	DHT11_PIN_IN();							//设置DHT11引脚为输入模式
	while( !Check_DHT11() && (retry<Delay_T) ) 	//DHT11会拉低40~80us
	{
		retry++;
		Delay_us(1);  
		
	}
	if( retry >= 100 ) 	return 1; 			//返回1，表示DHT11没有正常响应，或响应失败
	else retry = 0;
	while(Check_DHT11() && (retry<Delay_T) )		//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		Delay_us(1);
	}
	if( retry >= Delay_T ) 	return 1; 		//返回1，表示DHT11没有正常响应，或响应失败
	return 0; 								//返回0，表示DHT11正常响应
}

uint8_t DHT11_Init(void)
{
	
	  DHT11_PIN_OUT();
	  DHT11_Data(1);
	  DHT11_Rst();					//起始信号的检测
	  return DHT11_Check();                         //检测DHT11是否有响应
}

uint8_t DHT11_Read_Bit(void)
{
	uint8_t retry = 0;
	while( Check_DHT11() && (retry<Delay_T) )		//等待变为低电平
	{
		retry++;
		Delay_us(1);
	}
	retry = 0;                            
	while( !Check_DHT11() && (retry<Delay_T) )	//等待变为高电平，同时测量高电平时间
	{
		retry++;
		Delay_us(1);											 
	}
	Delay_us(40); 							//等待40us
	if( Check_DHT11() )	return 1;  			//读取该位为1，则返回1
	else 				return 0;          //否则返回0
}

uint8_t DHT11_Read_Byte(void)
{
	uint8_t i = 0,data = 0;
	for(i = 0; i < 8; i++)
	{
		data <<= 1;
		data |= DHT11_Read_Bit();  //一位一位读取
	}
	return data;	       				 //返回读取到数据
}


void DHT11_Show_Data(DHT11_TYPE *Dht11Type)
{
	DHT11_Rst();
	if(DHT11_Check() == 0)					//正常响应后
	{
		
		 Dht11Type->humInt   = DHT11_Read_Byte();
		 Dht11Type->humDeci  = DHT11_Read_Byte();
		 Dht11Type->tempInt  = DHT11_Read_Byte();
		 Dht11Type->tempDeci = DHT11_Read_Byte();
		 Dht11Type->check    = DHT11_Read_Byte();
		if( (Dht11Type->humInt + Dht11Type->humDeci + Dht11Type->tempInt + Dht11Type->tempDeci) == Dht11Type->check) //检验数据是否接收正确
		{
			Dht11Type->humidity= Dht11Type->humInt+ Dht11Type->humDeci / 256.0;   //存储湿度值，整数和小数
			Dht11Type->temperture = Dht11Type->tempInt+Dht11Type->tempDeci/ 256.0; //存储温度值，整数和小数
			

		}
	}

    //打印当前温度和湿度值
//	  printf("当前温度为:%.2f,当前湿度为:.2%f\r\n",Dht11Type->temperture,Dht11Type->humidity);
//}
//void Control(void)
//{

//        if(Dht11Type.humidity>Dht11Type.setHum||Dht11Type.temperture>Dht11Type.setTemp)
//        {
//              HAL_GPIO_WritePin(GPIOC, LED_Pin, 0);
//        }
//        else
//            {
//              HAL_GPIO_WritePin(GPIOC, LED_Pin,1);
//        }
//}

}
