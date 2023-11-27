/* 
 * File:   ecu_seven_segment.c
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 8:21 AM
 */
#include "ecu_seven_segment.h"


Std_ReturnType seven_segment_initialize(const segment_t * seg){
    Std_ReturnType ret = E_OK ;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_direction_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}

Std_ReturnType seven_segment_write_number(const segment_t * seg, uint8 number){
    Std_ReturnType ret = E_OK ;
    if((NULL == seg) || (number > 9) || (number < 0))
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), (number) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), (number>>1) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), (number>>2) & 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), (number>>3) & 1);
    }
    return ret;
}
