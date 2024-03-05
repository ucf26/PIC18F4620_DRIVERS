/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/Timer0/timer0.h"


led_t ld1= {.led_status = GPIO_LOW, .pin=GPIO_PIN0, .port_name=PORTC_INDEX};

volatile uint16 tmr0_fl = 0, cnt=0;

void timer0_defaulthandler(void){
    led_turn_toggle(&ld1);
}

timer0_t timer0_obj={
    .TMR0_InterruptHandler = timer0_defaulthandler,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_8,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_preloaded_value = 3036,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .timer0_counter_edge = TIMER0_COUNTER_RISING_EDGE_CFG
};

timer0_t timer0_counter_obj={
    .TMR0_InterruptHandler = timer0_defaulthandler,
    .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .timer0_preloaded_value = 0,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .timer0_counter_edge = TIMER0_COUNTER_RISING_EDGE_CFG
};


int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = TIMER0_Init(&timer0_obj);
    ret = led_initialize(&ld1);
    
    while(1)
    {
        
      //  ret = TIMER0_Read_Value(&timer0_counter_obj, &cnt);
    }
    return (EXIT_SUCCESS);
}



