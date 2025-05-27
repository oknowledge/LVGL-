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

void DHT11_PIN_OUT(void)//�˿�����Ϊ���
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

void DHT11_PIN_IN(void)//�˿�����Ϊ����
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

void DHT11_Rst(void)//DHT11��ʼ�ź�
{
	DHT11_PIN_OUT();	//����DHT11����Ϊͨ�����ģʽ
	DHT11_Data(0);			//����DAT����
	HAL_Delay(20);		//��������18ms
	DHT11_Data(1);			//����DAT����
	Delay_us(30);		//��������20~40us
}

uint8_t DHT11_Check(void)//�ȴ�DHT11��Ӧ������1 δ��⵽DHT11������0��ɹ��
{
	uint8_t retry = 0;
	DHT11_PIN_IN();							//����DHT11����Ϊ����ģʽ
	while( !Check_DHT11() && (retry<Delay_T) ) 	//DHT11������40~80us
	{
		retry++;
		Delay_us(1);  
		
	}
	if( retry >= 100 ) 	return 1; 			//����1����ʾDHT11û��������Ӧ������Ӧʧ��
	else retry = 0;
	while(Check_DHT11() && (retry<Delay_T) )		//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		Delay_us(1);
	}
	if( retry >= Delay_T ) 	return 1; 		//����1����ʾDHT11û��������Ӧ������Ӧʧ��
	return 0; 								//����0����ʾDHT11������Ӧ
}

uint8_t DHT11_Init(void)
{
	
	  DHT11_PIN_OUT();
	  DHT11_Data(1);
	  DHT11_Rst();					//��ʼ�źŵļ��
	  return DHT11_Check();                         //���DHT11�Ƿ�����Ӧ
}

uint8_t DHT11_Read_Bit(void)
{
	uint8_t retry = 0;
	while( Check_DHT11() && (retry<Delay_T) )		//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		Delay_us(1);
	}
	retry = 0;                            
	while( !Check_DHT11() && (retry<Delay_T) )	//�ȴ���Ϊ�ߵ�ƽ��ͬʱ�����ߵ�ƽʱ��
	{
		retry++;
		Delay_us(1);											 
	}
	Delay_us(40); 							//�ȴ�40us
	if( Check_DHT11() )	return 1;  			//��ȡ��λΪ1���򷵻�1
	else 				return 0;          //���򷵻�0
}

uint8_t DHT11_Read_Byte(void)
{
	uint8_t i = 0,data = 0;
	for(i = 0; i < 8; i++)
	{
		data <<= 1;
		data |= DHT11_Read_Bit();  //һλһλ��ȡ
	}
	return data;	       				 //���ض�ȡ������
}


void DHT11_Show_Data(DHT11_TYPE *Dht11Type)
{
	DHT11_Rst();
	if(DHT11_Check() == 0)					//������Ӧ��
	{
		
		 Dht11Type->humInt   = DHT11_Read_Byte();
		 Dht11Type->humDeci  = DHT11_Read_Byte();
		 Dht11Type->tempInt  = DHT11_Read_Byte();
		 Dht11Type->tempDeci = DHT11_Read_Byte();
		 Dht11Type->check    = DHT11_Read_Byte();
		if( (Dht11Type->humInt + Dht11Type->humDeci + Dht11Type->tempInt + Dht11Type->tempDeci) == Dht11Type->check) //���������Ƿ������ȷ
		{
			Dht11Type->humidity= Dht11Type->humInt+ Dht11Type->humDeci / 256.0;   //�洢ʪ��ֵ��������С��
			Dht11Type->temperture = Dht11Type->tempInt+Dht11Type->tempDeci/ 256.0; //�洢�¶�ֵ��������С��
			

		}
	}

    //��ӡ��ǰ�¶Ⱥ�ʪ��ֵ
//	  printf("��ǰ�¶�Ϊ:%.2f,��ǰʪ��Ϊ:.2%f\r\n",Dht11Type->temperture,Dht11Type->humidity);
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
