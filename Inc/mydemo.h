#ifndef __MYDEMO_h
#define __MYDEMO_h

#include "main.h"
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "lv_demo_widgets.h"

static void lv_example_imgbtn(void);
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act()) 
void lv_example(void);


#endif
