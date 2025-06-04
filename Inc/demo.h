#ifndef __demo_h
#define __demo_h

#include "main.h"
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "lv_demo_widgets.h"

 
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

void lv_mainstart(void);
//static void lv_example_label_1(void);
//static void lv_example_label_2(void);
//static void lv_example_label_3(void);
 void lv_example_label_4(void);
 void lv_example_label_5(void); 
void lv_example_tabview_2(void);
void create_colored_text(lv_obj_t * parent_tab, const char * text);
	void create_colored_text2(lv_obj_t * parent_tab, const char * text);
		void create_colored_text3(lv_obj_t * parent_tab, const char * text);
		void create_colored_text4(lv_obj_t * parent_tab, const char * text);
		 void create_ad_sensor_display(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, int ad_value, float voltage);
		 void update_ad_sensor_display(lv_obj_t *container, int ad_value, float voltage);
		 lv_obj_t* create_flashing_circle(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, uint16_t radius, uint32_t period_ms);
#endif













