/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD.h"
#include "lvgl.h"
#include "touch.h"
#include "demo.h"
#include <stdio.h>
#include "tcp.h"
#include "mqtt.h"
#include "esp8266.h"
#include "KEY.h"
#include "mydemo.h"
#include "button.h"
#include "gunlun.h"
#include "GUI.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern Weather_Result WX_Res;
LV_FONT_DECLARE(font70);
LV_FONT_DECLARE(font20);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//void lv_port_disp_init(void);   // æ˜¾ç¤ºè®¾å¤‡åˆå§‹åŒ?
//void lv_port_indev_init(void);  // è¾“å…¥è®¾å¤‡åˆå§‹åŒ?
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern lv_indev_t * indev_keypad;
extern lv_indev_t * indev_touch;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
// uint32_t startTimeTick = 0; 
 //uint32_t endTimeTick = 0;
	//double a;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	//DHT11_Init();
Dht11Type.setTemp=20;
Dht11Type.setHum=60;
//adcType.setfireidity=1.2;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//	startTimeTick=HAL_GetTick();
 
 
  /* USER CODE END 2 */
			lv_init();
	lv_port_disp_init();
	HAL_TIM_Base_Start_IT(&htim3); 
	lv_port_indev_init();
lv_example_tabview_2();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//twobutton();//Õâ¸öÊÇÒª³­µÄÊµÑéµÚ¶þ¸ö£¬È»ºóÊµÑéÏÖÏóÊÇÓÐÁ½¸ö°´Å¥Ò»¸ö»¬¿é£¬¶à´Îµç»ú°´Å¥key4»áÊµÏÖÒ»¸ö»¬¿éÒÆ¶¯µÄ²Ù×÷
//toesp();Õâ¸öÊÇÒª³­µÄµÚ¶þ¸öÊµÑé£¬È»ºóÒª¸Ätcp£¬esp8266£¬mqttµãhÎÄ¼þÖÐµÄwifiÕËºÅÒÔ¼°ÃÜÂë£¬Èç¹û³öÏÖÁ¬½Ó²»³É¹¦µÄ°ÎÏÂwifiÖØÐÂÁ¬½Ó
//µÚÒ»¸öÊµÑé¾ÍÊÇÓÐ¸ö´¥Ãþ¹¦ÄÜÈ»ºótempÎÄ¼þÄãÖ®Ç°ÊÇÐ´¹ýµÄ
//pict();//ÏÔÊ¾¶¯»­
//hanzi();//æ˜¾ç¤ºæ–‡å­—
//calculator();//è®¡ç®—å™¨
//scgunlun();//é‚£ä¸ªæ»šè½®å®žçŽ°æ¸©åº¦æ¹¿åº¦çš„æ˜¾ç¤º
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//			endTimeTick=HAL_GetTick();
// è¿™ä¸ªæ˜¯æœ€æ–°çš„è¿žæŽ¥mqttæ³¨æ„è¿žæŽ¥çš„æ˜¯æˆ‘çš„mqttéœ€è¦ä½ è‡ªå·±æ”¹å‚æ•°
//			DHT11_Show_Data(&Dht11Type);
//			get_ADCValue();
//			printf ("%d\n",(int)Dht11Type.temperture*100+(int)Dht11Type.humidity);
				HAL_Delay(5);
		lv_task_handler();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void scgunlun()
{
		lv_init();
	lv_port_disp_init();
	HAL_TIM_Base_Start_IT(&htim3); 
	lv_port_indev_init();
	//lv_mainstart4();
}

