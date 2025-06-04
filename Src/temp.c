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
 #include "main.h"
 #include "temp.h"
static lv_obj_t *s_prev_container = NULL; // 静态变量追踪上一次创建的容器

void create_temperature_bar(lv_obj_t *parent, int32_t min_temp, int32_t max_temp, int32_t init_temp, lv_coord_t x, lv_coord_t y) {
    // **第一步：销毁上一次创建的组件**
    if (s_prev_container != NULL) {
        lv_obj_del(s_prev_container); // 销毁容器及其所有子对象（bar、label）
        s_prev_container = NULL;
    }

    // **第二步：创建新组件**
    if (!parent) parent = lv_scr_act();

    // 创建新容器
    lv_obj_t *new_container = lv_obj_create(parent);
    lv_obj_set_size(new_container, 60, 240);
    lv_obj_set_pos(new_container, x, y);
    lv_obj_set_style_bg_opa(new_container, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(new_container, LV_OBJ_FLAG_SCROLLABLE);

    // 创建温度条（直接使用局部样式，避免静态样式问题）
    lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

    lv_obj_t *bar = lv_bar_create(new_container);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(bar, 20, 200);
    lv_obj_center(bar);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_bar_set_range(bar, min_temp, max_temp);
    lv_bar_set_value(bar, init_temp, LV_ANIM_OFF);

    // 创建温度标签
    lv_obj_t *temp_label = lv_label_create(new_container);
    lv_label_set_text_fmt(temp_label, "%d°C", init_temp);
    lv_obj_align(temp_label, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_16, 0);

    // **第三步：更新静态变量指向新容器**
    s_prev_container = new_container;
}
/**
 * @brief 更新温度条的值并同步更新显示文本
 * @param bar 温度条对象
 * @param temp 温度值
 */
void update_temperature(lv_obj_t *bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
    
    // 更新温度文本
    lv_obj_t *temp_label = (lv_obj_t*)lv_obj_get_user_data(bar);
    if(temp_label) {
        lv_label_set_text_fmt(temp_label, "%d°C", temp);
    }
}
lv_obj_t* create_temperature_bar2(lv_obj_t *parent, int32_t min_temp, int32_t max_temp, int32_t init_temp, lv_coord_t x, lv_coord_t y)
{
    // 创建样式
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

    // 创建温度条容器
    lv_obj_t *container = lv_obj_create(parent);
    lv_obj_set_size(container, 60, 240);
    lv_obj_set_pos(container, x, y);
    lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    // 创建温度条
    lv_obj_t *bar = lv_bar_create(container);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(bar, 20, 200);
    lv_obj_center(bar);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_bar_set_range(bar, min_temp, max_temp);
    lv_bar_set_value(bar, init_temp, LV_ANIM_OFF);

    // 创建温度显示文本
    lv_obj_t *temp_label = lv_label_create(container);
    lv_label_set_text_fmt(temp_label, "%d°C", init_temp);
    lv_obj_align(temp_label, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_16, 0);

    // 保存文本指针到用户数据，便于后续更新
    lv_obj_set_user_data(bar, temp_label);




    return bar;
}
/**
 * @brief 在tab3中创建温度显示示例
 */


