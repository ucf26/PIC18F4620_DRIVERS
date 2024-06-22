/* 
 * File:   hal_spi.h
 * Author: ucf_26
 *
 * Created on June 17, 2024, 9:32 AM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H


/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrup.h"

/* Section : Macro Declarations */

/* Master Synchronous Serial Port Mode Select bits */
#define SPI_MASTER_FOSC_DIV4             0
#define SPI_MASTER_FOSC_DIV16            1
#define SPI_MASTER_FOSC_DIV64            2
#define SPI_MASTER_FOSC_TMR2             3
#define SPI_SLAVE_SS_ENABLE              4
#define SPI_SLAVE_SS_DISABLE             5  

/*  Clock Polarity Select */
#define SPI_IDLE_STATE_HIGH_LEVEL        1      // Idle state for clock is a high level
#define SPI_IDLE_STATE_LOW_LEVEL         0      // Idle state for clock is a low level


/* SPI Master Sampling Mode */
#define SPI_DATA_SAMPLE_MIDDLE           0      // Input data sampled at middle of data output time
#define SPI_DATA_SAMPLE_END              1      // Input data sampled at end of data output time

/* SPI Clock Select */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE      1      // Transmit occurs on transition from active to Idle clock state
#define SPI_TRANSMIT_IDLE_TO_ACTIVE      0      // Transmit occurs on transition from Idle to active clock state

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECTED        1   // The SSPxBUF register is written while it is still transmitting the previous word (must be cleared insoftware)
#define SPI_WRITE_COLLISION_NOT_DETECTED    0   // No collision

/* Receive Overflow Indicator (Overflow can only occur in Slave mode) */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED         1   // A new byte is received while the SSPBUF register is still holding the previous data. In case of overflow, the data in SSPSR is lost
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED     0   // No overflow

/* Buffer Full Status */
#define SPI_BUFF_FULL_RECEIVE_COMPLETE               1 
#define SPI_BUFF_FULL_RECEIVE_NOT_COMPLETE           0


/* Section : Macro Functions Declarations */

/* Master Synchronous Serial Port Enable bit */
#define SPI_ENABLE_MODULE()       (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE_MODULE()      (SSPCON1bits.SSPEN = 0)


/* Section : Data Type Declarations */
typedef struct{
    
}SPI_Control_Config;

typedef struct{
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_Interrupt_Handler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 spi_mode:3;
    uint8 ClockPolarity:1;
    uint8 SampleSelect :1;
    uint8 ClockSelect:1;
}SPI_Config;


/* Section : Functions Declarations */
Std_ReturnType SPI_Init(SPI_Config *_config);
Std_ReturnType SPI_DeInit(SPI_Config *_config);
Std_ReturnType SPI_Send_Byte(SPI_Config *_config, const uint8 _data);
Std_ReturnType SPI_Read_Byte(SPI_Config *_config, uint8 *_data);
Std_ReturnType SPI_Send_Byte_NonBlocking(SPI_Config *_config, const uint8 _data);
Std_ReturnType SPI_Read_Byte_NonBlocking(SPI_Config *_config, uint8 *_data);

#endif	/* HAL_SPI_H */

