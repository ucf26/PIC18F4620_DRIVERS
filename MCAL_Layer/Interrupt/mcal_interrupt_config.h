/* 
 * File:   mcal_interrupt_config.h
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:52 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Includes */
#include "pic18f4620.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* Section : Macro Declarations */
#define INTERRUPT_ENABLE                1
#define INTERRUPT_DISABLE               0
#define INTERRUPT_OCCUR                 1
#define INTERRUPT_NOT_OCCUR             0
#define INTERRUPT_PRIORITY_ENABLE       1
#define INTERRUPT_PRIORITY_DISABLE      0

/* Section : Macro Functions Declarations */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro will enable priority levels on interrupts.*/
#define Interrupt_PriorityLevelsEnable()         (RCONbits.IPEN = 1);
/* This macro will disable priority levels on interrupts.*/
#define Interrupt_PriorityLevelsDisable()        (RCONbits.IPEN = 0);
/* This macro will enable global high priority interrups.*/
#define Interrupt_GlobalInterruptHighEnable()    (INTCONbits.GIEH = 1)
/* This macro will disable global high priority interrups.*/
#define Interrupt_GlobalInterruptHighDisable()   (INTCONbits.GIEH = 0)

/* This macro will enable global low priority interrups.*/
#define Interrupt_GlobalInterruptLowEnable()     (INTCONbits.GIEL = 1)
/* This macro will disable global low priority interrups.*/
#define Interrupt_GlobalInterruptLowEnable()     (INTCONbits.GIEL = 0)

#else 
/* This macro will enable peripheral interrupts.*/
#define Interrupt_PeripheralInterruptEnable()    (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts.*/
#define Interrupt_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)

/* This macro will enable global interrupts.*/
#define Interrupt_GlobalInterruptEnable() (INTCONbits.GIE = 1)
/* This macro will disable global interrupts.*/
#define Interrupt_GlobalInterruptDisable() (INTCONbits.GIE = 0)
#endif

/* Section : Data Type Declarations */
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0, 
    INTERRUPT_high_PRIORITY        
}interrupt_priority_cfg;

/* Section : Functions Declarations */



#endif	/* MCAL_INTERRUPT_CONFIG_H */

