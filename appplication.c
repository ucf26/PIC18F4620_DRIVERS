/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"



Std_ReturnType ret = E_NOT_OK;

dc_motor_t mot1={
    .dc_motor_pin[0].port=PORTC_INDEX, .dc_motor_pin[0].pin=GPIO_PIN0, 
    .dc_motor_pin[0].direction=GPIO_DIRECTION_OUTPUT, .dc_motor_pin[0].logic=GPIO_HIGH,
    .dc_motor_pin[1].port=PORTC_INDEX, .dc_motor_pin[1].pin=GPIO_PIN1 ,
    .dc_motor_pin[1].direction=GPIO_DIRECTION_OUTPUT ,.dc_motor_pin[1].logic=GPIO_HIGH
};

dc_motor_t mot2={
    .dc_motor_pin[0].port=PORTC_INDEX, .dc_motor_pin[0].pin=GPIO_PIN2, 
    .dc_motor_pin[0].direction=GPIO_DIRECTION_OUTPUT, .dc_motor_pin[0].logic=GPIO_HIGH,
    .dc_motor_pin[1].port=PORTC_INDEX, .dc_motor_pin[1].pin=GPIO_PIN3 ,
    .dc_motor_pin[1].direction=GPIO_DIRECTION_OUTPUT ,.dc_motor_pin[1].logic=GPIO_HIGH
 };


int main() {
    
    app_init();
    
    while(1)
    {
        
        // ret = gpio_pin_write_logic(&pin11, GPIO_HIGH);
        ret = dc_motor_move_right(&mot2);
        ret = dc_motor_move_right(&mot1);
        
        __delay_ms(3000);
        ret = dc_motor_move_left(&mot1);
        ret = dc_motor_move_left(&mot2);
        __delay_ms(3000);
        
        
    }
    return (EXIT_SUCCESS);
}

void app_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    // ret = gpio_pin_direction_initialize(&pin11);
    ret = dc_motor_initialize(&mot1);
    ret = dc_motor_initialize(&mot2);
}

