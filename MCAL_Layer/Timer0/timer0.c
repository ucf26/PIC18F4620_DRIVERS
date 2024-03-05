/* 
 * File:   timer0.h
 * Author: Yousef Mahmoud
 *
 * Created on March 4, 2024, 8:41 PM
 */

#include "timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
#endif

static inline void Timer0_Prescaler_Config(const timer0_t *_timer0);
static inline void Timer0_Mode_Select(const timer0_t *_timer0);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer0);

static uint16 timer0_preload = ZERO_INIT;

Std_ReturnType TIMER0_Init(const timer0_t *_timer0)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Disable The TMR0 */
        TIMER0_MODULE_DISABLE();
        
        /* Configure The TMR0 prescaler  */
        Timer0_Prescaler_Config(_timer0);
        
        /* Configure The TMR0 Mode */
        Timer0_Mode_Select(_timer0);
        
        /* Configure The TMR0 register size */
        Timer0_Register_Size_Config(_timer0);
        
        /* Configure The TMR0 preloded value */
        TMR0L = (uint8)(_timer0->timer0_preloaded_value);
        TMR0H = (_timer0->timer0_preloaded_value) >> 8;  
        timer0_preload = _timer0->timer0_preloaded_value;
        
        /* Configure The Interrupt */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer0->TMR0_InterruptHandler;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _timer0->priority)
        { 
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer0->priority)
        { 
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet(); 
        }
        else { /* Nothing */ }
        
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif

#endif
        
        /* Enable The ADC */
        TIMER0_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TIMER0_DeInit(const timer0_t *_timer0)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else 
    {
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TIMER0_Write_Value(const timer0_t *_timer0, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        TMR0L = (uint8)(_value);
        TMR0H = ((_value)>> 8);  
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TIMER0_Read_Value(const timer0_t *_timer0, uint16* _value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer0)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        *_value = ((uint16)(TMR0L) + (uint16)(TMR0H * 256));
        ret = E_OK;
    }
    return ret;
}


#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TMR0_ISR(void){
    /* The interrupt flag must be cleared using software. */
    TIMER0_InterruptFlagClear();
    TMR0L = (uint8)(timer0_preload);
    TMR0H = ((timer0_preload)>> 8);  
    
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(TMR0_InterruptHandler) { TMR0_InterruptHandler(); }
    else { /* Nothing */}
}
#endif

static inline void Timer0_Prescaler_Config(const timer0_t *_timer0)
{
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer0->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer0->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer0->prescaler_enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else { /* Nothing */}
}

static inline void Timer0_Mode_Select(const timer0_t *_timer0)
{
    if(TIMER0_TIMER_MODE == _timer0->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
        TIMER0_RISING_EDGE_ENABLE();
        
    }
    else if(TIMER0_COUNTER_MODE == _timer0->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        
        if(TIMER0_COUNTER_FALLING_EDGE_CFG == _timer0->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else if(TIMER0_COUNTER_RISING_EDGE_CFG == _timer0->timer0_counter_edge)
        {
            TIMER0_RISING_EDGE_ENABLE();
        }
        else { /* Nothing */}
    }
    else { /* Nothing */}
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer0)
{
    if(TIMER0_8BIT_REGISTER_MODE == _timer0->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer0->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else { /* Nothing */}
}