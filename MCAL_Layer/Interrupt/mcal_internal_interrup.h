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


#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the EUSART Module */
#define EUSART_TX_InterruptDisable()         (PIE1bits.TXIE = 0)
/* This routine sets the interrupt enable for the EUSART Module */
#define EUSART_TX_InterruptEnable()          (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the EUSART Interrupt Priority to be High priority */
#define EUSART_TX_HighPrioritySet()           (IPR1bits.TXIP = 1)
/* This routine set the EUSART Interrupt Priority to be Low priority */
#define EUSART_TX_LowPrioritySet()            (IPR1bits.TXIP = 0)
#endif

#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the EUSART Module */
#define EUSART_RX_InterruptDisable()         (PIE1bits.RCIE = 0)
/* This routine sets the interrupt enable for the EUSART Module */
#define EUSART_RX_InterruptEnable()          (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the EUSART Interrupt Priority to be High priority */
#define EUSART_RX_HighPrioritySet()           (IPR1bits.RCIP = 1)
/* This routine set the EUSART Interrupt Priority to be Low priority */
#define EUSART_RX_LowPrioritySet()            (IPR1bits.RCIP = 0)
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

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the SPI Module */
#define MSSP_SPI_InterruptDisable()         (PIE1bits.SSPIE = 0)
/* This routine sets the interrupt enable for the SPI Module */
#define MSSP_SPI_InterruptEnable()          (PIE1bits.SSPIE = 1)
/* This routine clears the interrupt flag for the SPI Module */
#define MSSP_SPI_InterruptFlagClear()       (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the SPI Interrupt Priority to be High priority */
#define MSSP_SPI_HighPrioritySet()           (IPR1bits.SSPIP = 1)
/* This routine set the SPI Interrupt Priority to be Low priority */
#define MSSP_SPI_LowPrioritySet()            (IPR1bits.SSPIP = 0)
#endif

#endif

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the I2C Module */
#define MSSP_I2C_InterruptDisable()               (PIE1bits.SSPIE = 0)
#define MSSP_I2C_Bus_Col_InterruptDisable()       (PIE2bits.BCLIE = 0)
/* This routine sets the interrupt enable for the I2C Module */
#define MSSP_I2C_InterruptEnable()                  (PIE1bits.SSPIE = 1)
#define MSSP_I2C_Bus_Col_InterruptEnable()          (PIE2bits.BCLIE = 1)
/* This routine clears the interrupt flag for the I2C Module */
#define MSSP_I2C_InterruptFlagClear()               (PIR1bits.SSPIF = 0)
#define MSSP_I2C_Bus_Col_InterruptFlagClear()       (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
/* This routine set the I2C Interrupt Priority to be High priority */
#define MSSP_I2C_HighPrioritySet()                   (IPR1bits.SSPIP = 1)
#define MSSP_I2C_Bus_Col_HighPrioritySet()           (IPR2bits.BCLIP = 1)
/* This routine set the I2C Interrupt Priority to be Low priority */
#define MSSP_I2C_LowPrioritySet()                    (IPR1bits.SSPIP = 0)
#define MSSP_I2C_Bus_Col_LowPrioritySet()            (IPR2bits.BCLIP = 0)
#endif

#endif


/* Section : Data Type Declarations */


/* Section : Functions Declarations */



#endif	/* MCAL_INTERNAL_INTERRUP_H */

