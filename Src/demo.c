/**************************** 第一部分 开始 ****************************/ 
/** 
* @brief  LVGL 演示 
253 
 
正点原子 LVGL开发教程 
 254 
LVGL开发指南 
 * @param  无 
 * @return 无 
 */ 
#include "demo.h"
#include "temp.h"
#include "gunlun.h"
#include "slider.h"
#include "stdlib.h"
#include "adc.h"
#include "stdio.h"
#include "mqtt.h"
#include "tcp.h"
LV_FONT_DECLARE(font20);
LV_FONT_DECLARE(font50);
LV_FONT_DECLARE(font80);
LV_FONT_DECLARE(font70);
LV_IMG_DECLARE(sunnny)
extern DHT11_TYPE Dht11Type;
extern float a;
//extern ADC_TYPE adcType;
lv_obj_t *tab1;
lv_obj_t *tab2;
lv_obj_t *tab3;
lv_obj_t *tab4;
lv_obj_t *tab5;
lv_obj_t *ad_display;
void lv_mainstart(void) 
{ 
//    lv_example_label_1(); 
//    lv_example_label_2(); 
//    lv_example_label_3(); 
	  lv_example_label_4();
	  lv_example_label_5(); 	
} 
/**************************** 第一部分 结束 ****************************/ 
 
/**************************** 第二部分 开始 ****************************/ 
/** 
 * @brief  例1 
 * @param  无 
 * @return 无 
 */ 
void lv_example_tabview_2(void)
{
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
		//create_humidity_arc(tab4, 20,90, Dht11Type.humidity);
		    // 创建显示组件
     
    
	 
if(a>=2)
{
	create_colored_text4(tab5, "燃气");
}
}
lv_obj_t* create_flashing_circle(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, uint16_t radius, uint32_t period_ms)
{
    // 创建圆形对象
    lv_obj_t *circle = lv_obj_create(parent);
    lv_obj_set_size(circle, radius * 2, radius * 2);
    lv_obj_set_pos(circle, x - radius, y - radius); // 居中对齐
    
    // 设置为圆形
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(circle, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, 0);
    
    // 创建动画
    static lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, circle);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_style_bg_opa);
    lv_anim_set_values(&anim, LV_OPA_COVER, LV_OPA_30); // 透明度从完全不透明到30%
    lv_anim_set_time(&anim, period_ms / 2); // 半周期
    lv_anim_set_playback_time(&anim, period_ms / 2); // 回放半周期
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE); // 无限循环
    lv_anim_start(&anim);
    
    return circle;
}
void update_ad_sensor_display(lv_obj_t *container, int ad_value, float voltage)
{
    if (!container) return;
    
    // 获取保存的标签指针
    lv_obj_t **labels = (lv_obj_t **)lv_obj_get_user_data(container);
    if (!labels) return;
    
    // 更新 AD 值标签
    char ad_text[32];
    snprintf(ad_text, sizeof(ad_text), "AD Value: %u", ad_value);
    lv_label_set_text(labels[0], ad_text);
    
    // 更新电压值标签
    char voltage_text[32];
    snprintf(voltage_text, sizeof(voltage_text), "Voltage: %.2f V", voltage);
    lv_label_set_text(labels[1], voltage_text);
}
static lv_obj_t *s_prev_ad_container = NULL; // 静态变量追踪上一个AD显示容器

