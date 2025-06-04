#include "picture.h"
static lv_anim_timeline_t* anim_timeline = NULL; 
 
static lv_obj_t* obj1 = NULL; 
 
static const lv_coord_t obj_width = 90; 
static const lv_coord_t obj_height = 70; 
 
/** 
 * @brief       a1动画回调函数 
 * @param       var:对象 
 * @param       v:数值 
 * @retval      无 
 */ 
static void set_width(void* var, int32_t v) 
{ 
    /* 设置obj1对象宽度 */ 
    lv_obj_set_width((lv_obj_t*)var, v); 
} 
 
/** 
 * @brief       a2动画回调函数 
 * @param       var:对象 
 * @param       v:数值 
 * @retval      无 
 */ 
static void set_height(void* var, int32_t v) 
{ 
    /* 设置obj1对象高度 */ 
    lv_obj_set_height((lv_obj_t*)var, v); 
} 
// * @brief       创建时间线 
// * @param       无 
// * @retval      无 
// */ 
static void anim_timeline_create(void) 
{ 
    /* obj1对象增宽动画 */ 
    lv_anim_t a1; 
    lv_anim_init(&a1); 
    lv_anim_set_var(&a1, obj1); 
    lv_anim_set_values(&a1, obj_width, obj_width + 10 ); 
    lv_anim_set_early_apply(&a1, false); 
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)set_width); 
    lv_anim_set_path_cb(&a1, lv_anim_path_overshoot); 
    lv_anim_set_time(&a1, 300); 
 
    /* obj1对象增高动画 */ 
    lv_anim_t a2; 
    lv_anim_init(&a2); 
    lv_anim_set_var(&a2, obj1); 
    lv_anim_set_values(&a2, obj_height, obj_height + 20 ); 
    lv_anim_set_early_apply(&a2, false); 
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)set_height); 
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_out); 
    lv_anim_set_time(&a2, 300); 
     
    /* 创建动画时间线 */ 
    anim_timeline = lv_anim_timeline_create(); 
    /* 把a1动画添加到时间线中 */ 
    lv_anim_timeline_add(anim_timeline, 0, &a1); 
    /* 把a2动画添加到时间线中 */ 
    lv_anim_timeline_add(anim_timeline, 300, &a2); 
} 
 
/** 
 * @brief       按键回调函数 
 * @param       e：事件 
 * @retval      无 
 */ 
static void btn_start_event_handler(lv_event_t* e) 
{ 
    lv_obj_t* btn = lv_event_get_target(e); 
	   if (!anim_timeline) { 
        anim_timeline_create(); 
    } 
    /* 获取按下的点击状态 */ 
    bool reverse = lv_obj_has_state(btn, LV_STATE_CHECKED); 
    /* 支持整个动画组的向前和向后播放 */ 
    lv_anim_timeline_set_reverse(anim_timeline, reverse); 
    /* 启动动画时间轴 */ 
    lv_anim_timeline_start(anim_timeline); 
} 
 
/** 
 * @brief       LVGL入口 
 * @param       无 
 * @retval      无 
 */ 
void lv_main(void) 
{ 
    lv_obj_t* par = lv_scr_act(); 
    /* 创建按键部件 */ 
    lv_obj_t* btn_start = lv_btn_create(par); 
    /* 设置回调函数 */ 
lv_obj_add_event_cb(btn_start, btn_start_event_handler, 
                    LV_EVENT_VALUE_CHANGED, NULL); 
    lv_obj_align(btn_start, LV_ALIGN_TOP_MID, -100, 20); 
    /* 按键文本 */ 
    lv_obj_t* label_start = lv_label_create(btn_start); 
    lv_label_set_text(label_start, "Start"); 
    lv_obj_center(label_start); 
 
    /* 创建动画操作对象 */ 
    obj1 = lv_obj_create(par); 
    lv_obj_set_size(obj1, obj_width, obj_height); 
} 

