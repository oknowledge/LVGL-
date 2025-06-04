#include "mydemo.h"
LV_IMG_DECLARE(bird3) 

// 动画回调函数，用于更新x轴和y轴的值以及图片大小
static void anim_x_y_size_cb(void* var, int32_t v) 
{
    lv_obj_t* img = (lv_obj_t*)var;
    // 计算x轴和y计算x轴和y轴的值，根据动画进度从右下角移动到左上角
    int32_t x = 480 - (v * 480 / 5000);  // 假设动画时间为5000ms
    int32_t y = 320 - (v * 320 / 5000);
    lv_obj_set_x(img, x);
    lv_obj_set_y(img, y);

    // 计算图片大小，根据动画进度由小变大
    int32_t size = 50 + (v * 180 / 5000);  // 假设起始大小为50，最终大小为150
    lv_obj_set_width(img, size);
    lv_obj_set_height(img, size);
}

void lv_example(void) 
{
    /* 第一步：创建图片对象 */ 
    lv_obj_t* lv_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(lv_obj, &bird3);

    /* 第二步：动画初始化 */ 
    lv_anim_t a;
    lv_anim_init(&a);

    /* 第三步：设置动画目标为图片对象 */ 
    lv_anim_set_var(&a, lv_obj);

    /* 第四步：设置动画起点和终点 */ 
    // 这里使用一个较大的数值作为动画进度的范围，因为我们在回调函数中根据这个范围计算实际的位置和大小变化
    lv_anim_set_values(&a, 0, 5000); 

    /* 第五步：设置动画时间 */ 
    lv_anim_set_time(&a, 5000);

    /* 第六步：设置动画回调函数 */ 
    lv_anim_set_exec_cb(&a, anim_x_y_size_cb);

    /* 第七步：设置动画轨道 */ 
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);

    /* 第八步：开启动画 */ 
    lv_anim_start(&a); 
} 

