#ifndef __KEY_H
#define __KEY_H
#include "main.h"
#define KEY1 HAL_GPIO_ReadPin (KEY1_GPIO_Port, KEY1_Pin) //读取 KEY1 引脚 /
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) //读取 KEY2 引脚 /
#define KEY3 HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) //读取 KEY3 引脚 /
#define KEY4 HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) //读取 KEY4 引脚 */
#define KEY1_PRES 1 // KEY1 按下 /
#define KEY2_PRES 2 //KEY2 按下 /
#define KEY3_PRES 3 //KEY3 按下 /
#define KEY4_PRES 4 //KEY4 按下 */
uint8_t key_scan (uint8_t mode); /* 按键扫描函数 */
#endif



