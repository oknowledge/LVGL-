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
//void lv_port_disp_init(void);   // 显示设备初始�?
//void lv_port_indev_init(void);  // 输入设备初始�?
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
//twobutton();//�����Ҫ����ʵ��ڶ�����Ȼ��ʵ����������������ťһ�����飬��ε����ťkey4��ʵ��һ�������ƶ��Ĳ���
//toesp();�����Ҫ���ĵڶ���ʵ�飬Ȼ��Ҫ��tcp��esp8266��mqtt��h�ļ��е�wifi�˺��Լ����룬����������Ӳ��ɹ��İ���wifi��������
//��һ��ʵ������и���������Ȼ��temp�ļ���֮ǰ��д����
//pict();//��ʾ����
//hanzi();//显示文字
//calculator();//计算器
//scgunlun();//那个滚轮实现温度湿度的显示
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//			endTimeTick=HAL_GetTick();
// 这个是最新的连接mqtt注意连接的是我的mqtt需要你自己改参数
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

void texts(void)//mqtt数据显示在屏幕上代码
{
		lv_init();
	lv_port_disp_init();
	HAL_TIM_Base_Start_IT(&htim3); 
	lv_port_indev_init();
    /* 静态变量保存上次创建的标签指针 */
    static lv_obj_t* prev_label = NULL;    
    /* 如果存在旧标签，删除它 */
    if (prev_label != NULL) {
        lv_obj_del(prev_label);
        prev_label = NULL;
    }
    /* 创建新标签 */
    lv_obj_t* label = lv_label_create(lv_scr_act());
    
    /* 设置标签文本 */
    char *tempandhum = (char *)malloc(100);
    sprintf(tempandhum, "%d,%d,%d,%d\r\n", 
            Dht11Type.humInt, Dht11Type.humDeci, 
            Dht11Type.tempInt, Dht11Type.tempDeci);
    lv_label_set_text(label, tempandhum);
    lv_label_set_recolor(label, true);
    
    /* 设置标签样式 */
    lv_obj_set_style_text_font(label, &font20, LV_PART_MAIN);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, -scr_act_width() / 16, 0);
    
    /* 保存当前标签指针供下次使用 */
    prev_label = label;
    printf("***************************************\r\n");
    /* 释放临时内存 */
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
void toesp(lv_obj_t *parrent)  // 传入 tab2 父容器
{
    // 初始化 LVGL（通常在程序入口初始化，此处假设需要）
    // lv_init();               // 若已在别处初始化，可注释此行
    // lv_port_disp_init();
    // lv_port_indev_init();

    // 在 tab2 下创建标签
    lv_obj_t *label = lv_label_create(parrent);
    if (!label) return;

    // 设置标签基本属性（可选）
    lv_obj_set_size(label, 200, LV_SIZE_CONTENT);  // 设置宽度，高度自适应
    lv_obj_set_pos(label, 150, 90);                           // 居中对齐

    // 计算字符串总长度（包含固定字符和结束符）
    size_t fixed_len = strlen("城市") + strlen("天气") + strlen("气温") + strlen("时间") + 7;  // 固定字符：4个逗号 + 空格
    size_t total_length = strlen(WX_Res.city) + strlen(WX_Res.text) +
                          strlen(WX_Res.temperature) + strlen(WX_Res.date) + fixed_len + 7;  // +1 用于 '\0'

    char *weather_info = (char *)malloc(total_length);
    if (!weather_info) {
        lv_label_set_text(label, "内存分配失败");
        printf("Error: 内存分配失败\n");
        return;
    }

    // 使用安全函数拼接字符串（避免中文乱码，确保格式正确）
    int ret = snprintf(weather_info, total_length, 
			"城市:%s""\n""天气:%s,气温:%s°C""\n""时间:%s",  // 移除多余空格，使用中文逗号
                       WX_Res.city, WX_Res.text, 
                       WX_Res.temperature, WX_Res.date);
		lv_obj_set_style_text_font(label, &font70, LV_PART_MAIN);  
    // 设置标签文本并释放内存
    lv_label_set_text(label, weather_info);
    free(weather_info);
}

void twobutton()
{
		lv_init();

lv_port_disp_init();
HAL_TIM_Base_Start_IT(&htim3); 

lv_port_indev_init();
lv_group_t *g = lv_group_create();//������
lv_group_set_default(g);//����ΪĬ�� group ��
lv_indev_set_group(indev_keypad,g);//���������豸�� group ��

//�����ú����ٴ����ؼ�
lv_obj_t *slider = lv_slider_create(lv_scr_act());
lv_obj_center(slider);
lv_group_add_obj(g,slider);//���ָ��������group���У�����Ĭ�����еĲ���ʹ��
 
//���� btn1
lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
lv_obj_align(btn1,LV_ALIGN_CENTER,0,-80);
lv_obj_set_size(btn1,200,80);
lv_obj_t *label1 = lv_label_create(btn1);
lv_label_set_text(label1,"01");
lv_obj_align_to(label1,btn1,LV_ALIGN_CENTER,0,0);

//���� btn2
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

static uint32_t g_fac_us=0; /*us��ʱ������*/ 
void delay_us(uint32_t nus) 
{ 
	uint32_t ticks; 
	uint32_t told, tnow, tent=0; 
	uint32_t reload=SysTick->LOAD; /*LOAD��ֵ */ 
	ticks= nus* g_fac_us; /*��Ҫ�Ľ����� */ 
	told=SysTick->VAL; /*�ս���ʱ�ļ�����ֵ */ 
	while(1) 
	{ 
		tnow=SysTick->VAL; 
		if(tnow!= told) 
		{ 
				if(tnow< told) 
				{ 
				tent+= told-tnow; 
						/*����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ����� */ 
					} 
				else 
					{ 
				tent+= reload-tnow+ told; 
						} 
			told = tnow; 
				if(tent>= ticks) 
			{ 
					break; /*ʱ�䳬��/����Ҫ�ӳٵ�ʱ�䣬���˳� */ 
			} 
}} }
void load_draw_dialog(void) 
{ 
 lcd_clear(WHITE); /*���� */ 
 lcd_show_string(lcddev.width-24,0,200,16,16, "RST",BLUE);/* ��ʾ�������� */
} 
/** 
*@ brief ���败�������Ժ��� 
*@ param �� 
*@ retval �� 
*/ 
void rtp_test(void) 
{
		while(1) 
		{ 
			tp_dev.scan(0); 
if(tp_dev.sta& TP_PRES_DOWN) /* ������������ */ 
{ 
if(tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) 
{ 
if(tp_dev.x[0] > (lcddev.width -24) && tp_dev.y[0]<16) 
{ 
load_draw_dialog();/* ��� */ 
} 
else 
{ 
tp_draw_big_point(tp_dev.x[0], tp_dev.y[0],RED); /* ���� */ 
} 
} 
} 
else 
{ 
HAL_Delay(10); /*û�а������µ�ʱ�� */ 
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