void create_ad_sensor_display(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, int ad_value, float voltage)
{
    // 第一步：销毁上一次创建的容器及所有子组件
    if (s_prev_ad_container != NULL) {
        lv_obj_del(s_prev_ad_container); // 销毁容器及其所有子标签
        s_prev_ad_container = NULL;
    }

    // 第二步：创建新的AD数据显示容器
    lv_obj_t *new_container = lv_obj_create(parent ? parent : lv_scr_act());
    lv_obj_set_size(new_container, 200, 100);
    lv_obj_set_pos(new_container, x, y);
    lv_obj_set_style_bg_color(new_container, lv_color_hex(0xF0F0F0), 0);
    lv_obj_set_style_radius(new_container, 10, 0);
    lv_obj_set_style_border_width(new_container, 1, 0);

    // 创建标题标签
    lv_obj_t *title_label = lv_label_create(new_container);
    lv_label_set_text(title_label, "AD Sensor Data");
    lv_obj_set_style_text_font(title_label, &font20, 0);
    lv_obj_set_pos(title_label, 10, 10);

    // 创建 AD 值标签
    lv_obj_t *ad_value_label = lv_label_create(new_container);
    char ad_text[32];
    snprintf(ad_text, sizeof(ad_text), "AD Value: %u", ad_value);
    lv_label_set_text(ad_value_label, ad_text);
    lv_obj_set_style_text_font(ad_value_label, &font20, 0);
    lv_obj_set_pos(ad_value_label, 10, 40);

    // 创建电压值标签
    lv_obj_t *voltage_label = lv_label_create(new_container);
    char voltage_text[32];
    snprintf(voltage_text, sizeof(voltage_text), "Voltage: %.2f V", voltage);
    lv_label_set_text(voltage_label, voltage_text);
    lv_obj_set_style_text_font(voltage_label, &font20, 0);
    lv_obj_set_pos(voltage_label, 10, 65);

    // 无需保存标签指针（容器销毁时自动清理子组件）
    // 更新静态变量追踪当前容器
    s_prev_ad_container = new_container;
}
 void create_colored_text(lv_obj_t * parent_tab, const char * text) 
{ 
    /* 在指定标签页中创建标签 */ 
    lv_obj_t* label = lv_label_create(parent_tab);  
    
    /* 设置标签文本 */          
    lv_label_set_text(label, text); 
    
    /* 启用标签文本重新着色 */ 
    lv_label_set_recolor(label, true);       
    
    /* 设置标签文本字体 */  
    lv_obj_set_style_text_font(label, &font20, LV_PART_MAIN);  
    
    /* 设置标签宽度为父标签页的80% */ 
    lv_obj_set_width(label, lv_obj_get_width(parent_tab) * 0.8);           
    
    /* 设置标签在父标签页中靠左上对齐 */ 
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 5, 5);  // 向右偏移20px，向下偏移20px
    
    /* 设置标签文本对齐方式 */ 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);  // 文本左对齐
}
void create_colored_text3(lv_obj_t * parent_tab, const char * text) 
{ 
    /* 在指定标签页中创建标签 */ 
    lv_obj_t* label = lv_label_create(parent_tab);  
    
    /* 设置标签文本 */          
    lv_label_set_text(label, text); 
    
    /* 启用标签文本重新着色 */ 
    lv_label_set_recolor(label, true);       
    
    /* 设置标签文本字体 */  
    lv_obj_set_style_text_font(label, &font70, LV_PART_MAIN);  
    
    /* 设置标签宽度为父标签页的80% */ 
    lv_obj_set_width(label, lv_obj_get_width(parent_tab) * 0.8);           
    
    /* 设置标签在父标签页中靠左上对齐 */ 
    lv_obj_align(label, LV_ALIGN_TOP_LEFT,120,90);  // 向右偏移20px，向下偏移20px
    
    /* 设置标签文本对齐方式 */ 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);  // 文本左对齐
}
void create_colored_text2(lv_obj_t * parent_tab, const char * text) 
{ 
    /* 在指定标签页中创建标签 */ 
    lv_obj_t* label = lv_label_create(parent_tab);  
    
    /* 设置标签文本 */          
    lv_label_set_text(label, text); 
    
    /* 启用标签文本重新着色 */ 
    lv_label_set_recolor(label, true);       
    
    /* 设置标签文本字体 */  
    lv_obj_set_style_text_font(label, &font80, LV_PART_MAIN);  
    
    /* 设置标签宽度为父标签页的80% */ 
    lv_obj_set_width(label, lv_obj_get_width(parent_tab) * 0.8);           
    
    /* 设置标签在父标签页中靠左上对齐 */ 
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 90, 120);  // 向右偏移20px，向下偏移20px
    
    /* 设置标签文本对齐方式 */ 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);  // 文本左对齐
}
void create_colored_text4(lv_obj_t * parent_tab, const char * text) 
{ 
		lv_obj_t *title_label = lv_label_create(parent_tab);
    lv_label_set_text(title_label, text);
    lv_obj_set_pos(title_label, 120, 20);
    lv_obj_set_style_text_color(title_label, lv_color_black(), 0);
    lv_obj_set_style_text_font(title_label, &font80, 0);
}
 void lv_example_label_4(void) 
{ 

// /* 定义并创建标签 */ 
//lv_obj_t* label = lv_label_create(lv_scr_act());  
///* 设置标签文本 */          
//lv_label_set_text(label, "#0000ff 无锡太湖学院# #ff00ff 物联网2 202#" "\n" 
//                             "#ff00aa 吴金英222012051 #" 
//                             "#aa00ff 小憨 #"); 
// /* 启用标签文本重新着色 */ 
//lv_label_set_recolor(label, true);       
///* 设置标签文本字体 */  
//lv_obj_set_style_text_font(label, &font50, LV_PART_MAIN);  
///* 设置标签宽度 */ 
////lv_obj_set_width(label, scr_act_width() );           
///* 设置标签位置 */ 
//lv_obj_align(label, LV_ALIGN_CENTER, -scr_act_width() / 16, 0);  
///* 设置标签文本对齐方式 */ 
//lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);   
} 

 void lv_example_label_5(void) 
{
//    // 创建一个普通标签
//    lv_obj_t* label = lv_label_create(lv_scr_act());  
//    // 启用标签文本重新着色
//    lv_label_set_recolor(label, true);       
//    // 设置标签文本字体
//    // 注意：需要确保 font20 已经正确定义
//    lv_obj_set_style_text_font(label, &font20, LV_PART_MAIN);  

    // 创建一个带有符号的标签
    lv_obj_t *sym_label = lv_label_create(lv_scr_act());
    // 设置标签文本
    lv_label_set_text(sym_label, "5G" LV_SYMBOL_WIFI);
    // 设置标签位置
    lv_obj_set_pos(sym_label, 430, 0);
}
//static void lv_example_label_1(void) 
//{ 

