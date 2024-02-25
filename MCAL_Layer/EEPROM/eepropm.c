/* 
 * File:   eeprom.c
 * Author: Yousef Mahmoud
 *
 * Created on February 16, 2024, 5:47 PM
 */

#include "eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 address, uint8 byte_of_data)
{
    Std_ReturnType ret = E_OK;
    /* Read The Interrupt Status "Enabled Or Disabled". */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Select the Address Register. */
    EEADRH = (uint8)((address >> 8) &0x03);
    EEADR = (uint8)(address & 0xFF);
    /* Data Memory Value to write. */
    EEDATA = byte_of_data;
    /* Point to Flash Program or Data EEPROM Memory. */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    
    /* Flash Program/Data EEPROM or Configuration Select bit. */
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    /* Flash Program/Data EEPROM Write Enable bit */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    
    /* Disable all interrupts "General Interrupt". */
    INTERRUPT_GlobalInterruptDisable();
    
    /* Write the sequence 0x55 -> 0xAA. */
    EECON2 = 0X55;
    EECON2 = 0xAA;
    
    /* Set WR bit to begin write. */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait to complete the writing. */
    while(EECON1bits.WR);
    
    /* Disable writes. */
    EECON1bits.WREN = INHIBT_WRITE_CYCLES_FLASH_EEPROM;
    
    /* Restore The interrupt status. */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

Std_ReturnType Data_EEPROM_ReadByte(uint16 address, uint8* add_of_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == add_of_data){
        ret = E_NOT_OK;
    }
    else {
        /* Select the Address Register. */
        EEADRH = (uint8)((address >> 8) &0x03);
        EEADR = (uint8)(address & 0xFF);
        /* Point to Flash Program or Data EEPROM Memory. */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        /* Flash Program/Data EEPROM or Configuration Select bit. */
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;

        /* Set RD bit to begin read. */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return Data. */
        *add_of_data = EEDATA;
        ret = E_OK;
    }
    return ret;
}