void texts(void)//mqttæ•°æ®æ˜¾ç¤ºåœ¨å±å¹•ä¸Šä»£ç 
{
		lv_init();
	lv_port_disp_init();
	HAL_TIM_Base_Start_IT(&htim3); 
	lv_port_indev_init();
    /* é™æ€å˜é‡ä¿å­˜ä¸Šæ¬¡åˆ›å»ºçš„æ ‡ç­¾æŒ‡é’ˆ */
    static lv_obj_t* prev_label = NULL;    
    /* å¦‚æžœå­˜åœ¨æ—§æ ‡ç­¾ï¼Œåˆ é™¤å®ƒ */
    if (prev_label != NULL) {
        lv_obj_del(prev_label);
        prev_label = NULL;
    }
    /* åˆ›å»ºæ–°æ ‡ç­¾ */
    lv_obj_t* label = lv_label_create(lv_scr_act());
    
    /* è®¾ç½®æ ‡ç­¾æ–‡æœ¬ */
    char *tempandhum = (char *)malloc(100);
    sprintf(tempandhum, "%d,%d,%d,%d\r\n", 
            Dht11Type.humInt, Dht11Type.humDeci, 
            Dht11Type.tempInt, Dht11Type.tempDeci);
    lv_label_set_text(label, tempandhum);
    lv_label_set_recolor(label, true);
    
    /* è®¾ç½®æ ‡ç­¾æ ·å¼ */
    lv_obj_set_style_text_font(label, &font20, LV_PART_MAIN);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, -scr_act_width() / 16, 0);
    
    /* ä¿å­˜å½“å‰æ ‡ç­¾æŒ‡é’ˆä¾›ä¸‹æ¬¡ä½¿ç”¨ */
    prev_label = label;
    printf("***************************************\r\n");
    /* é‡Šæ”¾ä¸´æ—¶å†…å­˜ */
    free(tempandhum);
}
void calculator()
{
lv_init();
lv_port_disp_init();
HAL_TIM_Base_Start_IT(&htim3); 
lv_port_indev_init();
create_calculator();
}
void hanzi()
{
	lv_init();
lv_port_disp_init();
HAL_TIM_Base_Start_IT(&htim3); 
lv_port_indev_init();
lv_mainstart();
}
void pict()
{
	lv_init();
lv_port_disp_init();
HAL_TIM_Base_Start_IT(&htim3); 
lv_port_indev_init();
lv_example();
	
}
void toesp(lv_obj_t *parrent)  // ä¼ å…¥ tab2 çˆ¶å®¹å™¨
{
    // åˆå§‹åŒ– LVGLï¼ˆé€šå¸¸åœ¨ç¨‹åºå…¥å£åˆå§‹åŒ–ï¼Œæ­¤å¤„å‡è®¾éœ€è¦ï¼‰
    // lv_init();               // è‹¥å·²åœ¨åˆ«å¤„åˆå§‹åŒ–ï¼Œå¯æ³¨é‡Šæ­¤è¡Œ
    // lv_port_disp_init();
    // lv_port_indev_init();

    // åœ¨ tab2 ä¸‹åˆ›å»ºæ ‡ç­¾
    lv_obj_t *label = lv_label_create(parrent);
    if (!label) return;

    // è®¾ç½®æ ‡ç­¾åŸºæœ¬å±žæ€§ï¼ˆå¯é€‰ï¼‰
    lv_obj_set_size(label, 200, LV_SIZE_CONTENT);  // è®¾ç½®å®½åº¦ï¼Œé«˜åº¦è‡ªé€‚åº”
    lv_obj_set_pos(label, 150, 90);                           // å±…ä¸­å¯¹é½

    // è®¡ç®—å­—ç¬¦ä¸²æ€»é•¿åº¦ï¼ˆåŒ…å«å›ºå®šå­—ç¬¦å’Œç»“æŸç¬¦ï¼‰
    size_t fixed_len = strlen("åŸŽå¸‚") + strlen("å¤©æ°”") + strlen("æ°”æ¸©") + strlen("æ—¶é—´") + 7;  // å›ºå®šå­—ç¬¦ï¼š4ä¸ªé€—å· + ç©ºæ ¼
    size_t total_length = strlen(WX_Res.city) + strlen(WX_Res.text) +
                          strlen(WX_Res.temperature) + strlen(WX_Res.date) + fixed_len + 7;  // +1 ç”¨äºŽ '\0'

    char *weather_info = (char *)malloc(total_length);
    if (!weather_info) {
        lv_label_set_text(label, "å†…å­˜åˆ†é…å¤±è´¥");
        printf("Error: å†…å­˜åˆ†é…å¤±è´¥\n");
        return;
    }

    // ä½¿ç”¨å®‰å…¨å‡½æ•°æ‹¼æŽ¥å­—ç¬¦ä¸²ï¼ˆé¿å…ä¸­æ–‡ä¹±ç ï¼Œç¡®ä¿æ ¼å¼æ­£ç¡®ï¼‰
    int ret = snprintf(weather_info, total_length, 
			"åŸŽå¸‚:%s""\n""å¤©æ°”:%s,æ°”æ¸©:%sÂ°C""\n""æ—¶é—´:%s",  // ç§»é™¤å¤šä½™ç©ºæ ¼ï¼Œä½¿ç”¨ä¸­æ–‡é€—å·
                       WX_Res.city, WX_Res.text, 
                       WX_Res.temperature, WX_Res.date);
		lv_obj_set_style_text_font(label, &font70, LV_PART_MAIN);  
    // è®¾ç½®æ ‡ç­¾æ–‡æœ¬å¹¶é‡Šæ”¾å†…å­˜
    lv_label_set_text(label, weather_info);
    free(weather_info);
}

