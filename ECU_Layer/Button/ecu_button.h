/* 
 * File:   ecu_button.h
 * Author: Yousef Mahmoud
 *
 * Created on October 25, 2023, 3:10 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    BUTTON_PRESSED = 0, 
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH = 0, 
    BUTTON_ACTIVE_LOW        
}button_active_t;

typedef struct{
    pin_config_t buton;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/* Section : Macro Declarations */

/* Section : Software Interfaces Declarations */

/**
 * @breif   initialize the assigned pin to be input
 * @param   btn : pointer to the Button configrations           @ref button_t
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType button_initialize(const button_t *btn);

/**
 * @breif   read the state of the pin 
 * @param   btn       : pointer to the Button configrations     @ref button_t
 * @param   btn_state : store the button state                  @ref button_state_t         
 * @return  the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);


#endif	/* ECU_BUTTON_H */

