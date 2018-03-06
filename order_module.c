
#include "order_module.h"


int check_next_direction(int state, int button_pressed_matix[4][3],int last_known_floor, int last_known_direction)
{

	if(state == ELEVATOR_MOVING_UP || state == ELEVATOR_MOVING_DOWN)
	{	
		return state; 
	}

	for (int button_type = 0; button_type<3; button_type++)
	{
		if (button_pressed_matix[last_known_floor][button_type] && (get_floor_signal() == last_known_floor))
		{
			printf( "Opens door because is at floor where order came from\n");
			return STANDING_STILL_DOOR_OPEN;
		}	
	} //sjekker knappene til etasjen vi er i, og returnerer at heisen skal stå stille dersom den er trykket inn.
	

	if(last_known_direction == DIRN_UP)
	{
		if(is_active_order_above(last_known_floor, button_pressed_matix))
		{
			return ELEVATOR_MOVING_UP;
		}
		if(is_active_order_below(last_known_floor, button_pressed_matix))
		{
			return ELEVATOR_MOVING_DOWN;
		}
	}

	if(last_known_direction == DIRN_DOWN)
	{

		if(is_active_order_below(last_known_floor, button_pressed_matix))
		{
			return ELEVATOR_MOVING_DOWN;
		}

		if(is_active_order_above(last_known_floor, button_pressed_matix))
		{
			return ELEVATOR_MOVING_UP;
		}
		
	}
	printf(" -----   Ingen bestillinger  -----  \n");
	return STANDING_STILL_DOOR_CLOSED;


	
}

int
is_active_order_above(int last_known_floor, int button_pressed_matix[4][3])
{
	for(int floor = 3; floor > last_known_floor;floor--)
	{
		for(int button_type = 0; button_type<3;button_type++)
		{
			if(button_pressed_matix[floor][button_type])
			{
				return 1; 
			}
		}
	}
	return 0; 
}

int
is_active_order_below(int last_known_floor, int button_pressed_matix[4][3])
{
	for(int floor = 0; floor < last_known_floor ;floor++)
	{
		for(int button_type = 0; button_type<3;button_type++)
		{
			if(button_pressed_matix[floor][button_type])
			{
				return 1; 
			}
		}
	}
	return 0; 
}


int
order_module(int state, int button_pressed_matix[4][3], int stop_button, int last_known_floor, int last_known_direction, time_t open_time)
{
	int floor = get_floor_signal(); 
	if(stop_button)
	{
		return EMERGENCY; 
	}

	if(state == STANDING_STILL_DOOR_OPEN)
	{
		if( time(NULL)- open_time <= 3)
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		//printf("Lukker døren etter 3 sekunder");
		return STANDING_STILL_DOOR_CLOSED;
	}



	if(floor == -1) //Hvis vi er mellom etasjer
	{
		if(state != EMERGENCY) //Hvis ikke emergency, bli i current state
		{
			return state;
		} 


		// Hvis EMERGENCY - så sjekk dette - hvilken retning skal en bevege seg etter emergency. 

		if (check_next_direction(state, button_pressed_matix, last_known_floor,last_known_direction) == STANDING_STILL_DOOR_OPEN && last_known_direction == DIRN_DOWN)
			return ELEVATOR_MOVING_UP; 
			// Sjekker neste retning etter emergency. 
			// Hvis EMERGENCY, og heisen bevegde seg ned fra last known floor, og får bestilling til last known floor


		if (check_next_direction(state, button_pressed_matix, last_known_floor,last_known_direction) == STANDING_STILL_DOOR_OPEN && last_known_direction == DIRN_UP)
			return ELEVATOR_MOVING_DOWN;
			// Sjekker neste retning etter emergency. 
			// Hvis EMERGENCY, og heisen bevegde seg ned fra last known floor, og får bestilling til last known floor

		return check_next_direction(state, button_pressed_matix, last_known_floor,last_known_direction); // Ellers så gå i retningen gitt av check_next_direction()
	}


	// Hvis er i en etasje hvor den skal stoppe
	if ( button_pressed_matix[floor][BUTTON_COMMAND] 
			|| (button_pressed_matix[floor][BUTTON_CALL_UP] && (last_known_direction == DIRN_UP || !is_active_order_below(last_known_direction, button_pressed_matix)))
			|| (button_pressed_matix[floor][BUTTON_CALL_DOWN] && (last_known_direction == DIRN_DOWN || !is_active_order_above(last_known_direction, button_pressed_matix)))
			)

	{
		printf("Beveger seg og stopper i en etasje den treffer fordi den skal\n");
		return STANDING_STILL_DOOR_OPEN; 
	}

	return check_next_direction(state, button_pressed_matix, last_known_floor,last_known_direction); 
	

}
