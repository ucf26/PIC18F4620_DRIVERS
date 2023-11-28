/* 
 * File:   ecu_keypad.c
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 11:33 AM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLS] ={
                                                        {'7', '8', '9', '/'},
                                                        {'4', '5', '6', '*'},
                                                        {'1', '2', '3', '-'},
                                                        {'#', '8', '=', '+'}
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
    Std_ReturnType ret = E_OK ;
    if(NULL == kaypad_obj || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        uint8 current_colmn = ZERO_INIT, current_row = ZERO_INIT;
        uint8 l_row_cnt = ZERO_INIT, current_col_logic = ZERO_INIT;
        
        for(current_row = ZERO_INIT; current_row < KEYPAD_ROWS; current_row++) 
        {
            for(l_row_cnt = ZERO_INIT; l_row_cnt < KEYPAD_ROWS; l_row_cnt++) // off all the rows
            {
                ret = gpio_pin_write_logic(&(kaypad_obj->keypad_row_pins[l_row_cnt]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(kaypad_obj->keypad_row_pins[current_row]), GPIO_HIGH); // activate the current row
            for(current_colmn = ZERO_INIT; current_colmn < KEYPAD_COLS; current_colmn++) // check the columns
            {
                ret = gpio_pin_read_logic(&(kaypad_obj->keypad_column_pins[current_colmn]), &current_col_logic);
                if(GPIO_HIGH == current_col_logic)
                {
                    *value = btn_values[current_row][current_colmn];
                }
            }
        }
    }
    return ret;
}

