/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/EEPROM/eeprom.h"


int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret= Data_EEPROM_WriteByte(0X3FF ,6);
    ret= Data_EEPROM_WriteByte(0 ,6);
    
    while(1)
    {
    }
    return (EXIT_SUCCESS);
}

