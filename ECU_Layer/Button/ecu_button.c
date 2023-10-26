/* 
 * File:   ecu_button.c
 * Author: Yousef Mahmoud
 *
 * Created on October 25, 2023, 3:10 AM
 */

#include "ecu_button.h"


Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK ;
    if(NULL == btn )
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_direction_initialize(&(btn->buton));
    }
    return ret;
}

Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK ;
    logic_t pin_logic_status = GPIO_LOW;
    if(NULL == btn || NULL == btn_state)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_read_logic(&(btn->buton), &pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED; 
            }
            else
            {
                *btn_state = BUTTON_RELEASED; 
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_RELEASED; 
            }
            else
            {
                *btn_state = BUTTON_PRESSED; 
            }
        }
        else { /* do nothing */}
    }
    return ret;
}
