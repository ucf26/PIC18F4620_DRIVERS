/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;

segment_t seg1={
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
};
int main() {
    app_init();
    int num=1;
    while(1)
    {
        ret = seven_segment_write_number(&seg1, num);
        __delay_ms(50);
        num++;
        
        if(num==10)num=0;
    }
    return (EXIT_SUCCESS);
}
void app_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = seven_segment_initialize(&seg1);
    // ret = gpio_port_direction_initialize(PORTD_INDEX, 0x00);
}

