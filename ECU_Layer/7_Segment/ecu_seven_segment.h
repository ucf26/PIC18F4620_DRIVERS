/* 
 * File:   ecu_seven_segment.h
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 8:21 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE = 0, 
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Functions Declarations */

/**
 * breif   initialize the 7-segment pins 
 * @param  seg pointer to the 7-segment configuration
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType seven_segment_initialize(const segment_t * seg);

/**
 * @breif  display a value on the 7-segment         
 * @param  seg    : pointer to the 7-segment configuration
 * @param  number : value to be shown 
 * @return the status of the function :
 *              (E_OK)     : the function is done successfully
 *              (E_NOT_OK) : the function is not done successfully
 */
Std_ReturnType seven_segment_write_number(const segment_t * seg, uint8 number);



#endif	/* ECU_SEVEN_SEGMENT_H */

