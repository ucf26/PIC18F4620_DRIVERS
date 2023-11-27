/* 
 * File:   ecu_layer_init.h
 * Author: Yousef Mahmoud
 *
 * Created on November 27, 2023, 8:37 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H



/* Section : Includes */
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_segment.h"
#include "Keypad/ecu_keypad.h"
/* Section : Macro Declarations */


keypad_t keypad1 ={
    .keypad_row_pins[0].port = PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].port = PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].port = PORTC_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].port = PORTC_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    .keypad_column_pins[0].port = PORTC_INDEX,
    .keypad_column_pins[0].pin = GPIO_PIN4,
    .keypad_column_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[0].logic = GPIO_LOW,
    .keypad_column_pins[1].port = PORTC_INDEX,
    .keypad_column_pins[1].pin = GPIO_PIN5,
    .keypad_column_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[1].logic = GPIO_LOW,
    .keypad_column_pins[2].port = PORTC_INDEX,
    .keypad_column_pins[2].pin = GPIO_PIN6,
    .keypad_column_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[2].logic = GPIO_LOW,
    .keypad_column_pins[3].port = PORTC_INDEX,
    .keypad_column_pins[3].pin = GPIO_PIN7,
    .keypad_column_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[3].logic = GPIO_LOW,
};



/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
void app_init(void);

#endif	/* ECU_LAYER_INIT_H */

