/* 
 * File:   hal_spi.h
 * Author: ucf_26
 *
 * Created on June 17, 2024, 9:32 AM
 */


#include "hal_spi.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*SPI_InterruptHandler)(void) = NULL;
#endif  

static void MSSP_SPI_Interrupt_Init(SPI_Config *_config);
static void MSSP_SPI_MASTER_MODE_GPIO_PIN_CONFIG(void);
static void MSSP_SPI_SLAVE_MODE_GPIO_PIN_CONFIG(SPI_Config *_config);


Std_ReturnType SPI_Init(SPI_Config *_config){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* disable spi module */
        SPI_DISABLE_MODULE();
        
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = _config->spi_mode;
        
        /* configure I/O pins */
        if(SPI_MASTER_FOSC_DIV4  == _config->spi_mode || SPI_MASTER_FOSC_DIV16 ==_config->spi_mode || 
           SPI_MASTER_FOSC_DIV64 == _config->spi_mode || SPI_MASTER_FOSC_TMR2  ==_config->spi_mode)
        {
            MSSP_SPI_MASTER_MODE_GPIO_PIN_CONFIG();
        }
        else if(SPI_SLAVE_SS_ENABLE == _config->spi_mode || SPI_SLAVE_SS_DISABLE == _config->spi_mode)
        {
            MSSP_SPI_SLAVE_MODE_GPIO_PIN_CONFIG(_config);
        }
        
        /* Clock Polarity Select */
        SSPCON1bits.CKP = _config->ClockPolarity;
        
        /* Sample Select */
        SSPSTATbits.SMP = _config->SampleSelect;
        
        /* SPI Clock Edge Select */
        SSPSTATbits.CKE = _config->ClockSelect;   // edge select
        
        /* enable spi module */
        SPI_ENABLE_MODULE();
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_DeInit(SPI_Config *_config){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        /* Disable The Module */
        SPI_DISABLE_MODULE();
        
        /* Disable the interrupt */
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_InterruptDisable();
#endif        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Send_Byte(SPI_Config *_config, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        SSPBUF = _data;
        while(!(PIR1bits.SSPIF));
        PIR1bits.SSPIF=0;
        
//        uint8 temp;
//        temp = SSPBUF;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte(SPI_Config *_config, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        while(!(PIR1bits.SSPIF));
        *_data = SSPBUF;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Send_Byte_NonBlocking(SPI_Config *_config, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte_NonBlocking(SPI_Config *_config, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else {
        
        
        ret = E_OK;
    }
    return ret;
}

static void MSSP_SPI_MASTER_MODE_GPIO_PIN_CONFIG(void)
{
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTC_INDEX, .pin = GPIO_PIN5};
    pin_config_t SPI_SDI = {.direction = GPIO_DIRECTION_INPUT , .port = PORTC_INDEX, .pin = GPIO_PIN4};
    pin_config_t SPI_CLK = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTC_INDEX, .pin = GPIO_PIN3};
    
    ret = gpio_pin_direction_initialize(&SPI_CLK);
    ret = gpio_pin_direction_initialize(&SPI_SDO);
    ret = gpio_pin_direction_initialize(&SPI_SDI);
}


static void MSSP_SPI_SLAVE_MODE_GPIO_PIN_CONFIG(SPI_Config *_config)
{
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTC_INDEX, .pin = GPIO_PIN5};
    pin_config_t SPI_SDI = {.direction = GPIO_DIRECTION_INPUT , .port = PORTC_INDEX, .pin = GPIO_PIN4};
    pin_config_t SPI_CLK = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTC_INDEX, .pin = GPIO_PIN3};
    pin_config_t SPI_SS  = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTA_INDEX, .pin = GPIO_PIN5};
    
    ret = gpio_pin_direction_initialize(&SPI_CLK);
    ret = gpio_pin_direction_initialize(&SPI_SDO);
    ret = gpio_pin_direction_initialize(&SPI_SDI);
    
    if(SPI_SLAVE_SS_ENABLE == _config->spi_mode){
        ret = gpio_pin_direction_initialize(&SPI_SS);
    }
}

static void MSSP_SPI_Interrupt_Init(SPI_Config *_config)
{
    
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptEnable();
    MSSP_SPI_InterruptFlagClear();
    
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==(INTERRUPT_FEATURE_ENABLE)
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY ==_config-> priority ){
        MSSP_SPI_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY ==_config-> priority){
        MSSP_SPI_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else {/* Nothing */}
#else 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
    
#endif
}