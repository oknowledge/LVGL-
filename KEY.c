#include "KEY.h"

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY1 == 1 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))  /* 按键松开标志为 1, 且有任意一个按键按下了 */
    {
        HAL_Delay(10);          /* 去抖动 */
        key_up = 0;

        if (KEY1 == 1)  keyval = KEY1_PRES;

        if (KEY2 == 0)  keyval = KEY2_PRES;

        if (KEY3 == 0)  keyval = KEY3_PRES;

        if (KEY4 == 0)  keyval = KEY4_PRES;
    }
    else if (KEY1 == 0 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}
 

