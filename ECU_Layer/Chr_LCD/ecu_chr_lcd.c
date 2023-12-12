/* 
 * File:   ecu_chr_lcd.c
 * Author: Yousef Mahmoud
 *
 * Created on December 8, 2023, 4:17 PM
 */

#include "ecu_chr_lcd.h"


static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd,uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column);

/**
 * 
 * @param lcd
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
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
    __delay_ms(20);
    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(5);
    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(150);
    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    
    ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
    ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
    ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
    ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
    ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
    ret = lcd_4bit_send_command(lcd, 0x80);
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
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

/**
 * 
 * @param lcd
 * @param data
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
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

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        while(*str != '\0')
        {
            ret = lcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str != '\0')
        {
            ret = lcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param _chr
 * @param row
 * @param column
 * @param mem_pos
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, const uint8 _chr[], uint8 row, uint8 column, uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
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
    __delay_ms(20);
    ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(5);
    ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(150);
    ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    
    ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
    ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
    ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
    ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
    ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    ret = lcd_8bit_send_command(lcd, 0x80);
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 cnt = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW );
        for(cnt=ZERO_INIT; cnt<8; cnt++)
        {
            ret  = gpio_pin_write_logic(&(lcd->lcd_data[cnt]), (command >> cnt) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 cnt = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(cnt=ZERO_INIT; cnt<8; cnt++)
        {
            ret  = gpio_pin_write_logic(&(lcd->lcd_data[cnt]), (data >> cnt) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @param row
 * @param column
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 data, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        while(*str != '\0')
        {
            ret = lcd_8bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while(*str != '\0')
        {
            ret = lcd_8bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @param _data_command
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
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

/**
 * 
 * @param lcd
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
static Std_ReturnType lcd_4bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;
        case ROW3: ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_4bit_send_command(lcd, (0xD4 + column)); break;
        default : ;
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_8bit_send_command(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_8bit_send_command(lcd, (0xC0 + column)); break;
        case ROW3: ret = lcd_8bit_send_command(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_8bit_send_command(lcd, (0xD4 + column)); break;
        default : ;
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}
