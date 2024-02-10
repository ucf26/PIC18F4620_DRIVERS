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

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This macro will enable external interrupt INT0 */
#define EXT_INT0_InterruptEnable() (INTCONbits.INT0E = 1)
/* This macro will disable external interrupt INT0 */
#define EXT_INT0_InterruptDisable() (INTCONbits.INT0E = 0)
/* This macro will clear the flag bit for external interrupt INT0 */
#define EXT_EXT_INT0_InterruptFlagClear (INTCONbits.INT0IE = 0)
/* This macro will set INT0 trigger as Rising Edge */
#define EXT_EXT_INT0_RisingEdgeSet() (INTCON2bits.INTEDG0 = 1)
/* This macro will set INT0 trigger as Falling Edge */
#define EXT_EXT_INT0_FallingEdgeSet() (INTCON2bits.INTEDG0 = 0)


/* This macro will enable external interrupt INT1 */
#define EXT_INT1_InterruptEnable() (INTCON3bits.INT1E = 1)
/* This macro will disable external interrupt INT1 */
#define EXT_INT1_InterruptDisable() (INTCON3bits.INT1E = 0)
/* This macro will clear the flag bit for external interrupt INT1 */
#define EXT_EXT_INT1_InterruptFlagClear (INTCON3bits.INT1F = 0)
/* This macro will set INT1 trigger as Rising Edge */
#define EXT_EXT_INT1_RisingEdgeSet() (INTCON2bits.INTEDG1 = 1)
/* This macro will set INT1 trigger as Falling Edge */
#define EXT_EXT_INT1_FallingEdgeSet() (INTCON2bits.INTEDG1 = 0)


/* This macro will enable external interrupt INT2 */
#define EXT_INT2_InterruptEnable() (INTCON3bits.INT2E = 1)
/* This macro will disable external interrupt INT2 */
#define EXT_INT2_InterruptDisable() (INTCON3bits.INT2E = 0)
/* This macro will clear the flag bit for external interrupt INT2 */
#define EXT_EXT_INT2_InterruptFlagClear (INTCON3bits.INT2F = 0)
/* This macro will set INT2 trigger as Rising Edge */
#define EXT_EXT_INT2_RisingEdgeSet() (INTCON2bits.INTEDG2 = 1)
/* This macro will set INT2 trigger as Falling Edge */
#define EXT_EXT_INT2_FallingEdgeSet() (INTCON2bits.INTEDG2 = 0)



#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This macro will set INT1 external interrupt as high priority */
#define EXT_INT1_HighPrioritySet()  (INTCON3bits.INT1IP = 1)
/* This macro will set INT1 external interrupt as low priority */
#define EXT_INT1_LowPrioritySet()  (INTCON3bits.INT1IP = 0)
/* This macro will set INT2 external interrupt as high priority */
#define EXT_INT2_HighPrioritySet()  (INTCON3bits.INT2IP = 1)
/* This macro will set INT2 external interrupt as los priority */
#define EXT_INT2_LowPrioritySet()  (INTCON3bits.INT2IP = 1)

#endif



#endif


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro will enable external interrupt RBx */
#define EXT_RBx_InterruptEnable()  (INTCONbits.RBIE = 1)
/* This macro will disable external interrupt RBx */
#define EXT_RBx_InterruptEnable()  (INTCONbits.RBIE = 0)
/*This macro will clear the flag bit for external interrupt RBx */
#define EXT_RBx_InterruptFlagClear() (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro will set RBx external interrupt as high priority */
#define EXT_RBx_Priority_High()   (INTCON2bits.RBIP = 1)
/* This macro will set RBx external interrupt as low priority */
#define EXT_RBx_Priority_low()   (INTCON2bits.RBIP = 0)
#endif

#endif
/* Section : Data Type Declarations */

typedef enum{
    INTERRUBT_EXTERNAL_INT0 = 0,
    INTERRUBT_EXTERNAL_INT1, 
    INTERRUBT_EXTERNAL_INT2        
}interrupt_INx_src;

typedef enum{
    INTERRUBT_FALLING_EDGE = 0,
    INTERRUBT_RISING_EDGE        
}interrupt_INx_edge;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INx_edge edge;
    interrupt_INx_src  source;
    interrupt_priority_cfg priority;
}interrupt_INx_t;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/* Section : Functions Declarations */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INx_t *int_obj);
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUP_H */
