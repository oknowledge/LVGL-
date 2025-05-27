#include "slider.h"
#include "main.h"
LV_FONT_DECLARE(font90);
/**
 * @brief 创建带状态显示的空调控制开关
 * @param parent 父容器对象
 * @param x 组件x坐标
 * @param y 组件y坐标
 * @return 开关对象指针
 */
lv_obj_t* create_aircon_switch(lv_obj_t *parent, lv_coord_t x, lv_coord_t y)
{
    // 创建开关样式
    static lv_style_t style_sw_indic;
    static lv_style_t style_sw_bg;
    
    lv_style_init(&style_sw_indic);
    lv_style_set_bg_color(&style_sw_indic, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_radius(&style_sw_indic, LV_RADIUS_CIRCLE);
    
    lv_style_init(&style_sw_bg);
    lv_style_set_bg_color(&style_sw_bg, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_opa(&style_sw_bg, LV_OPA_30);
    lv_style_set_radius(&style_sw_bg, LV_RADIUS_CIRCLE);
    
    // 创建开关
    lv_obj_t *sw = lv_switch_create(parent);
    lv_obj_add_style(sw, &style_sw_indic, LV_PART_INDICATOR);
    lv_obj_add_style(sw, &style_sw_bg, LV_PART_MAIN);
    lv_obj_set_pos(sw, x, y);
    
    // 创建状态标签（初始隐藏）
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "加湿器已经打开");
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_obj_set_style_text_font(label, &font90, 0);
    lv_obj_set_pos(label, x-20 , y - 30);
    lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    
    // 将标签指针保存为开关的用户数据
    lv_obj_set_user_data(sw, label);
    
    // 添加事件回调
    lv_obj_add_event_cb(sw, aircon_sw_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
    return sw;
}

/**
 * @brief 空调开关事件处理函数
 */
lv_obj_t* create_aircon_switch2(lv_obj_t *parent, lv_coord_t x, lv_coord_t y)
{
    // 创建开关样式
    static lv_style_t style_sw_indic;
    static lv_style_t style_sw_bg;
    
    lv_style_init(&style_sw_indic);
    lv_style_set_bg_color(&style_sw_indic, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_radius(&style_sw_indic, LV_RADIUS_CIRCLE);
    
    lv_style_init(&style_sw_bg);
    lv_style_set_bg_color(&style_sw_bg, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_opa(&style_sw_bg, LV_OPA_30);
    lv_style_set_radius(&style_sw_bg, LV_RADIUS_CIRCLE);
    
    // 创建开关
    lv_obj_t *sw = lv_switch_create(parent);
    lv_obj_add_style(sw, &style_sw_indic, LV_PART_INDICATOR);
    lv_obj_add_style(sw, &style_sw_bg, LV_PART_MAIN);
    lv_obj_set_pos(sw, x, y);
    
    // 创建状态标签（初始隐藏）
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "空调已经打开");
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_obj_set_style_text_font(label, &font90, 0);
    lv_obj_set_pos(label, x-20 , y - 30);
    lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    
    // 将标签指针保存为开关的用户数据
    lv_obj_set_user_data(sw, label);
    
    // 添加事件回调
    lv_obj_add_event_cb(sw, aircon_sw_event_cb2, LV_EVENT_VALUE_CHANGED, NULL);


  
    return sw;
}
static void aircon_sw_event_cb2(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_user_data(sw);
    
    if(label == NULL) return;
    
    if(lv_obj_has_state(sw, LV_STATE_CHECKED)) {
        // 开关打开：显示"空调已经打开"
        lv_label_set_text(label, "加湿器已经打开");
        lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
        
        // 添加淡入动画
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, 0, 255);
        lv_anim_set_time(&a, 300);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_style_text_opa);
        lv_anim_start(&a);
    }
    else {
        // 开关关闭：隐藏标签（可添加淡出动画）
        lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    }
}
static void aircon_sw_event_cb(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_user_data(sw);
    
    if(label == NULL) return;
    
    if(lv_obj_has_state(sw, LV_STATE_CHECKED)) {
        // 开关打开：显示"空调已经打开"
        lv_label_set_text(label, "空调已经打开");
        lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
        
        // 添加淡入动画
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, label);
        lv_anim_set_values(&a, 0, 255);
        lv_anim_set_time(&a, 300);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_style_text_opa);
        lv_anim_start(&a);
    }
    else {
        // 开关关闭：隐藏标签（可添加淡出动画）
        lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    }
}

/**
 * @brief 在tab3中创建空调控制组件示例
 */
void add_aircon_control_to_tab3(lv_obj_t *tab3)
{
    // 创建标题
    lv_obj_t *title = lv_label_create(tab3);
    lv_label_set_text(title, "空调控制");
    lv_obj_set_style_text_font(title, &font90, 0);
    lv_obj_set_pos(title, 20, 20);
    
    // 创建空调开关（位置可根据需要调整）
    create_aircon_switch(tab3, 50, 80);
}
 