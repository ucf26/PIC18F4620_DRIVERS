/* 
 * File:   mcal_interrupt_manager.h
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:27 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */


/* Section : Functions Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

