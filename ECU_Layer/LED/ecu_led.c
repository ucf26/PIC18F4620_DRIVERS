/* 
 * File:   ecu_led.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 6:07 AM
 */

#include "../LED/ecu_led.h"

/**
 * @breif   initialize the assigned pin to be OUTPUT and teurn the led ON or OFF 
 * @param   led : pointer to the led configrations
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin , 
                                 .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * @breif   turn the led on
 * @param   led : pointer to the led configrations
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin , 
                                 .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @breif   turn the led off
 * @param   led : pointer to the led configrations
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin , 
                                 .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @breif   toggle the led
 * @param   led : pointer to the led configrations
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        pin_config_t pin_obj = { .port = led->port_name, .pin = led->pin , 
                                 .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}

