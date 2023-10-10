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


/* Section : Macro Declarations */
#define BIT_MASK ((uint8)1)
/* Section : Macro Functions Declarations */
#define HWREG8(_x)      (*((volatile uint8 *)(_x)))


#define SET_BIT(REG, BIT_POSITION)      (REG |=  (BIT_MASK << BIT_POSITION))
#define CLEAR_BIT(REG, BIT_POSITION)    (REG &= ~(BIT_MASK << BIT_POSITION))
#define TOGGLE_BIT(REG, BIT_POSITION)   (REG ^=  (BIT_MASK << BIT_POSITION))

#define READ_BIT(REG, BIT_POSITION)     (REG >> BIT_POSITION)

/* Section : Data Type Declarations */
typedef enum{
    LOW = 0, 
    HIGH
}logic_t;

typedef enum{
    OUTPUT = 0, 
    INPUT
}deirection_t;

typedef enum{
    pin0 = 0, 
    pin1,
    pin2, 
    pin3,
    pin4,
    pin5,
    pin6,
    pin7
}pin_index_t;

typedef enum{
    POTRA_INDEX = 0, 
    PORTB_INDEX, 
    POTRC_INDEX,
    PORTD_INDEX, 
    POTRE_INDEX,
}port_index_t;

typedef struct{
    unsigned port : 3;
    unsigned pin : 3;
    unsigned direction : 1;
    unsigned logic : 1;
}pin_config_t;
/* Section : Macro Declarations */

/* Section : Functions Declarations */

#endif	/* HAL_GPIO_H */

