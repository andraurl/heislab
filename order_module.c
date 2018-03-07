
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
		if (get_button_pressed_matrix(get_last_known_floor(), button_type) && (get_floor_signal() == get_last_known_floor()))
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
	printf(" -----   Ingen bestillinger  -----  \n");
	return STANDING_STILL_DOOR_CLOSED;


	
}

int
is_active_order_above()
{


	for(int floor = 3; floor > get_last_known_floor();floor--)
	{
		for(int button_type = 0; button_type<3;button_type++)
		{
			if(get_button_pressed_matrix(floor, button_type))
			{
				return 1; 
			}
		}
	}
	return 0; 
}

int
is_active_order_below()
{


	for(int floor = 0; floor < get_last_known_floor() ;floor++)
	{
		for(int button_type = 0; button_type<3;button_type++)
		{
			if(get_button_pressed_matrix(floor, button_type))
			{
				return 1; 
			}
		}
	}
	return 0; 
}


int
calculate_next_state()
{

	int floor = get_floor_signal(); 


	if(get_stop_button())
	{
		return EMERGENCY; 
	}


	// Hold døren åpen i 3 sek.
	if(get_state() == STANDING_STILL_DOOR_OPEN)
	{
		if( time(NULL)- get_open_time() <= 3)
		{
			return STANDING_STILL_DOOR_OPEN;
		}

		//printf("Lukker døren etter 3 sekunder");
		return STANDING_STILL_DOOR_CLOSED;
	}



	if(floor == -1) //Hvis vi er mellom etasjer
	{
		if(get_state() != EMERGENCY) // Fortsett i samme state hvis ikke EMERGENZY
		{
			return get_state();
		} 


		// Hvis EMERGENCY - så sjekk dette - hvilken retning skal en bevege seg etter emergency. 

		if (check_next_direction() == STANDING_STILL_DOOR_OPEN && get_last_known_direction() == DIRN_DOWN)
			return ELEVATOR_MOVING_UP; 
			// Sjekker neste retning etter emergency. 
			// Hvis EMERGENCY, og heisen bevegde seg ned fra last known floor, og får bestilling til last known floor

		if (check_next_direction() == STANDING_STILL_DOOR_OPEN && get_last_known_direction() == DIRN_UP)
			return ELEVATOR_MOVING_DOWN;
			// Sjekker neste retning etter emergency. 
			// Hvis EMERGENCY, og heisen bevegde seg ned fra last known floor, og får bestilling til last known floor

		return check_next_direction(); // Ellers så gå i retningen gitt av check_next_direction()
	}


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
