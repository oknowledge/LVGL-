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
#include "dht11.h"
#include "temp.h"
#include "slider.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
LV_IMG_DECLARE(sunnny)
extern Weather_Result WX_Res;
LV_FONT_DECLARE(font70);
LV_FONT_DECLARE(font20);
double a;
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
 uint32_t startTimeTick = 0; 
 uint32_t endTimeTick = 0;
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
	startTimeTick=HAL_GetTick();
 
	 
  /* USER CODE END 2 */
	lv_init();
	lv_port_disp_init();
	HAL_TIM_Base_Start_IT(&htim3); 
	lv_port_indev_init();
	a=get_ADCValue();
	//value=get_ADCValue();
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);
	 //ESP8266_STA_TCPClient_Test();	
    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_BLUE, 2), 0);
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
		lv_obj_set_style_text_font(tab_btns, &font20, LV_PART_MAIN); 
		lv_example_label_5(); 	
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "主页");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "天气");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "温度");
    lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "湿度");
    lv_obj_t * tab5 = lv_tabview_add_tab(tabview, "燃气");
    /*Add content to the tabs*/
		//lv_obj_t * label = lv_label_create(tab1);
    //lv_label_set_text(label, "First tab");
		create_colored_text(tab1, "#0000ff 无锡太湖学院#""\n"
															"#ff00ff 物联网2202#""\n" 
                              "#ff00aa 赵荣胜222012062 #""\n" 
                              );
		create_colored_text2(tab1, "智能家居系统");
		create_colored_text4(tab3, "室内温度");
		create_colored_text4(tab4, "室内湿度");
		 /* 创建图片对象 */
    lv_obj_t * img = lv_img_create(tab2);  // 在屏幕上创建图片    
    /* 设置图片源 */
    lv_img_set_src(img, &sunnny);                  // 使用预定义的图片数组    
    /* 调整图片大小（可选） */
    lv_obj_set_size(img, 96, 75);               // 缩放图片到200x200像素   
    /* 居中对齐 */
    lv_obj_set_pos(img, 40, 80);  // 直接设置绝对坐标（覆盖居中对齐）  
		toesp(tab2);
		//lv_obj_t *temp_bar =create_temperature_bar(tab3, -20, 40, Dht11Type.temperture, 40, 25);
		//update_temperature(temp_bar, Dht11Type.temperture);
		create_temperature_roller(tab3, 240,90);
		create_aircon_switch(tab3, 160,250);
		create_aircon_switch2(tab4, 160,250);
		create_humidity_roller(tab4, 240,50);
		 
		    // 创建显示组件
