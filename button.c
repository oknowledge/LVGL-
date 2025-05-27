#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // 引入math.h头文件以使用pow函数

static lv_obj_t* textarea; // 全局变量，用于存储文本框和按键等对象
static double num1 = 0;
static double num2 = 0;
static char op = '+';
static double result = 0;
static int input_index = 0;
static int is_second_num = 0;
static int has_dot1 = 0; // 标记第一个数是否有小数点
static int has_dot2 = 0; // 标记第二个数是否有小数点
static int decimal_places1 = 0; // 第一个数的小数位数
static int decimal_places2 = 0; // 第二个数的小数位数

// 定义样式变量
static lv_style_t num_btn_style;
static lv_style_t operator_btn_style;
static lv_style_t reset_btn_style;

static void num_btn_event_cb(lv_event_t * e) // 数字按键事件处理函数
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED) {
        const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));
        int num = atoi(btn_text);
        if (!is_second_num) {
            if (!has_dot1) {
                num1 = num1 * 10 + num;
            } else {
                decimal_places1++;
                num1 += num / pow(10, decimal_places1);
            }
            char num_str[30];
            snprintf(num_str, sizeof(num_str), "%.2f", num1);
            lv_textarea_set_text(textarea, num_str);
        } else {
            if (!has_dot2) {
                num2 = num2 * 10 + num;
            } else {
                decimal_places2++;
                num2 += num / pow(10, decimal_places2);
            }
            char num_str[30];
            snprintf(num_str, sizeof(num_str), "%.2f %c %.2f", num1, op, num2);
            lv_textarea_set_text(textarea, num_str);
        }
    }
}

static void dot_btn_event_cb(lv_event_t * e) // 小数点按键事件处理函数
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED) {
        if (!is_second_num) {
            if (!has_dot1) {
                has_dot1 = 1;
                char num_str[30];
                snprintf(num_str, sizeof(num_str), "%.2f.", num1);
                lv_textarea_set_text(textarea, num_str);
            }
        } else {
            if (!has_dot2) {
                has_dot2 = 1;
                char num_str[30];
                snprintf(num_str, sizeof(num_str), "%.2f %c %.2f.", num1, op, num2);
                lv_textarea_set_text(textarea, num_str);
            }
        }
    }
}

static void operator_btn_event_cb(lv_event_t * e) // 运算符按键事件处理函数
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED) {
        const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));
        op = btn_text[0];
        is_second_num = 1;
        has_dot1 = 0;
        decimal_places1 = 0;
        char num_str[30];
        snprintf(num_str, sizeof(num_str), "%.2f %c ", num1, op);
        lv_textarea_set_text(textarea, num_str);
    }
}

static void reset_btn_event_cb(lv_event_t * e) // 复位按键事件处理函数
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        // 清空文本框内容
        lv_textarea_set_text(textarea, "");
        // 重置全局变量
        num1 = 0;
        num2 = 0;
        op = '+';
        result = 0;
        input_index = 0;
        is_second_num = 0;
        has_dot1 = 0;
        has_dot2 = 0;
        decimal_places1 = 0;
        decimal_places2 = 0;
    }
}

static void equal_btn_event_cb(lv_event_t * e) // 等于号按键事件处理函数
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    lv_textarea_set_text(textarea, "Error: Division by zero");
                    return;
                }
                break;
            default:
                break;
        }
        char result_str[30];
        snprintf(result_str, sizeof(result_str), "%.2f %c %.2f = %.2f", num1, op, num2, result);
        lv_textarea_set_text(textarea, result_str);
        // 重置状态
        num1 = 0;
        num2 = 0;
        is_second_num = 0;
        has_dot1 = 0;
        has_dot2 = 0;
        decimal_places1 = 0;
        decimal_places2 = 0;
    }
}

