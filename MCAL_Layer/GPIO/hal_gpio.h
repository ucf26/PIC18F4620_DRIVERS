/* 
 * File:   hal_gpio.h
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:53 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
 
/* Section : Includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"


/* Section : Macro Declarations */
#define BIT_MASK                ((uint8)1)
#define PORT_PIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         5

#define GPIO_PIN_PORT_CONFIGRATIONS    CONFIG_ENABLE
#define GPIO_PORT_CONFIGRATIONS        CONFIG_ENABLE

#define PORT_MASK       0xFF

/* Section : Macro Functions Declarations */
#define HWREG8(_x)      (*((volatile uint8 *)(_x)))

#define SET_BIT(REG, BIT_POSITION)      (REG |=  (BIT_MASK << BIT_POSITION))
#define CLEAR_BIT(REG, BIT_POSITION)    (REG &= ~(BIT_MASK << BIT_POSITION))
#define TOGGLE_BIT(REG, BIT_POSITION)   (REG ^=  (BIT_MASK << BIT_POSITION))

#define READ_BIT(REG, BIT_POSITION)     (REG >> BIT_POSITION)

/* Section : Data Type Declarations */
typedef enum{
    GPIO_LOW = 0, 
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0, 
    GPIO_DIRECTION_INPUT
}deirection_t;

typedef enum{
    GPIO_PIN0 = 0, 
    GPIO_PIN1,
    GPIO_PIN2, 
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0, 
    PORTB_INDEX, 
    PORTC_INDEX,
    PORTD_INDEX, 
    PORTE_INDEX,
}port_index_t;

typedef struct{
    uint8 port : 3;         /* @ref port_index_t */
    uint8 pin : 3;          /* @ref pin_index_t */ 
    uint8 direction : 1;    /* @ref deirection_t */
    uint8 logic : 1;        /* @ref logic_t */
}pin_config_t;

/* Section : Functions Declarations */
Std_ReturnType gpio_pin_direction_initialize(pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(pin_config_t *_pin_config, deirection_t *direction_status);
Std_ReturnType gpio_pin_write_logic(pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HAL_GPIO_H */

