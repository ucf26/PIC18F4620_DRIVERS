/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;



int main() {
    
    app_init();
    ret = lcd_8bit_send_char_data(&lcd_2, 'Z');
    ret = lcd_8bit_send_char_data(&lcd_2, 'Z');
    ret = lcd_8bit_send_char_data(&lcd_2, 'Z');
    while(1)
    {
        
    }
    return (EXIT_SUCCESS);
}


void app_init(void)
{
    ecu_layer_initialize();
}