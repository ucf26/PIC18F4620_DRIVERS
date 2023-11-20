/* 
 * File:   dc_motor.c
 * Author: Yousef Mahmoud
 *
 * Created on November 20, 2023, 3:27 PM
 */


#include"ecu_dc_motor.h"

/**
 * @breif   initialize the motor pins
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK ;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_direction_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        ret = gpio_pin_direction_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}

/**
 * @breif   turn the motor right
 * @param   _dc_motor
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK ;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
 
/**
 * @breif   turn the motor left
 * @param   _dc_motor
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK ;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret;
}

/**
 * @breif   stop the motor 
 * @param   _dc_motor 
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK ;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}





