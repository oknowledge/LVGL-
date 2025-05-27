#ifndef __AIRCON_CONTROL_H
#define __AIRCON_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/**
 * @brief 创建带状态显示的空调控制开关（通用组件）
 * @param parent 父容器对象（如 tab、屏幕、容器等）
 * @param x 组件在父容器中的 x 坐标
 * @param y 组件在父容器中的 y 坐标
 * @return 开关对象指针（`lv_obj_t*`）
 */
lv_obj_t* create_aircon_switch(lv_obj_t *parent, lv_coord_t x, lv_coord_t y);
lv_obj_t* create_aircon_switch2(lv_obj_t *parent, lv_coord_t x, lv_coord_t y);
/**
 * @brief 在 tab3 中添加空调控制组件的示例函数
 * @param tab3 tab3 标签页对象
 */
void add_aircon_control_to_tab3(lv_obj_t *tab3);
static void aircon_sw_event_cb(lv_event_t *e);
static void aircon_sw_event_cb2(lv_event_t *e);
#ifdef __cplusplus
}
#endif

#endif /* __AIRCON_CONTROL_H */