/* 
 * File:   mcal_interrupt_manager.c
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:27 AM
 */
#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

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
    
    /* ============================== PORTB On-Change ==============================*/
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
    && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(0); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) 
    && (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(1); 
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
    && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(0); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) 
    && (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(1); 
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
    && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(0); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) 
    && (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(1); 
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF )
    && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(0); 
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF ) 
    && (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(1); 
    }
    else{ /* Nothing */ }
    
    /* ============================== ADC_Interrupt ==============================*/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();  /* External Interrupt 2 */
    }
    else{ /* Nothing */ }
    
    /* ============================== TMR0_Interrupt ==============================*/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_ENABLE == INTCONbits.TMR0IF)){
        TMR0_ISR();  
    }
    else{ /* Nothing */ }
    
    /* ============================= EUSART_Interrupt =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_ENABLE == PIR1bits.TXIF)){
        EUSART_TX_ISR();  
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_ENABLE == PIR1bits.RCIF)){
        EUSART_RX_ISR();  
    }
    else{ /* Nothing */ }
    
    /* ============================= I2C_Interrupt =============================*/
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_ENABLE == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();  
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_ENABLE == PIR2bits.BCLIF)){
        MSSP_I2C_BC_ISR();  
    }
    else{ /* Nothing */ }
    
    
    
}

#endif