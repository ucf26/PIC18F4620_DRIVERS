/* 
 * File:   ecu_layer_init.c
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 8:37 PM
 */

#include "ecu_layer_init.h"


void app_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_initialize(&keypad1);
}