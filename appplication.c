/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */
#include "application.h"
#include "ECU_Layer/Keypad/ecu_keypad.h"

Std_ReturnType ret = E_NOT_OK;




uint8 val;

int main() {
    ecu_layer_initialize();
    
    while(1)
    {
        ret = keypad_get_value(&keypad1, &val);
    }
    return (EXIT_SUCCESS);
}


