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




int main() {
    
    ret = led_initialize(&ld1);
    ret = led_initialize(&ld2);
    ret = led_initialize(&ld3);
    ret = led_initialize(&ld4);
    while(1)
    {
        
    }
    return (EXIT_SUCCESS);
}


