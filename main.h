/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_dma.h"

#include "stm32f4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "lv_demo_widgets.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void texts(void);
void delay_us(uint32_t nus);
void rtp_test(void) ;
void load_draw_dialog(void);
void twobutton(void);
void toesp(lv_obj_t *parrent);
void pict(void);
void hanzi(void);
void calculator(void);
void scgunlun(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOE
#define KEY3_Pin GPIO_PIN_3
#define KEY3_GPIO_Port GPIOE
#define KEY4_Pin GPIO_PIN_4
#define KEY4_GPIO_Port GPIOE
#define T_MISO_Pin GPIO_PIN_5
#define T_MISO_GPIO_Port GPIOE
#define T_MOSI_Pin GPIO_PIN_6
#define T_MOSI_GPIO_Port GPIOE
#define T_CS_Pin GPIO_PIN_13
#define T_CS_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define DHT11_Pin GPIO_PIN_5
#define DHT11_GPIO_Port GPIOC
#define T_CLK_Pin GPIO_PIN_0
#define T_CLK_GPIO_Port GPIOB
#define T_PEN_Pin GPIO_PIN_1
#define T_PEN_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define IIC_SCL_Pin GPIO_PIN_6
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_7
#define IIC_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
typedef struct //DHT11ʽ¾݀Ѝ
{
uint8_t setHum; 
uint8_t setTemp; 
 float  temperture; 
 float  humidity; 
uint8_t tempInt; 
uint8_t tempDeci; 
uint8_t humInt; 
uint8_t humDeci; 
uint8_t fanRunf;
uint8_t check;
}DHT11_TYPE;
extern DHT11_TYPE Dht11Type;
#define RX_LEN 128 
typedef struct  
{  
uint8_t  RX_flag:1;        
uint16_t RX_Size;         
uint8_t  RX_pData[RX_LEN]; 
uint16_t TX_Size;          
uint8_t  TX_pData[RX_LEN]; 
}USART_TYPE;  

extern USART_TYPE UsartType;
typedef struct 
{
uint8_t adfireInt; 
uint8_t adfireDeci; 
uint8_t vfireInt; 
uint8_t vfireDeci; 
uint8_t setfireInt; 
uint8_t setfireDeci;
float  fireidity;
float  setfireidity;
}ADC_TYPE;
 extern ADC_TYPE adcType;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
