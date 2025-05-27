#include "gunlun.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lvgl.h"
//#include "lv_examples.h"
LV_FONT_DECLARE(font20);
// 滚轮 1 的选项
const char* roller1_options[] = {"auto", "heat", "dry", "cool"};

// 滚轮 2 的选项范围是 16 - 30
const char* roller2_options[15];
// 滚轮 3 的选项范围是 35 - 95
const char* roller3_options[61];

// 全局变量，用于存储三个滚轮和文本框对象
static lv_obj_t* roller1;
static lv_obj_t* roller2;
static lv_obj_t* roller3;
static lv_obj_t* textarea;

// 生成滚轮 2 和 3 的选项数组
void generate_roller_options() {
    // 生成滚轮 2 的选项
    for (int i = 0; i < 15; i++) {
        char* option = (char*)malloc(10 * sizeof(char));
        snprintf(option, 10, "%d", 16 + i);
        roller2_options[i] = option;
    }
    // 生成滚轮 3 的选项
    for (int i = 0; i < 61; i++) {
        char* option = (char*)malloc(10 * sizeof(char));
        snprintf(option, 10, "%d", 35 + i);
        roller3_options[i] = option;
    }
}

// 释放滚轮 2 和 3 的选项数组内存
void free_roller_options() {
    for (int i = 0; i < 15; i++) {
        free((void*)roller2_options[i]);
    }
    for (int i = 0; i < 61; i++) {
        free((void*)roller3_options[i]);
    }
}

