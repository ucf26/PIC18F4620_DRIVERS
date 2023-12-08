/* 
 * File:   ecu_chr_lcd.h
 * Author: Yousef Mahmoud
 *
 * Created on December 8, 2023, 4:17 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* Section : Includes */
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */

#define _LCD_CLEAR                      0x01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE                 0x06
#define _LCD_CURSOR_OFF_DISPLAY_ON      0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0X08
#define _LCD_CURSOR_ON_BLINK_ON         0X0F
#define _LCD_CURSOR_ON_BLINK_OFF        0X0E
#define _LCD_DIPLAY_SHIFT_RIGHT         0X1C
#define _LCD_DIPLAY_SHIFT_LEFT          0X18
#define _LCD_4BIR_MODE_2_LINE           0X28
#define _LCD_8BIR_MODE_2_LINE           0X38
#define _LCD_CGRAM_START                0X40
#define _LCD_DDRAM_START                0X80


/* Section : Macro Functions Declarations */
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;


/* Section : Data Type Declarations */

/* Section : Functions Declarations */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, const uint8 _chr[]
                                        , uint8 row, uint8 column, uint8 mem_pos);


Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, const uint8 _chr[]
                                        , uint8 row, uint8 column, uint8 mem_pos);

#endif	/* ECU_CHR_LCD_H */

