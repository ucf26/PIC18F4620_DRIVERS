/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

button_t btn_high = {
    .buton.port = PORTC_INDEX, 
    .buton.pin = GPIO_PIN2, 
    .buton.direction = GPIO_DIRECTION_INPUT, 
    .buton.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn_low = {
    .buton.port = PORTD_INDEX, 
    .buton.pin = GPIO_PIN0, 
    .buton.direction = GPIO_DIRECTION_INPUT, 
    .buton.logic = GPIO_HIGH, 
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_state = BUTTON_RELEASED
};

led_t led1={.port_name=PORTC_INDEX, .pin=GPIO_PIN0, .led_status=LED_off};
led_t led2={.port_name=PORTC_INDEX, .pin=GPIO_PIN1, .led_status=LED_off};


Std_ReturnType ret = E_NOT_OK;
button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_low_status = BUTTON_RELEASED;


int main() {
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);
    
    
    while(1)
    {
        ret = button_read_state(&btn_high, &btn_high_status);
        ret = button_read_state(&btn_low, &btn_low_status);
        
        if(BUTTON_PRESSED == btn_high_status)
        {
            ret = led_turn_on(&led1);
        }
        else 
        {
            ret = led_turn_off(&led1);
        }
        
        if(BUTTON_PRESSED == btn_low_status)
        {
            ret = led_turn_on(&led2);
        }
        else 
        {
            ret = led_turn_off(&led2);
        }
        
    }
    return (EXIT_SUCCESS);
}

void app_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    
}

