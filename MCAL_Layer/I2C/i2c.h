/* 
 * File:   i2c.h
 * Author: ucf_26
 *
 * Created on June 25, 2024, 1:32 PM
 */

#ifndef I2C_H
#define	I2C_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrup.h"
#include "../Interrupt/mcal_interrupt_config.h"

#include "../GPIO/hal_gpio.h"

/* ----------------- Macro Definitions -----------------*/
/* I2C: Master Or Slave Mode */
#define MSSP_I2C_MASTER_MODE    1
#define MSSP_I2C_SLAVE_MODE     0

/* MSSP I2C Mode */
#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS                     0x06U
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS                    0x07U
#define MSSP_I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE       0x0EU
#define MSSP_I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE      0x0FU
#define MSSP_I2C_MASTER_MODE_DEFINED_CLOCK                   0x08U
#define MSSP_I2C_MASTER_MODE_FIRMWARE_CONTROLLED             0x0Bu

/* Slew Rate Control */
#define I2C_SLEW_RATE_ENABLE     0    /* High-Speed mode (400 kHz) */
#define I2C_SLEW_RATE_DISABLE    1    /* Standard Speed mode (100 kHz) */

/* SMBus Select */
#define I2C_SMBus_ENABLE     1
#define I2C_SMBus_DISABLE    0

/* D/A: last byte Data/Address In Slave mode */
#define I2C_LAST_BYTE_DATA      1
#define I2C_LAST_BYTE_ADDRESS   0

/* P: Stop Detected Or Not */
#define I2C_STOP_BIT_DETECTED       1
#define I2C_STOP_BIT_NOT_DETECTED   0

/* S: Start Detected Or Not */
#define I2C_START_BIT_DETECTED       1
#define I2C_START_BIT_NOT_DETECTED   0

/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE 1
#define I2C_GENERAL_CALL_DISABLE 0

/* Master mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE   1
#define I2C_MASTER_RECEIVE_DISABLE   0

/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE   0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE   1

/*  Acknowledge Data (Master Receive mode only) */
#define I2C_MASTER_SENG_ACK  0
#define I2C_MASTER_SENG_NACK 1

/* ----------------- Macro Functions Declarations -----------------*/
/* Master Synchronous Serial Port Enable bit */
#define MSSP_MODULE_ENABLE()             (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE()            (SSPCON1bits.SSPEN = 0)

/* Slew Rate Control */
#define I2C_SLEW_RATE_ENABLE_CFG()       (SSPSTATbits.SMP = 0)    /* High-Speed mode (400 kHz) */
#define I2C_SLEW_RATE_DISABLE_CFG()      (SSPSTATbits.SMP = 1)    /* Standard Speed mode (100 kHz) */

/* SMBus Select */
#define I2C_SMBus_ENABLE_CFG()           (SSPSTATbits.CKE=1)
#define I2C_SMBus_DISABLE_CFG()          (SSPSTATbits.CKE=0)

/* clock stretch */
#define I2C_CLOCK_STRETCH_ENABLE()   (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()  (SSPCON1bits.CKP = 1)

/* Receive Enable bit (Master mode only) */
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)

/* General Call Enable bit (Slave mode only) */
#define  I2C_GENERAL_CALL_ENABLE_CFG()  (SSPCON2bits.GCEN = 1)
#define  I2C_GENERAL_CALL_DISABLE_CFG() (SSPCON2bits.GCEN = 1)


/* Start Condition Enable */
#define  I2C_MASTER_SEND_START()    (SSPCON2bits.SEN = 1)

/* -----------------Data Type Declarations -----------------*/
typedef struct {
    uint8 i2c_mode_cnfg;
    uint8 i2c_slave_address;
    uint8 i2c_slew_rate:1;
    uint8 i2c_SMbus_control:1;
    uint8 i2c_general_call:1;
    uint8 i2c_mode:1;
    uint8 i2c_master_receive_mode:1;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority;
#endif
    uint8 reserved:1;
}i2c_config_t;

typedef struct{
    uint32 i2c_clock;
    i2c_config_t i2c_cfg;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void);
    void (*I2C_Report_Over_Flow)(void);
    void (*I2C_DefaultInterruptHandler)(void);
#endif    
    
}i2c_t;
/* ----------------- Functions Declarations ----------------- */
Std_ReturnType MSSP_I2C_Init(i2c_t *_config);
Std_ReturnType MSSP_I2C_DeInit(i2c_t *_config);
Std_ReturnType MSSP_I2C_Master_Send_Start(i2c_t *_config);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(i2c_t *_config);
Std_ReturnType MSSP_I2C_Master_Send_Stop(i2c_t *_config);
Std_ReturnType MSSP_I2C_Write(i2c_t *_config, uint8 _data);
Std_ReturnType MSSP_I2C_Read(i2c_t *_config, uint8 *ack, uint8 *_data);



#endif	/* I2C_H */