// /* 定义并创建标签 */ 
//lv_obj_t* label = lv_label_create(lv_scr_act());  
///* 设置标签文本 */          
//    lv_label_set_text(label, "#0000ff Re-color# #ff00ff words# #ff0000 of a# "  
//                             "label, align the lines to the center" 
//                             "and  wrap long text automatically."); 
// /* 启用标签文本重新着色 */ 
//lv_label_set_recolor(label, true);       
///* 设置标签文本字体 */  
//lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN);  
///* 设置标签宽度 */ 
//lv_obj_set_width(label, scr_act_width() / 3);           
///* 设置标签位置 */ 
//lv_obj_align(label, LV_ALIGN_CENTER, -scr_act_width() / 3, 0);  
///* 设置标签文本对齐方式 */ 
//    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);   
//} 


///** 
// * @brief  例2 
// * @param  无 
// * @return 无 
// */ 
//static void lv_example_label_2(void) 
//{ 
// /* 定义并创建标签 */ 
//lv_obj_t* label = lv_label_create(lv_scr_act());   
///* 设置标签文本 */                               
//lv_label_set_text(label, "It is a circularly scrolling text. ");  
///* 设置标签文本字体 */ 
//lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN);  
///* 设置标签宽度 */  
//lv_obj_set_width(label, scr_act_width() / 3);  
///* 设置标签长模式：循环滚动 */   
//lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);  
///* 设置标签位置 */ 
//    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);  
//} 
// 
///** 
// * @brief  例3 
// * @param  无 
// * @return 无 
// */ 
//static void lv_example_label_3(void) 
//{ 
// /* 定义并创建标签 */ 
//lv_obj_t* label = lv_label_create(lv_scr_act());  
///* 设置标签文本 */    
//lv_label_set_text_fmt(label, "Label can set text like %s", "printf");   
///* 设置标签文本字体 */ 
//lv_obj_set_style_text_font(label,&lv_font_montserrat_18,LV_PART_MAIN);  
///* 设置标签宽度 */ 
//lv_obj_set_width(label, scr_act_width() / 3);   
///* 设置标签位置 */ 
//lv_obj_align(label, LV_ALIGN_CENTER, scr_act_width() / 3, 0);  
///* 设置标签文本对齐方式 */ 
//    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);   
// 
// /* 定义并创建阴影标签 */ 
// 

//lv_obj_t* label_shadow = lv_label_create(lv_scr_act());    
///* 设置标签文本 */ 
//lv_label_set_text(label_shadow, lv_label_get_text(label));     
///* 设置标签文本字体 */ 
//lv_obj_set_style_text_font(label_shadow, &lv_font_montserrat_18, LV_PART_MAIN);   
///* 设置标签宽度 */  
//lv_obj_set_width(label_shadow, scr_act_width() / 3);    
///* 设置标签文本透明度 */ 
//lv_obj_set_style_text_opa(label_shadow, LV_OPA_30, LV_PART_MAIN);  
///* 设置标签文本颜色 */ 
//lv_obj_set_style_text_color(label_shadow, lv_color_black(), LV_PART_MAIN);  
///* 设置标签文本对齐方式 */ 
//lv_obj_set_style_text_align(label_shadow, LV_TEXT_ALIGN_CENTER,  
//LV_PART_MAIN);   
// /* 设置标签位置 */ 
//    lv_obj_align_to(label_shadow, label, LV_ALIGN_TOP_LEFT, 3, 3);  
//} 
