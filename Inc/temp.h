#ifndef __temp_H
#define __temp_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/**
 * @brief 创建一个带温度显示的垂直条形图
 * @param parent 父容器对象
 * @param min_temp 最小温度值
 * @param max_temp 最大温度值
 * @param init_temp 初始温度值
 * @param x 组件x坐标
 * @param y 组件y坐标
 * @return 创建的温度条对象指针
 */
void create_temperature_bar(lv_obj_t *parent, int32_t min_temp, int32_t max_temp, int32_t init_temp, lv_coord_t x, lv_coord_t y);
lv_obj_t* create_temperature_bar2(lv_obj_t *parent, int32_t min_temp, int32_t max_temp, int32_t init_temp, lv_coord_t x, lv_coord_t y);
/**
 * @brief 更新温度条的值并同步更新显示文本
 * @param bar 温度条对象
 * @param temp 温度值
 */
void update_temperature(lv_obj_t *bar, int32_t temp);
lv_style_t* get_indicator_style(void);
/**
 * @brief 在tab3中创建温度显示示例
 */


#ifdef __cplusplus
}
#endif

#endif /* __LV_EXAMPLE_BAR_H */



