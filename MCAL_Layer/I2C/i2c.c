/* 
 * File:   i2c.h
 * Author: ucf_26
 *
 * Created on June 25, 2024, 1:32 PM
 */
#include "i2c.h"

static inline void MSSP_I2C_Mode_GPIO_Config(void);
static inline void I2C_Master_Mode_Clock_Config(i2c_t *_config);
static inline void MSSP_I2C_Interrupt_Config(i2c_t *_config);

Std_ReturnType MSSP_I2C_Init(i2c_t *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Disable The Module */
        MSSP_MODULE_DISABLE();
        
        /* Select The mode (master/slave) */
        if(MSSP_I2C_MASTER_MODE == _config->i2c_cfg.i2c_mode)
        {
            /* Configure the Buad Rate (master mode) */
            I2C_Master_Mode_Clock_Config(_config);
            
            /* Configure The mode */
            SSPCON1bits.SSPM = _config->i2c_cfg.i2c_mode_cnfg;
            
        }
        else if(MSSP_I2C_SLAVE_MODE == _config->i2c_cfg.i2c_mode)
        {
            /* Configure the general call */
            if(I2C_GENERAL_CALL_ENABLE == _config->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == _config->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else { /* Nothing */ }
            
            /* Configure The mode */
            SSPCON1bits.SSPM = _config->i2c_cfg.i2c_mode_cnfg;
            
            /* clear Write Collision flag */
            SSPCON1bits.WCOL = 0;
            
            /* clear Over Flow flag */
            SSPCON1bits.SSPOV = 0;
            
            /* Release The Clock */
            SSPCON1bits.CKP = 1;
        }
        else { /* Nothing */ }
        
        /* Configure GPIO pins */
        MSSP_I2C_Mode_GPIO_Config();
        
        /* configure slew rate */
        if(I2C_SLEW_RATE_ENABLE == _config->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == _config->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else { /* Nothing */ }
        
        /* Configure SMBus */
        if(I2C_SMBus_ENABLE == _config->i2c_cfg.i2c_SMbus_control)
        {
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == _config->i2c_cfg.i2c_SMbus_control)
        {
            I2C_SMBus_DISABLE_CFG();
        }
        else { /* Nothing */ }
        
        /* Handle Interrupt */
//        MSSP_I2C_Interrupt_Config(_config);
        
        /* Enable The Module */
        MSSP_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeInit(i2c_t *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Disable The Module */
        MSSP_MODULE_DISABLE();
        
        /* Handle Interrupt */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_InterruptEnable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(i2c_t *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Send Start Condition */
        SSPCON2bits.SEN = 1;
        
        /* Wait for completion */
        while(SSPCON2bits.SEN);
        
        /* Clear The Flag */
        PIR1bits.SSPIF = 0;
        
        /* Check if Start Condition Detected */
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret = E_OK;
        }
        else 
        {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(i2c_t *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Send Start Condition */
        SSPCON2bits.SEN = 1;
        
        /* Wait for completion */
        while(SSPCON2bits.SEN);
        
        /* Clear The Flag */
        PIR1bits.SSPIF = 0;
        
        ret = E_OK;
        
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(i2c_t *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Send Stop Condition */
        SSPCON2bits.PEN = 1;
        
        /* Wait for completion */
        while(SSPCON2bits.PEN);
        
        /* Clear The Flag */
        PIR1bits.SSPIF = 0;
        
        /* Check if Stop Condition Detected */
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            ret = E_OK;
        }
        else 
        {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Write(i2c_t *_config, uint8 _data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Read(i2c_t *_config, uint8 *ack, uint8 *_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        
        ret = E_OK;
    }
    return ret;
}


static inline void I2C_Master_Mode_Clock_Config(i2c_t *_config)
{
    /* clock = FOSC/(4 * (SSPADD + 1)) */
    SSPADD = (uint8)(_XTAL_FREQ/(4.0 * (_config->i2c_clock - 1)));
}

static inline void MSSP_I2C_Mode_GPIO_Config(void)
{
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
}


static inline void MSSP_I2C_Interrupt_Config(i2c_t *_config)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_InterruptEnable();
    MSSP_I2C_InterruptFlagClear();
    
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY ==_config->i2c_cfg.mssp_i2c_priority ){
        MSSP_I2C_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY ==_config->i2c_cfg.mssp_i2c_priority){
        MSSP_I2C_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else {/* Nothing */}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
    
#endif
}