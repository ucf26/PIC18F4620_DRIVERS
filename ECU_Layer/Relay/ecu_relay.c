/* 
 * File:   ecu_relay_cfg.c
 * Author: Yousef Mahmoud
 *
 * Created on November 6, 2023, 2:48 PM
 */
#include "ecu_relay.h"

Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = E_OK;
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        ret = gpio_pin_direction_initialize(&pin_obj);
    }
    return ret;
}

Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = E_OK;
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = E_OK;
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}