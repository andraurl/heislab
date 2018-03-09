#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "memory.h"
#include "hardware_driver.h"
#include "order_module.h"



// This module handles transitions from states to other states, and initializes this new sta



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







