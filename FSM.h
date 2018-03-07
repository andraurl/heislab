#pragma once


#include "elev.h"
#include <time.h>
#include <memory.h>
#include "hardware_driver.h"





void initialize();


typedef enum 
Elevator_state
{
	ERROR = -1,
	STANDING_STILL_DOOR_CLOSED = 0, 
	STANDING_STILL_DOOR_OPEN = 1, 
	ELEVATOR_MOVING_UP = 2,
	ELEVATOR_MOVING_DOWN = 3,	
	EMERGENCY = 4

} elev_state;




void
FSM();

void
set_lights(int light_value, elev_button_type_t button, int floor);




