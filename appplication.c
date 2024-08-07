/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"

i2c_t i2c_obj;
uint8 rep;

#define SLAVE_1 0x60
#define SLAVE_2 0x62

void MSSP_I2C_Send_1_Byte(uint8 add, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, add, &rep);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, data, &rep);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}


int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_cfg.i2c_mode = MSSP_I2C_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_mode_cnfg = MSSP_I2C_MASTER_MODE_DEFINED_CLOCK;
    i2c_obj.i2c_cfg.i2c_SMbus_control = I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE;
    i2c_obj.I2C_DefaultInterruptHandler = NULL;
    
    ret = MSSP_I2C_Init(&i2c_obj);
    
    while(1)
    {
        MSSP_I2C_Send_1_Byte(SLAVE_1, 0x55);
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(SLAVE_2, 0x55);
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(SLAVE_1, 0x55);
        __delay_ms(1000);
        MSSP_I2C_Send_1_Byte(SLAVE_2, 0x55);
        __delay_ms(1000);
        
        
    }
    return (EXIT_SUCCESS);
}