if(a>=2)
{
	create_colored_text4(tab5, "燃气");
}
  
  while (1)
  {
    /* USER CODE END WHILE */
			a=get_ADCValue();
    /* USER CODE BEGIN 3 */
			endTimeTick=HAL_GetTick();
			DHT11_Show_Data(&Dht11Type);
			printf ("%d,%f,%f\n",(int)(a*4090/3.3), Dht11Type.temperture, Dht11Type.humidity);
		//create_humidity_arc(tab4, 20,90, Dht11Type.humidity);
		//lv_obj_t *ad_display = create_ad_sensor_display(tab5, 20, 100, a* 4096 / 3.3,a);
		// update_ad_sensor_display(ad_display, a* 4096 / 3.3,a);
		
			HAL_Delay(5);
		//create_temperature_bar4(tab3,Dht11Type.temperture, 40, 25);
		create_temperature_bar(tab3, -20, 40, Dht11Type.temperture, 40, 25);
		create_humidity_arc(tab4, 20,90, Dht11Type.humidity);
		//txts(tab3);
		create_ad_sensor_display(tab5, 20, 100, a* 4096 / 3.3,a);
		lv_task_handler();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void txts(lv_obj_t *parent)
{
    // 静态变量保存上次创建的标签指针
    static lv_obj_t* prev_label = NULL;    
    
    // 如果存在旧标签，删除它
    if (prev_label != NULL) {
        lv_obj_del(prev_label);
        prev_label = NULL;
    }
    
    // 确保父容器有效，默认为活动屏幕
    if (parent == NULL) parent = lv_scr_act();
    
    // 创建新标签
    lv_obj_t* label = lv_label_create(parent);
    
    // 设置标签文本（修正温湿度变量对应关系）
    char tempandhum[100];  // 使用栈内存而非堆内存，避免手动管理free
    sprintf(tempandhum, "温度:%d.%d°C\n湿度:%d.%d%%",  
            Dht11Type.tempInt, Dht11Type.tempDeci,
            Dht11Type.humInt, Dht11Type.humDeci);
    lv_label_set_text(label, tempandhum);
    lv_label_set_recolor(label, true);
    
    // 设置标签样式
    lv_obj_set_style_text_font(label, &font70, LV_PART_MAIN);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    
    // 居中对齐（基于父容器而非屏幕）
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    
    // 保存当前标签指针供下次使用
    prev_label = label;
}
static lv_obj_t *prev_temp_container = NULL;
static lv_obj_t *prev_temp_bar = NULL;
void create_temperature_bar4(lv_obj_t *parent, int32_t temp, lv_coord_t x, lv_coord_t y)
{
    // 清除上一次创建的温度条
    if (prev_temp_container != NULL) {
        lv_obj_del(prev_temp_container);
        prev_temp_container = NULL;
        prev_temp_bar = NULL;
    }

    // 创建样式（仅初始化一次）
    static lv_style_t style_indic;
    static bool style_initialized = false;
    
    if (!style_initialized) {
        lv_style_init(&style_indic);
        lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
        lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
        lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
        lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);
        style_initialized = true;
    }

    // 创建温度条容器
    lv_obj_t *container = lv_obj_create(parent);
    lv_obj_set_size(container, 20, 120);  // 调整高度为合理值（原200可能超出容器范围）
    lv_obj_set_pos(container, x, y);
    lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    // 创建温度条
    lv_obj_t *bar = lv_bar_create(container);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(bar, 20, 100);       // 调整进度条高度适配容器
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, 0);  // 底部居中对齐
    lv_bar_set_range(bar, -20, 40);
    lv_bar_set_value(bar, temp, LV_ANIM_ON);  // 开启动画效果

    // 创建温度显示文本
    lv_obj_t *temp_label = lv_label_create(container);
    lv_label_set_text_fmt(temp_label, "%d°C", temp);
    lv_obj_align(temp_label, LV_ALIGN_TOP_MID, 0, -5);  // 文本位于进度条上方
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_16, 0);

    // 更新静态变量以追踪当前组件
    prev_temp_container = container;
    prev_temp_bar = bar;
    // 无需保存temp_label，因为容器删除时会自动销毁子对象
}
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
void toesp(lv_obj_t *parent)  // 传入 tab2 父容器（参数名建议改为 parent）
{
    // 创建标签并设置自适应尺寸
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    // 居中对齐后沿Y轴向下移动90个单位
    lv_obj_center(label);
    lv_obj_set_y(label, lv_obj_get_y(label) + 90);

    // 定义固定格式字符串（直接计算长度，避免错误）
    const char *format = "城市:%s\n天气:%s,气温:%s°C\n时间:%s";
    size_t format_len = strlen(format);
    size_t total_length = 
        strlen(WX_Res.city) + 
        strlen(WX_Res.text) + 
        strlen(WX_Res.temperature) + 
        strlen(WX_Res.date) + 
        format_len;

    char *weather_info = (char *)malloc(total_length);
    if (!weather_info) {
        lv_label_set_text(label, "内存不足");
        return;
    }

    // 使用安全格式化，检查返回值防止越界
    int ret = snprintf(weather_info, total_length, format, 
                       WX_Res.city, WX_Res.text, 
                       WX_Res.temperature, WX_Res.date);
    if (ret < 0 || ret >= (int)total_length) {
        lv_label_set_text(label, "格式错误");
        free(weather_info);
        return;
    }

    // 设置中文字体（确保字体正确声明）
    LV_FONT_DECLARE(font70);  // 替换为实际中文字体
    lv_obj_set_style_text_font(label, &font70, 0);
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
lv_group_add_obj(g,slider);//����ָ��������group���У�����Ĭ�����еĲ���ʹ��
 
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
