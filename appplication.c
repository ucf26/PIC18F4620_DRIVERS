/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/EEPROM/eeprom.h"

volatile uint8 eeprom_val=0, rd=0;
Std_ReturnType ret = E_NOT_OK;

led_t ld1= {.led_status = GPIO_LOW, .pin=GPIO_PIN0, .port_name=PORTC_INDEX};
led_t ld2= {.led_status = GPIO_LOW, .pin=GPIO_PIN1, .port_name=PORTC_INDEX};
led_t ld3= {.led_status = GPIO_LOW, .pin=GPIO_PIN2, .port_name=PORTC_INDEX};
led_t ld4= {.led_status = GPIO_LOW, .pin=GPIO_PIN3, .port_name=PORTC_INDEX};


void rb4_isr_high(void){
    ret = led_turn_on(&ld1);
}

void rb4_isr_low(void){
    ret = led_turn_on(&ld2);
}

void rb5_isr_high(void){
    ret = led_turn_off(&ld2);
}

void rb5_isr_low(void){
    ret = led_turn_off(&ld1);
}


void rb6_isr_high(void){
    ret = led_turn_on(&ld3);
}

void rb6_isr_low(void){
    ret = led_turn_on(&ld4);
}

void rb7_isr_high(void){
    ret = led_turn_off(&ld3);
}

void rb7_isr_low(void){
    ret = led_turn_off(&ld4);
}



void program2(void){
    led_turn_off(&ld1);
    led_turn_on(&ld2);
}
//
//interrupt_INTx_t int0_obj ={
//    .EXT_InterruptHandler = int0_isr,
//    .edge = INTERRUPT_RISING_EDGE, 
//    .priority = INTERRUPT_HIGH_PRIORITY,
//    .source = INTERRUPT_EXTERNAL_INT0,
//    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
//    .mcu_pin.pin = GPIO_PIN0,
//    .mcu_pin.port = PORTB_INDEX
//};

interrupt_RBx_t rb4_obj = {
    .EXT_InterruptHandler_HIGH = rb4_isr_high,
    .EXT_InterruptHandler_LOW = rb4_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.port = PORTB_INDEX
};

interrupt_RBx_t rb5_obj = {
    .EXT_InterruptHandler_HIGH = rb5_isr_high,
    .EXT_InterruptHandler_LOW = rb5_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.port = PORTB_INDEX
};

interrupt_RBx_t rb6_obj = {
    .EXT_InterruptHandler_HIGH = rb6_isr_high,
    .EXT_InterruptHandler_LOW = rb6_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.port = PORTB_INDEX
};

interrupt_RBx_t rb7_obj = {
    .EXT_InterruptHandler_HIGH = rb7_isr_high,
    .EXT_InterruptHandler_LOW = rb7_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.pin = GPIO_PIN7,
    .mcu_pin.port = PORTB_INDEX
};

int main() {
    
    ret = led_initialize(&ld1);
    ret = led_initialize(&ld2);
    ret = led_initialize(&ld3);
    ret = led_initialize(&ld4);
    ret = Interrupt_RBx_Init(&rb4_obj);
    ret = Interrupt_RBx_Init(&rb5_obj);
    ret = Interrupt_RBx_Init(&rb6_obj);
    ret = Interrupt_RBx_Init(&rb7_obj);
    while(1)
    {
        
    }
    return (EXIT_SUCCESS);
}


