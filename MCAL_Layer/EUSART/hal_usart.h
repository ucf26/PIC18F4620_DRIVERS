/* 
 * File:   hal_usart.h
 * Author: ucf_26
 *
 * Created on April 20, 2024, 5:42 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrup.h"
#include "hal_usart_cfg.h"

/* Section : Macro Definitions */

/* EUSART Enable/Disable */
#define EUSART_MODULE_ENABLE     1
#define EUSART_MODULE_DISABLE    0

/* The EUSART Mode */
#define EUSART_SYNCHRONOUS_MODE             1
#define EUSART_ASYNCHRONOUS_MODE            0
/* EUSART Asynchronous speed mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED      1
#define EUSART_ASYNCHRONOUS_LOW_SPEED       0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN           1
#define EUSART_8BIT_BAUDRATE_GEN            0

/* USART Transmitting Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE       1
#define EUSART_ASYNCHRONOUS_TX_DISABLE      0

/* USART Transmitting Interrupt Enable */
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE       1
#define EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE      0

/* USART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE       1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE      0

/* USART Receiving Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE       1
#define EUSART_ASYNCHRONOUS_RX_DISABLE      0

/* USART Receiving Interrupt Enable */
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE       1
#define EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE      0

/* USART 9-Bit Receive Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE       1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE      0

/* USART Overrun error */
#define EUSART_OVERRUN_ERROR_DETECTED       1
#define EUSART_OVERRUN_ERROR_CLEARED        0
/* USART Framing error */
#define EUSART_FRAMING_ERROR_DETECTED       1
#define EUSART_FRAMING_ERROR_CLEARED        0


/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT        
}baudrate_gen_t;

typedef union {
    struct{
        uint8 usart_error_reserved :6;
        uint8 usart_ferr :1;
        uint8 usart_oerr :1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct {
    uint8 usart_tx_reserved :5;
    uint8 usart_tx_enable :1;
    uint8 usart_tx_interrupt_enable :1;
    uint8 usart_tx_9bit_enable :1;
    interrupt_priority_cfg usart_tx_priority;
}usart_tx_cfg_t;

typedef struct {
    uint8 usart_rx_reserved :5;
    uint8 usart_rx_enable :1;
    uint8 usart_rx_interrupt_enable :1;
    uint8 usart_rx_9bit_enable :1;
    interrupt_priority_cfg usart_rx_priority;
}usart_rx_cfg_t;

typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
    
    void (*EUSART_Tx_DefaultInterruptHandler) (void);
    void (*EUSART_Rx_DefaultInterruptHandler) (void);
    void (*EUSART_FramingErrorHandler) (void);
    void (*EUSART_OverrunErrorHandler) (void);
    
}usart_t;

/* Section : Functions Declarations */

Std_ReturnType EUSART_ASYNC_Init(const usart_t* _eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t* _eusart);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);

Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);

#endif	/* HAL_USART_H */

