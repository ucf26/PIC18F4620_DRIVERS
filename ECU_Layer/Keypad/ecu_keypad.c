/* 
 * File:   ecu_keypad.c
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 11:33 AM
 */

#include "ecu_keypad.h"

static const btn_values [KEYPAD_ROWS][KEYPAD_COLS] ={
                                                        {'7', '8', '9', '/'},
                                                        {'4', '5', '6', '*'},
                                                        {'1', '2', '3', '-'},
                                                        {'#', '8', '=', '+'},
                                                    };



/**
 * @breif  initialize the keypad pins
 * @param  kaypad_obj pointer to the keypad configurations 
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType keypad_initialize(const keypad_t *kaypad_obj){
    Std_ReturnType ret = E_OK ;
    if(NULL == kaypad_obj)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        uint8 rows_cnt = ZERO_INIT, cols_cnt = ZERO_INIT;
        for(rows_cnt = ZERO_INIT; rows_cnt < KEYPAD_ROWS; rows_cnt++)
        {
            ret = gpio_pin_initialize(&(kaypad_obj->keypad_row_pins[rows_cnt]));
        }
        for(cols_cnt = ZERO_INIT; cols_cnt < KEYPAD_COLS; cols_cnt++)
        {
            ret = gpio_pin_direction_initialize(&(kaypad_obj->keypad_column_pins[cols_cnt]));
        }
    }
    return ret;
}

/**
 * @breif  get the value assigned to the pressed button 
 * @param  kaypad_obj  pointer to the keypad configurations 
 * @param  value       pointer to whare the value pressed will be stored 
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType keypad_get_value(const keypad_t *kaypad_obj, uint8 *value){
    
}