/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"


pin_config_t led_1 = {
    .port = POTRC_INDEX, 
    .pin = GPIO_PIN0 ,
    .direction = GPIO_DIRECTION_OUTPUT, 
    .logic = GPIO_LOW
};

pin_config_t led_2 = {
    .port = POTRC_INDEX, 
    .pin = GPIO_PIN1 ,
    .direction = GPIO_DIRECTION_OUTPUT, 
    .logic = GPIO_LOW
};

pin_config_t led_3 = {
    .port = POTRC_INDEX, 
    .pin = GPIO_PIN2 ,
    .direction = GPIO_DIRECTION_OUTPUT, 
    .logic = GPIO_LOW
};

pin_config_t btn_1 = {
    .port = PORTD_INDEX, 
    .pin = GPIO_PIN0 ,
    .direction = GPIO_DIRECTION_INPUT, 
    .logic = GPIO_LOW
};

Std_ReturnType ret = E_NOT_OK;
deirection_t led_1_st; 
logic_t btn_1_st;

int main() {

    ret = gpio_pin_initialize(&btn_1);
    ret = gpio_pin_initialize(&led_1);
    ret = gpio_pin_initialize(&led_2);
    ret = gpio_pin_initialize(&led_3);
    ret = gpio_pin_write_logic(&led_2, GPIO_HIGH);
    // ret = gpio_pin_direction_initialize(NULL);
    
    while(1){
        ret = gpio_pin_toggle_logic(&led_1);
        
        ret = gpio_pin_toggle_logic(&led_2);
       __delaywdt_ms(500);
        
        /*
        // ret = gpio_pin_read_logic(&btn_1, &btn_1_st);
        if(btn_1_st == GPIO_HIGH){
            ret = gpio_pin_toggle_logic(&led_1);
            ret = gpio_pin_toggle_logic(&led_2);
            
        }
        else {
            ret = gpio_pin_write_logic(&led_1, GPIO_HIGH);
            ret = gpio_pin_write_logic(&led_2, GPIO_HIGH); 
        }
        */
    }
    return (EXIT_SUCCESS);
}

void app_init()
{
    
}

