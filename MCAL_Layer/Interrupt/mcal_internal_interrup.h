/* 
 * File:   mcal_internal_interrup.h
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:26 AM
 */

#ifndef MCAL_INTERNAL_INTERRUP_H
#define	MCAL_INTERNAL_INTERRUP_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the ADC Module */
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the ADC Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()           (IPR1bits.ADIP = 1)
/* This routine set the ADC Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()            (IPR1bits.ADIP = 0)
#endif

#endif


#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the TIMER0 Module */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the TIMER0 Interrupt Priority to be High priority */
#define TIMER0_HighPrioritySet()           (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 Interrupt Priority to be Low priority */
#define TIMER0_LowPrioritySet()            (INTCON2bits.TMR0IP = 0)
#endif

#endif


/* Section : Data Type Declarations */


/* Section : Functions Declarations */



#endif	/* MCAL_INTERNAL_INTERRUP_H */

