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


#define _XTAL_FREQ 8000000UL


void app_init(void);

#endif	/* APPLICATION_H */

