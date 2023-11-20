/* 
 * File:   dc_motor.h
 * Author: Yousef Mahmoud
 *
 * Created on November 20, 2023, 3:27 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

 
/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"


/* Section : Macro Declarations */
#define DC_MOTOR_ON_STATUS       0x01U
#define DC_MOTOR_OFF_STATUS      0x00U

#define DC_MOTOR_PIN1      0x00U
#define DC_MOTOR_PIN2      0x01U


/* Section : Macro Functions Declarations */
typedef struct{
    pin_config_t dc_motor_pin[2]; 
}dc_motor_t;

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* DC_MOTOR_H */

