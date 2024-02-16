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

static void (*RB4_InterruptHandler)(void) = NULL;
static void (*RB5_InterruptHandler)(void) = NULL;
static void (*RB6_InterruptHandler)(void) = NULL;
static void (*RB7_InterruptHandler)(void) = NULL;

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else {
        /* Disable The External Interrupt. */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear The Interrupt Flag : External Interrupt didn't occur. */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Configure The Interrupt Priority. */
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        
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

void INT0_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_INT0_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(INT0_InterruptHandler) { INT0_InterruptHandler(); }
    else { /* Nothing */}
}

void INT1_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_INT1_InterruptFlagClear();
    
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(INT1_InterruptHandler) { INT1_InterruptHandler(); }
    else { /* Nothing */}
}

void INT2_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_INT2_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(INT2_InterruptHandler) { INT2_InterruptHandler(); }
    else { /* Nothing */}
}

void RB4_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_RBx_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(RB4_InterruptHandler) { RB4_InterruptHandler(); }
    else { /* Nothing */}
}

void RB5_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_RBx_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(RB5_InterruptHandler) { RB5_InterruptHandler(); }
    else { /* Nothing */}
}

void RB6_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_RBx_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(RB6_InterruptHandler) { RB6_InterruptHandler(); }
    else { /* Nothing */}
}

void RB7_ISR(void)
{
    /* The interrupt flag must be cleared using software. */
    EXT_RBx_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(RB6_InterruptHandler) { RB6_InterruptHandler(); }
    else { /* Nothing */}
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
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

Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        /* This macro will enable priority levels on interrupts. */
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            /* This macro will enable high priority global interrupts. */
            INTERRUPT_GlobalInterruptHighEnable();
            /* This routine set the RBx External Interrupt Priority to be High priority */
            EXT_RBx_Priority_High();
        }
        else if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            /* This macro will enable low priority global interrupts. */
            INTERRUPT_GlobalInterruptLowEnable();
            /* This routine set the RBx External Interrupt Priority to be Low priority */
            EXT_RBx_Priority_Low();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif   
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        switch(int_obj->mcu_pin.pin)
        {
            case (GPIO_PIN4):
                RB4_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case (GPIO_PIN5):
                RB5_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case (GPIO_PIN6):
                RB6_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case (GPIO_PIN7):
                RB7_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            default:
                ret = E_NOT_OK;
        }
        EXT_RBx_InterruptEnable();
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj)
{
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

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
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
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                EXT_INT1_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2: 
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
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT0_RisingEdgeSet(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdgeSet(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_RisingEdgeSet(); }
                else{ /* Nothing */ }
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the MCU Pin for INTx with the needed configurations */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        
    }
    return ret;
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT0 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT1 */
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT2 */
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}