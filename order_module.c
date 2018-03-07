
#include "order_module.h"


int 
check_next_direction()
{


	if(get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN)
	{	
		return get_state(); 
	}

	for (int button_type = 0; button_type<3; button_type++)
	{
		if (get_button_pressed_matrix(get_last_known_floor(), button_type) && (get_floor_sensor_signal() == get_last_known_floor()))
		{
			printf( "Opens door because is at floor where order came from\n");

			return STANDING_STILL_DOOR_OPEN;
		}	
	} //sjekker knappene til etasjen vi er i, og returnerer at heisen skal stå stille dersom den er trykket inn.
	

	if(get_last_known_direction() == DIRN_UP)
	{
		if(is_active_order_above())
		{
			return ELEVATOR_MOVING_UP;
		}
		if(is_active_order_below())
		{
			return ELEVATOR_MOVING_DOWN;
		}
	}

	if(get_last_known_direction() == DIRN_DOWN)
	{

		if(is_active_order_below())
		{
			return ELEVATOR_MOVING_DOWN;
		}

		if(is_active_order_above())
		{
			return ELEVATOR_MOVING_UP;
		}
		
	}
	//printf(" -----   Ingen bestillinger  -----  \n");
	return STANDING_STILL_DOOR_CLOSED;


	
}

int
is_active_order_above()
{


	for(int floor = 3; floor > get_last_known_floor();floor--)
	{
		if(is_active_order_on_floor(floor))
		{
			return 1; 
		}
	}
	return 0; 
}

int
is_active_order_below()
{


	for(int floor = 0; floor < get_last_known_floor() ;floor++)
	{
		if(is_active_order_on_floor(floor))
		{
			return 1; 
		}
	}
	return 0; 
}


int 
is_active_order_on_floor(int floor)
{
	for(int button_type = 0; button_type<3;button_type++)
	{
		if(get_button_pressed_matrix(floor, button_type))
		{
			return 1; 
		}
	}
}

int
calculate_next_state()
{

	int floor = get_floor_sensor_signal(); // Forsikrer oss om at vi har samme verdi for get_floor_sensor_signal() i løpet av hele funksjonen. 


	if(get_stop_button())
	{
		return EMERGENCY; 
	}

	if(get_state() == EMERGENCY)
	{
		if(on_floor())
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		return STANDING_STILL_DOOR_CLOSED;
	}

	// Hold døren åpen i 3 sek.
	if(get_state() == STANDING_STILL_DOOR_OPEN)
	{
		if(get_door_open_time() <= 3)
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		//printf("Lukker døren etter 3 sekunder");
		return STANDING_STILL_DOOR_CLOSED;
	}



	if(floor == -1) //Hvis vi er mellom etasjer
	{
		if(get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN)
		{
			return get_state(); 
		}


		// For å komme hit er get_state() == STANDING_STILL_DOOR_CLOSED. 
		if(is_active_order_below())
		{
			return  ELEVATOR_MOVING_DOWN;
		}
		if(is_active_order_above())
		{
			return ELEVATOR_MOVING_UP;
		}

		if(is_active_order_on_floor(get_last_known_floor()))
		{
			if(get_last_known_direction() == DIRN_DOWN)
			{
				return ELEVATOR_MOVING_UP;
			}
			return ELEVATOR_MOVING_DOWN; 
		}
	}

	// Hvis vi er i etasjer: 
	
	// Hvis er i en etasje hvor den skal stoppe
	if ( get_button_pressed_matrix(floor, BUTTON_COMMAND) 
			|| (get_button_pressed_matrix(floor, BUTTON_CALL_UP) && (get_last_known_direction() == DIRN_UP || !is_active_order_below()))
			|| (get_button_pressed_matrix(floor, BUTTON_CALL_DOWN) && (get_last_known_direction() == DIRN_DOWN || !is_active_order_above()))
			)
	{
		printf("Beveger seg og stopper i en etasje den treffer fordi den skal\n");
		return STANDING_STILL_DOOR_OPEN; 
	}

	return check_next_direction();
}
