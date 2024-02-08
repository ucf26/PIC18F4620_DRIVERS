/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;

const uint8 customChar[] = {
  0x0A,
  0x1F,
  0x1F,
  0x0E,
  0x04,
  0x00,
  0x00,
  0x00
};

int main() {
    
    app_init();
    ret = lcd_8bit_send_string_pos(&lcd_2, 1, 1, "Broken..");
    while(1)
    {
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 5, customChar, 0);
    }
    return (EXIT_SUCCESS);
}


void app_init(void)
{
    ecu_layer_initialize();
}