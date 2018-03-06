
#include "order_module.h"


int check_next_direction(int state, int button_pressed_matix[4][3],int last_known_floor, int last_known_direction)
{

	for (int button_type = 0; button_type < 3; button_type++)
	{
		if (button_pressed_matix[last_known_floor][button_type] && get_floor_signal() == last_known_floor)
			return STANDING_STILL_DOOR_OPEN;
	}


	// Elevator standing still
	if(state == STANDING_STILL_DOOR_CLOSED && last_known_direction == DIRN_UP)
	{
		for (int floor = 3; floor >= 0; floor--)
		{
			if (floor != last_known_floor)
			{
				for (int button_type = 0; i < 3)
				{
					if (button_pressed_matix[floor][button_type] && floor > last_known_floor)
						return ELEVATOR_MOVING_UP;

					if (button_pressed_matix[floor][button_type] && floor < last_known_floor)
						return ELEVATOR_MOVING_DOWN;
				}
			}
		}
	}

	if(state == STANDING_STILL_DOOR_CLOSED && last_known_direction == DIRN_DOWN)
	{
		for (int floor = 0; floor < 4; floor++)	
		{
			if (floor != last_known_floor)
			{
				for (int button_type = 0; i < 3)
				{
					if (button_pressed_matix[floor][button_type] && floor < last_known_floor)
						return ELEVATOR_MOVING_DOWN;

					if (button_pressed_matix[floor][button_type] && floor > last_known_floor)
						return ELEVATOR_MOVING_UP;
				}
			}	
		}
	return -1; 
	}
}




int
order_module(int state, int button_pressed_matix[4][3], int stop_button, int last_known_floor, int last_known_direction, time_t open_time)
{
	if(stop_button)
	{
		return EMERGENCY; 
	}

	// Hold døren åpen i 3 sek.
	if(state == STANDING_STILL_DOOR_OPEN)
	{
		if( time(NULL)- open_time <= 3)
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		return STANDING_STILL_DOOR_CLOSED;
	}



	if(get_floor_signal() == -1) // Mellom etasjer
	{	// Fortsett i samme state hvis du state != EMERGENZY
		if(state != EMERGENCY)
		{
			return state;
		} 
		// Anta emerganzy bestem retning etter betilling fra antatt etasjeverdi.
		if (check_next_direction() == STANDING_STILL_DOOR_OPEN && last_known_direction == DIRN_DOWN)
			return ELEVATOR_MOVING_UP;

		if (check_next_direction() == STANDING_STILL_DOOR_OPEN && last_known_direction == DIRN_UP)
			return ELEVATOR_MOVING_DOWN;

		return check_next_direction();
	}

	// I en etasje fordi != -1. Stop på etasjen hvis det er forespurt.
	if ( button_pressed_matix[get_floor_signal][BUTTON_COMMAND] 
			|| (button_pressed_matix[get_floor_signal][BUTTON_CALL_UP] && last_known_direction == DIRN_UP)
			|| (button_pressed_matix[get_floor_signal][BUTTON_CALL_DOWN] && last_known_direction == DIRN_DOWN))
	{
		return STANDING_STILL_DOOR_CLOSED;
	}

	// On floor fordu != -1. GJØR: Hvis det er noen som vil noe sett retning til å utføre dette.
	if(check_next_direction() != -1)
	{
		return check_next_direction();
	}

	return STANDING_STILL_DOOR_CLOSED;
}
