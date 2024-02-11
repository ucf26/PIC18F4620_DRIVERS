/* 
 * File:   mcal_external_interrup.c
 * Author: Yousef Mahmoud
 *
 * Created on February 8, 2024, 2:26 AM
 */

#include "mcal_external_interrup.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;


static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INx_t *int_obj);


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        /* Disable The External Interrupt. */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear The Interrupt Flag : External Interrupt didn't occur. */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure The Interrupt Priority. */
        ret = Interrupt_INTx_Priority_Init(int_obj);
        /* Configure The Interrupt Edge. */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        /* Configure The Interrupt I/O Pin. */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure The Interrupt Callback. */
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable The External Interrupt. */
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT0:
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT1: 
                EXT_INT1_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                EXT_INT2_InterruptEnable();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT1: 
                EXT_INT1_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                EXT_INT2_InterruptDisable();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT1: 
                if(INTERRUPT_high_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet(); }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet(); }
                else {/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                if(INTERRUPT_high_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet(); }
                else if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet(); }
                else {/* Nothing */}
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT0: 
                if(INTERRUBT_FALLING_EDGE == int_obj->edge){ EXT_EXT_INT0_FallingEdgeSet(); }
                else if(INTERRUBT_RISING_EDGE == int_obj->edge){ EXT_EXT_INT0_RisingEdgeSet(); }
                else {/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT1: 
                if(INTERRUBT_FALLING_EDGE == int_obj->edge){ EXT_EXT_INT1_FallingEdgeSet(); }
                else if(INTERRUBT_RISING_EDGE == int_obj->edge){ EXT_EXT_INT1_RisingEdgeSet(); }
                else {/* Nothing */}
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                if(INTERRUBT_FALLING_EDGE == int_obj->edge){ EXT_EXT_INT2_FallingEdgeSet(); }
                else if(INTERRUBT_RISING_EDGE == int_obj->edge){ EXT_EXT_INT2_RisingEdgeSet(); }
                else {/* Nothing */}
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT0:
                EXT_EXT_INT0_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT1: 
                EXT_EXT_INT1_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                EXT_EXT_INT2_InterruptFlagClear();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}


static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUBT_EXTERNAL_INT0:
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUBT_EXTERNAL_INT1: 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUBT_EXTERNAL_INT2: 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

