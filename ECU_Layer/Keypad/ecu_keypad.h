/* 
 * File:   ecu_keypad.h
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 11:33 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define KEYPAD_ROWS     4
#define KEYPAD_COLS     4


/* Section : Macro Functions Declarations */
typedef struct{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_column_pins[KEYPAD_COLS];
}keypad_t;

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
Std_ReturnType keypad_initialize(const keypad_t *kaypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *kaypad_obj, uint8 *value);
#endif	/* ECU_KEYPAD_H */

