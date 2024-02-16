/* 
 * File:   mcal_interrupt_manager.c
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:27 AM
 */
#include "mcal_interrupt_manager.h"

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0E) && (INTERRUPT_OCCUR == INTCONbits.INT0F)){
        INT0_ISR();
    }
    else { /* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2E) && (INTERRUPT_OCCUR == INTCON3bits.INT2F)){
        INT2_ISR();
    }
    else { /* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )){
        RB4_ISR(); 
    }
    else{ /* Nothing */ }
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else { /* Nothing */}
}

#else 

void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR(); /* External Interrupt 0 */
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR(); /* External Interrupt 1 */
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR(); /* External Interrupt 2 */
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )){
        RB4_ISR(); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )){
        RB5_ISR(); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )){
        RB6_ISR(); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )){
        RB7_ISR(); 
    }
    else{ /* Nothing */ }
}

#endif