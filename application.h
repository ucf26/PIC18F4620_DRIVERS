/* 
 * File:   application.h
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 6:21 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/Button/ecu_button.h"
#include "ECU_Layer/Relay/ecu_relay.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_Layer/7_Segment/ecu_seven_segment.h"


#define _XTAL_FREQ 8000000UL


void app_init(void);

#endif	/* APPLICATION_H */

