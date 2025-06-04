#ifndef GUNLUN_H
#define GUNLUN_H

#include "main.h"
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "lv_demo_widgets.h"

//#define scr_act_width() lv_obj_get_width(lv_scr_act())
/**
 * @brief LVGL演示
 * @param 无
 * @return 无
 */
lv_obj_t* create_temperature_roller(lv_obj_t *parent, lv_coord_t x, lv_coord_t y);
void lv_mainstart4();
lv_obj_t* create_humidity_roller(lv_obj_t *parent, lv_coord_t x, lv_coord_t y);
void lv_ex_gauge_1(void);
void create_humidity_arc(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, uint8_t init_value);
static void value_changed_event_cb(lv_event_t *e);
#endif /* GUNLUN_H */













