#pragma once


#include "elev.h"
#include <time.h>
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
	EMERGENCY = 4, 

} elev_state;



enum 
Door_state
{
	DOOR_CLOSED = 0, 
	DOOR_OPEN = 1
};


void
FSM(int* state, int button_pressed_matrix[4][3], int stop_button, time_t* open_time, int* last_known_floor, int* last_known_direction);

void
set_lights(int light_value, elev_button_type_t button, int floor);




