/* 
 * File:   eeprom.h
 * Author: Yousef Mahmoud
 *
 * Created on February 16, 2024, 5:47 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H


/* Section : Includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrup.h"



/* Section : Macro Definitions */
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBT_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1


/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
Std_ReturnType Data_EEPROM_WriteByte(uint16 address, uint8 byte_of_data);
Std_ReturnType Data_EEPROM_ReadByte(uint16 address, uint8* address_of_data);

#endif	/* EEPROM_H */