// 滚轮事件处理函数
static void roller_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t* target = lv_event_get_target(e);
        if (target == roller1) {
            // 获取滚轮 1 当前选中的索引
            uint16_t selected_index = lv_roller_get_selected(roller1);
            // 根据索引获取对应的选项字符串
            const char* selected_option = NULL;
            if (selected_index < sizeof(roller1_options) / sizeof(roller1_options[0])) {
                selected_option = roller1_options[selected_index];
            }

            if (selected_option == NULL) {
                // 处理获取选项失败的情况
                return;
            }
            if (strcmp(selected_option, "auto") == 0) {
                lv_obj_add_flag(roller2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(roller3, LV_OBJ_FLAG_HIDDEN);
                lv_textarea_set_text(textarea, "");  // 清空文本框内容
            } else if (strcmp(selected_option, "heat") == 0 || strcmp(selected_option, "cool") == 0) {
                lv_obj_clear_flag(roller2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(roller3, LV_OBJ_FLAG_HIDDEN);
                uint16_t selected_index_2 = lv_roller_get_selected(roller2);
                if (selected_index_2 < 15) {
                    lv_textarea_set_text(textarea, roller2_options[selected_index_2]);
                }
            } else if (strcmp(selected_option, "dry") == 0) {
                lv_obj_add_flag(roller2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(roller3, LV_OBJ_FLAG_HIDDEN);
                uint16_t selected_index_3 = lv_roller_get_selected(roller3);
                if (selected_index_3 < 61) {
                    lv_textarea_set_text(textarea, roller3_options[selected_index_3]);
                }
            }
        } else if (target == roller2) {
            uint16_t selected_index_2 = lv_roller_get_selected(roller2);
            if (selected_index_2 < 15) {
                lv_textarea_set_text(textarea, roller2_options[selected_index_2]);
            }
        } else if (target == roller3) {
            uint16_t selected_index_3 = lv_roller_get_selected(roller3);
            if (selected_index_3 < 61) {
                lv_textarea_set_text(textarea, roller3_options[selected_index_3]);
            }
        }
    }
}

/** 
 * @brief  LVGL 演示 
 * @param  无 
 * @return 无 
 */ 
/**
 * @brief 在指定父容器中创建温度调节滚轮
 * @param parent 父容器对象（如 tab3、屏幕等）
 * @param x 滚轮x坐标
 * @param y 滚轮y坐标
 * @return 滚轮对象指针
 */
lv_obj_t* create_temperature_roller(lv_obj_t *parent, lv_coord_t x, lv_coord_t y)
{
    // 生成温度选项数组（16-35°C）
    char roller_options[20][10];
    for (int i = 0; i < 20; i++) {
        snprintf(roller_options[i], sizeof(roller_options[i]), "%d°C", i + 16);
    }

    // 转换为选项字符串
    char options_str[256] = "";
    for (int i = 0; i < 20; i++) {
        strncat(options_str, roller_options[i], sizeof(options_str) - strlen(options_str) - 1);
        if (i < 19) strncat(options_str, "\n", 1);
    }

    // 创建"set temp"标签
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "set temp:");
    lv_obj_set_style_text_font(label, &font20, 0);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_pos(label, x - 90, y+40); // 标签位于滚轮左侧

    // 创建滚轮样式
    static lv_style_t style_roller;
    lv_style_init(&style_roller);
    lv_style_set_bg_opa(&style_roller, LV_OPA_COVER);
    lv_style_set_bg_color(&style_roller, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_roller, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_roller, LV_GRAD_DIR_HOR); // 水平渐变
    lv_style_set_text_color(&style_roller, lv_color_white());
    lv_style_set_border_width(&style_roller, 2);
    lv_style_set_border_color(&style_roller, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_radius(&style_roller, 10);

    // 创建选中项样式
    static lv_style_t style_roller_selected;
    lv_style_init(&style_roller_selected);
    lv_style_set_bg_color(&style_roller_selected, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_color(&style_roller_selected, lv_color_white());
    lv_style_set_text_font(&style_roller_selected, &font20);

    // 创建滚轮
    lv_obj_t *roller = lv_roller_create(parent);
    lv_roller_set_options(roller, options_str, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(roller, 120, 160);
    lv_obj_set_pos(roller, x, y);
    lv_roller_set_visible_row_count(roller, 5);
    lv_roller_set_selected(roller, 9, LV_ANIM_OFF); // 默认25°C

    // 应用样式
    lv_obj_add_style(roller, &style_roller, 0);
    lv_obj_add_style(roller, &style_roller_selected, LV_PART_SELECTED);

    // 保存标签指针到滚轮用户数据（可选，便于后续操作）
    lv_obj_set_user_data(roller, label);

    return roller;
}
lv_obj_t* create_humidity_roller(lv_obj_t *parent, lv_coord_t x, lv_coord_t y)
{
    // 生成湿度选项数组（0 - 100%）
    char roller_options[101][10];
    for (int i = 0; i < 101; i++) {
        snprintf(roller_options[i], sizeof(roller_options[i]), "%d%%", i);
    }

    // 转换为选项字符串
    char options_str[1024] = "";
    for (int i = 0; i < 101; i++) {
        strncat(options_str, roller_options[i], sizeof(options_str) - strlen(options_str) - 1);
        if (i < 100) strncat(options_str, "\n", 1);
    }

    // 创建"set humidity"标签
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "set humidity:");
    lv_obj_set_style_text_font(label, &font20, 0);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_pos(label, x - 130, y+80); // 标签位于滚轮上方

    // 创建滚轮样式
    static lv_style_t style_roller;
    lv_style_init(&style_roller);
    lv_style_set_bg_opa(&style_roller, LV_OPA_COVER);
    lv_style_set_bg_color(&style_roller, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_roller, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_bg_grad_dir(&style_roller, LV_GRAD_DIR_VER); // 垂直渐变
    lv_style_set_text_color(&style_roller, lv_color_white());
    lv_style_set_border_width(&style_roller, 2);
    lv_style_set_border_color(&style_roller, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_radius(&style_roller, 10);

    // 创建选中项样式
    static lv_style_t style_roller_selected;
    lv_style_init(&style_roller_selected);
    lv_style_set_bg_color(&style_roller_selected, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_text_color(&style_roller_selected, lv_color_black());
    lv_style_set_text_font(&style_roller_selected, &font20);

    // 创建滚轮
    lv_obj_t *roller = lv_roller_create(parent);
    lv_roller_set_options(roller, options_str, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(roller, 80, 200); // 调整尺寸适配竖版
    lv_obj_set_pos(roller, x, y + 30); // 调整位置
    lv_roller_set_visible_row_count(roller, 5); // 增加可见行数
    lv_roller_set_selected(roller, 50, LV_ANIM_OFF); // 默认50%

    // 应用样式
    lv_obj_add_style(roller, &style_roller, 0);
    lv_obj_add_style(roller, &style_roller_selected, LV_PART_SELECTED);

    // 保存标签指针到滚轮用户数据（可选，便于后续操作）
    lv_obj_set_user_data(roller, label);

    return roller;
}
// 创建显示温湿度的界面
/**
 * @brief 创建湿度弧形量表（通用组件）
 * @param parent 父容器（如 tab4、屏幕等）
 * @param x 坐标 x
 * @param y 坐标 y
 * @param init_value 初始湿度值（0-100，建议20-80）
 * @return 弧形量表对象指针
 */
lv_obj_t* create_humidity_arc(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, uint8_t init_value)
{
    // 创建弧形量表
    lv_obj_t *arc = lv_arc_create(parent);
    lv_obj_set_size(arc, 90, 90);
    lv_obj_set_pos(arc, x, y);
    lv_arc_set_rotation(arc, 135);          // 旋转起始角度
    lv_arc_set_bg_angles(arc, 0, 270);       // 背景弧度范围
    lv_arc_set_value(arc, init_value);       // 初始值
    //lv_obj_center(arc);                     // 居中对齐（可根据parent调整）

    // 创建数值显示标签
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "0%");
    lv_obj_set_style_text_font(label, &font20, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_align(label, LV_ALIGN_TOP_LEFT,40,130);
    // 绑定事件：值变化时更新标签
    lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);
    lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL); // 初始化标签显示

    // 保存标签到量表用户数据，便于外部访问
    lv_obj_set_user_data(arc, label);

    return arc;
}
static void value_changed_event_cb(lv_event_t *e)
{
    lv_obj_t *arc = lv_event_get_target(e);
    lv_obj_t *label = lv_event_get_user_data(e);
    
    // 更新标签显示
    uint8_t value = lv_arc_get_value(arc);
    lv_label_set_text_fmt(label, "%d%%", value);
    
    // （可选）旋转标签到弧形末端（根据需求决定是否保留）
    // lv_arc_rotate_obj_to_angle(arc, label, 25);
}
void lv_mainstart4()
{
}



