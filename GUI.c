#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
 
// 全局变量，用于存储滚轮和文本框对象
static lv_obj_t* roller1;


// 函数声明
void create_calculator(void);
void lv_mainstart(void);
void lv_mainstart4(void);

// 滚轮事件处理函数
static void roller_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        // 获取滚轮当前选中的索引
        uint16_t sel = lv_roller_get_selected(roller1);
        // 清空屏幕上除滚轮之外的所有对象
        lv_obj_t* obj;
        for (int i = 0; (obj = lv_obj_get_child(lv_scr_act(), i)) != NULL; ) {
            if (obj != roller1) {
                lv_obj_del(obj);
            } else {
                // 如果是指定滚轮，不删除，继续检查下一个对象
                i++;
            }
        }
        // 根据选中的索引调用不同的函数
        switch (sel) {
            case 0:
                create_calculator();
                break;
            case 1:
                lv_mainstart();
                break;
            case 2:
                lv_mainstart4();
                break;
            default:
                break;
        }
    }
}


void lv_mainstart8(void) 
{ 
    // 定义并创建滚轮
    roller1 = lv_roller_create(lv_scr_act()); 
    // 滚轮添加选项并设置无限模式
    static const char* roller_options = "calculator\nintroduction\nsum2";
    lv_roller_set_options(roller1, roller_options, LV_ROLLER_MODE_NORMAL);  
    // 设置滚轮宽度
    lv_obj_set_width(roller1, 110); 
    // 设置滚轮可见选项个数
    lv_roller_set_visible_row_count(roller1, 4);  
    // 设置滚轮位置
    lv_obj_set_pos(roller1, 350, 40);
    // 添加事件处理函数
    lv_obj_add_event_cb(roller1, roller_event_cb, LV_EVENT_ALL, NULL);


}