void twobutton()
{
		lv_init();

lv_port_disp_init();
HAL_TIM_Base_Start_IT(&htim3); 

lv_port_indev_init();
lv_group_t *g = lv_group_create();//´´½¨×é
lv_group_set_default(g);//ÉèÖÃÎªÄ¬ÈÏ group ×é
lv_indev_set_group(indev_keypad,g);//¹ØÁªÊäÈëÉè±¸µ½ group ×é

//ÏÈÉèÖÃºÃ×éÔÙ´´½¨¿Ø¼þ
lv_obj_t *slider = lv_slider_create(lv_scr_act());
lv_obj_center(slider);
lv_group_add_obj(g,slider);//Ìí¼ÓÖ¸¶¨²¿¼þµ½group×éÖÐ£¨²»ÔÚÄ¬ÈÏ×éÖÐµÄ²¿¼þÊ¹ÓÃ
 
//´´½¨ btn1
lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
lv_obj_align(btn1,LV_ALIGN_CENTER,0,-80);
lv_obj_set_size(btn1,200,80);
lv_obj_t *label1 = lv_label_create(btn1);
lv_label_set_text(label1,"01");
lv_obj_align_to(label1,btn1,LV_ALIGN_CENTER,0,0);

//´´½¨ btn2
lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
lv_obj_align_to(btn2,btn1,LV_ALIGN_OUT_BOTTOM_LEFT,0,80);
lv_obj_set_size(btn2,200,80);
lv_obj_t *label2 = lv_label_create(btn2);
lv_label_set_text(label2,"02");
lv_obj_align_to(label2,btn2,LV_ALIGN_CENTER,0,0);

lv_group_add_obj(g,btn1);
lv_group_add_obj(g,btn2);
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
   void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)
	{
		lv_tick_inc(1);
	}}

static uint32_t g_fac_us=0; /*usÑÓÊ±±¶³ËÊý*/ 
void delay_us(uint32_t nus) 
{ 
	uint32_t ticks; 
	uint32_t told, tnow, tent=0; 
	uint32_t reload=SysTick->LOAD; /*LOADµÄÖµ */ 
	ticks= nus* g_fac_us; /*ÐèÒªµÄ½ÚÅÄÊý */ 
	told=SysTick->VAL; /*¸Õ½øÈëÊ±µÄ¼ÆÊýÆ÷Öµ */ 
	while(1) 
	{ 
		tnow=SysTick->VAL; 
		if(tnow!= told) 
		{ 
				if(tnow< told) 
				{ 
				tent+= told-tnow; 
						/*ÕâÀï×¢ÒâÒ»ÏÂSYSTICKÊÇÒ»¸öµÝ¼õµÄ¼ÆÊýÆ÷¾Í¿ÉÒÔÁË */ 
					} 
				else 
					{ 
				tent+= reload-tnow+ told; 
						} 
			told = tnow; 
				if(tent>= ticks) 
			{ 
					break; /*Ê±¼ä³¬¹ý/µÈÓÚÒªÑÓ³ÙµÄÊ±¼ä£¬ÔòÍË³ö */ 
			} 
}} }
void load_draw_dialog(void) 
{ 
 lcd_clear(WHITE); /*ÇåÆÁ */ 
 lcd_show_string(lcddev.width-24,0,200,16,16, "RST",BLUE);/* ÏÔÊ¾ÇåÆÁÇøÓò */
} 
/** 
*@ brief µç×è´¥ÃþÆÁ²âÊÔº¯Êý 
*@ param ÎÞ 
*@ retval ÎÞ 
*/ 
void rtp_test(void) 
{
		while(1) 
		{ 
			tp_dev.scan(0); 
if(tp_dev.sta& TP_PRES_DOWN) /* ´¥ÃþÆÁ±»°´ÏÂ */ 
{ 
if(tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) 
{ 
if(tp_dev.x[0] > (lcddev.width -24) && tp_dev.y[0]<16) 
{ 
load_draw_dialog();/* Çå³ý */ 
} 
else 
{ 
tp_draw_big_point(tp_dev.x[0], tp_dev.y[0],RED); /* »­µã */ 
} 
} 
} 
else 
{ 
HAL_Delay(10); /*Ã»ÓÐ°´¼ü°´ÏÂµÄÊ±ºò */ 
} 
} 
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
