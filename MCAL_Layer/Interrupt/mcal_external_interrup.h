/* 
 * File:   mcal_external_interrup.h
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:26 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUP_H
#define	MCAL_EXTERNAL_INTERRUP_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */
/* This macro will enable external interrupt INT0 */
#define EXT_INT0_InterruptEnable() (INTCONbits.INT0E = 1)
/* This macro will disable external interrupt INT0 */
#define EXT_INT0_InterruptEnable() (INTCONbits.INT0E = 0)
/* This macro will clear the flag bit for external interrupt INT0 */
#define EXT_EXT_INT0_InterruptFlagClear (INTCONbits.INT0IE = 0)
/* This macro will set INT0 trigger as Rising Edge */
#define EXT_EXT_INT0_RisingEdgeSet() (INTCON2bits.INTEDG0 = 1)
/* This macro will set INT0 trigger as Falling Edge */
#define EXT_EXT_INT0_FallingEdgeSet() (INTCON2bits.INTEDG0 = 0)


/* This macro will enable external interrupt INT1 */
#define EXT_INT1_InterruptEnable() (INTCON3bits.INT1E = 1)
/* This macro will disable external interrupt INT1 */
#define EXT_INT1_InterruptEnable() (INTCON3bits.INT1E = 0)
/* This macro will clear the flag bit for external interrupt INT1 */
#define EXT_EXT_INT1_InterruptFlagClear (INTCON3bits.INT1F = 0)
/* This macro will set INT1 trigger as Rising Edge */
#define EXT_EXT_INT1_RisingEdgeSet() (INTCON2bits.INTEDG1 = 1)
/* This macro will set INT1 trigger as Falling Edge */
#define EXT_EXT_INT1_FallingEdgeSet() (INTCON2bits.INTEDG1 = 0)


/* This macro will enable external interrupt INT2 */
#define EXT_INT2_InterruptEnable() (INTCON3bits.INT2E = 1)
/* This macro will disable external interrupt INT2 */
#define EXT_INT2_InterruptEnable() (INTCON3bits.INT2E = 0)
/* This macro will clear the flag bit for external interrupt INT2 */
#define EXT_EXT_INT2_InterruptFlagClear (INTCON3bits.INT2F = 0)
/* This macro will set INT2 trigger as Rising Edge */
#define EXT_EXT_INT2_RisingEdgeSet() (INTCON2bits.INTEDG2 = 1)
/* This macro will set INT2 trigger as Falling Edge */
#define EXT_EXT_INT2_FallingEdgeSet() (INTCON2bits.INTEDG2 = 0)

/* Section : Data Type Declarations */


/* Section : Functions Declarations */




#endif	/* MCAL_EXTERNAL_INTERRUP_H */