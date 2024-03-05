/* 
 * File:   hal_adc.h
 * Author: Yousef Mahmoud
 *
 * Created on February 27, 2024, 2:55 AM
 */

#include "hal_adc.h"


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif


static inline void select_result_format(const adc_cfg_t *_adc);
static inline void configure_voltage_reference(const adc_cfg_t *_adc);
static inline void adc_input_channel_port_cfg(adc_channel_select_t channel);


Std_ReturnType ADC_Init(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Disable The ADC */
        ADC_CONVERTER_DISABLE();
        
        /* Configure The Channel */
        ADCON1bits.PCFG = _adc->adc_channel;
        adc_input_channel_port_cfg(_adc);
        
        /* Configure The Acquisition Time */
        ADCON2bits.ACQT = _adc->acuisition_time;
        
        /* Configure The Result Format */
        select_result_format(_adc);
        
        /* Configure The Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority)
        { 
            INTERRUPT_GlobalInterruptHighEnable();
            ADC_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            ADC_LowPrioritySet(); 
        }
        else { /* Nothing */ }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif
        /* Configure The Conversion Clock */
        ADCON2bits.ADCS = _adc->conversion_clock;
        
        /* Configure The Voltage Reference */
        configure_voltage_reference(_adc);
        
        /* Enable The ADC */
        ADC_CONVERTER_ENABLE();
         
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_DeInit(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Disable The ADC */
        ADC_CONVERTER_DISABLE();
        
        /* Configure The Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#endif
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_SelectChannel(const adc_cfg_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Configure The Channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_cfg(channel);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_StartConversion(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ADC_START_COVERSION();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_IsConversionDone(const adc_cfg_t *_adc, uint8* conversion_status)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else 
    {
        *conversion_status = ADC_COVERSION_STATUS();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_GetConversionResult(const adc_cfg_t *_adc, adc_result_t* conversion_result)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else 
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL) ;
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else 
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL) ;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_cfg_t *_adc, adc_result_t* conversion_result, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Select The A/D Channel */
        ret &= ADC_SelectChannel(_adc, channel);
        /* Start The A/D Channel */
        ret &= ADC_StartConversion(_adc);
        /* Wait until The conversion is Done */
        while(ADCON0bits.GO_nDONE);
        /* Return The Conversion Result */
        ret &= ADC_GetConversionResult(_adc, conversion_result);
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_StartConversion_Interrupt(const adc_cfg_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        /* Select The A/D Channel */
        ret &= ADC_SelectChannel(_adc, channel);
        /* Start The A/D Channel */
        ret &= ADC_StartConversion(_adc);
        ret = E_OK;
    }
    return ret;
}

static inline void adc_input_channel_port_cfg(adc_channel_select_t channel)
{
    switch(channel){
        case ADC_CHANNEL_AN0:  SET_BIT(TRISA, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1:  SET_BIT(TRISA, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2:  SET_BIT(TRISA, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3:  SET_BIT(TRISA, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4:  SET_BIT(TRISA, _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5:  SET_BIT(TRISE, _TRISE_RE0_POSN); break;
        case ADC_CHANNEL_AN6:  SET_BIT(TRISE, _TRISE_RE1_POSN); break;
        case ADC_CHANNEL_AN7:  SET_BIT(TRISE, _TRISE_RE2_POSN); break;
        case ADC_CHANNEL_AN8:  SET_BIT(TRISB, _TRISB_RB2_POSN); break;
        case ADC_CHANNEL_AN9:  SET_BIT(TRISB, _TRISB_RB3_POSN); break;
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_RB1_POSN); break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSN); break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_RB0_POSN); break;
        default: break;
    }
}

static inline void select_result_format(const adc_cfg_t *_adc)
{
    if(ADC_RESULT_RIGHT == _adc->result_format)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else 
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_reference(const adc_cfg_t *_adc)
{
    if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_reference)
    {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else 
    {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
}


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void){
    /* The interrupt flag must be cleared using software. */
    ADC_InterruptFlagClear();
    /* code in MCAL context */
    
    /* Callback function gets called every time this ISR excutes. */
    if(ADC_InterruptHandler) { ADC_InterruptHandler(); }
    else { /* Nothing */}
}
#endif