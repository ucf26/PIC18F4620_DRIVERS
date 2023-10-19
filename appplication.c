/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

led_t led1={.port_name = PORTC_INDEX , .pin = GPIO_PIN0 , .led_status = LED_off };
led_t led2={.port_name = PORTC_INDEX , .pin = GPIO_PIN1 , .led_status = LED_off };
led_t led3={.port_name = PORTC_INDEX , .pin = GPIO_PIN2 , .led_status = LED_off };
led_t led4={.port_name = PORTC_INDEX , .pin = GPIO_PIN3 , .led_status = LED_off };

int main() {
    
    app_init();
    
    while(1)
    {
        led_turn_on(&led1);
        led_turn_on(&led2);
        led_turn_on(&led3);
        led_turn_on(&led4);
        __delay_ms(500);
        led_turn_off(&led1);
        led_turn_off(&led2);
        led_turn_off(&led3);
        led_turn_off(&led4);
        __delay_ms(500);
    }
    return (EXIT_SUCCESS);
}

void app_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
}

