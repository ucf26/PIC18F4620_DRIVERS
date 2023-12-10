/* 
 * File:   ecu_chr_lcd.c
 * Author: Yousef Mahmoud
 *
 * Created on December 8, 2023, 4:17 PM
 */

#include "ecu_chr_lcd.h"


static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd,uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_4bit_t *lcd)l;

Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter<4; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(lcd, (command >> 4));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(lcd, (data >> 4));
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str){
    
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, const uint8 _chr[], uint8 row, uint8 column, uint8 mem_pos){
    
}



Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter<8; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 cnt = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(cnt=ZERO_INIT; cnt<8; cnt++)
        {
            ret  = gpio_pin_write_logic(&(lcd->lcd_data[cnt]), (command >> cnt) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 cnt = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(cnt=ZERO_INIT; cnt<8; cnt++)
        {
            ret  = gpio_pin_write_logic(&(lcd->lcd_data[cnt]), (data >> cnt) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str){
    
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, const uint8 _chr[], uint8 row, uint8 column, uint8 mem_pos){
    
}


static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd,uint8 _data_command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret  = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
        ret &= gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
        ret &= gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
        ret &= gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
    }
    return ret;
}


static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
    }
    return ret;
}