void create_num_buttons(void) // 创建数字按键
{
    int x = 50;
    int y = 200 - 120;
    for (int i = 0; i < 10; i++) {
        lv_obj_t * btn = lv_btn_create(lv_scr_act());
        lv_obj_set_pos(btn, x + (i % 3) * 60, y + (i / 3) * 60);
        lv_obj_set_size(btn, 50, 50);

        // 应用数字按钮样式
        lv_obj_add_style(btn, &num_btn_style, 0);

        lv_obj_t * label = lv_label_create(btn);
        char num_str[2];
        snprintf(num_str, sizeof(num_str), "%d", i);
        lv_label_set_text(label, num_str);
        lv_obj_center(label);

        lv_obj_add_event_cb(btn, num_btn_event_cb, LV_EVENT_ALL, NULL);
    }
}

void create_dot_button(void) // 创建小数点按键
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_set_pos(btn, 300, 380 - 120);
    lv_obj_set_size(btn, 50, 50);

    // 应用数字按钮样式
    lv_obj_add_style(btn, &num_btn_style, 0);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, ".");
    lv_obj_center(label);

    lv_obj_add_event_cb(btn, dot_btn_event_cb, LV_EVENT_ALL, NULL);
}

void create_operator_buttons(void) // 创建运算符按键
{
    const char* operators[] = {"+", "-", "*", "/"};
    int x = 230;
    int y = 200 - 120;
    for (int i = 0; i < 4; i++) {
        lv_obj_t * btn = lv_btn_create(lv_scr_act());
        lv_obj_set_pos(btn, x, y + i * 60);
        lv_obj_set_size(btn, 50, 50);

        // 应用运算符按钮样式
        lv_obj_add_style(btn, &operator_btn_style, 0);

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text(label, operators[i]);
        lv_obj_center(label);

        lv_obj_add_event_cb(btn, operator_btn_event_cb, LV_EVENT_ALL, NULL);
    }
}

void create_equal_button(void) // 创建等于号按键
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_set_pos(btn, 170, 380 - 120);
    lv_obj_set_size(btn, 50, 50);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "=");
    lv_obj_center(label);

    lv_obj_add_event_cb(btn, equal_btn_event_cb, LV_EVENT_ALL, NULL);
}

// 创建文本框
void lv_mainstart7(void) 
{ 
    textarea = lv_textarea_create(lv_scr_act());
    lv_textarea_set_one_line(textarea, true);
    lv_obj_set_size(textarea, 230, 50);
    lv_obj_set_pos(textarea, 50, 2);
}

// 创建复位按键
void create_reset_button(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_set_pos(btn, 110, 380 - 120);
    lv_obj_set_size(btn, 50, 50);

    // 应用复位按钮样式
    lv_obj_add_style(btn, &reset_btn_style, 0);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "C");
    lv_obj_center(label);

    lv_obj_add_event_cb(btn, reset_btn_event_cb, LV_EVENT_ALL, NULL);
}

// 主函数调用创建各个组件
void create_calculator(void)
{
    // 初始化数字按钮样式
    lv_style_init(&num_btn_style);
    lv_style_set_bg_color(&num_btn_style, lv_color_hex(0xFF00AA)); // 设置数字按钮背景颜色为白色，可按需修改
    lv_style_set_bg_opa(&num_btn_style, LV_OPA_COVER);

    // 初始化运算符按钮样式
    lv_style_init(&operator_btn_style);
    lv_style_set_bg_color(&operator_btn_style, lv_color_hex(0xFFA500)); // 设置运算符按钮背景颜色为橙色，可按需修改
    lv_style_set_bg_opa(&operator_btn_style, LV_OPA_COVER);

    // 初始化复位按钮样式
    lv_style_init(&reset_btn_style);
    lv_style_set_bg_color(&reset_btn_style, lv_color_hex(0xFF0000)); // 设置复位按钮背景颜色为红色
    lv_style_set_bg_opa(&reset_btn_style, LV_OPA_COVER);

    lv_mainstart7();
    create_num_buttons();
    create_dot_button();
    create_operator_buttons();
    create_equal_button();
    create_reset_button();
}    