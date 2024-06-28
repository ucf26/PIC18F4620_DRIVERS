/* 
 * File:   application.h
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 6:21 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrup.h"
#include "MCAL_Layer/Timer0/timer0.h"
#include "MCAL_Layer/EUSART/hal_usart.h"
#include "MCAL_Layer/SPI/hal_spi.h"
#include "MCAL_Layer/I2C/i2c.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
void app_init(void);



#endif	/* APPLICATION_H */

