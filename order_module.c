
#include "order_module.h"




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
	return 0; 
}


int 
check_stop_on_current_floor(int floor)
{
	return (get_button_pressed_matrix(floor, BUTTON_COMMAND) 
			|| (get_button_pressed_matrix(floor, BUTTON_CALL_UP) && (get_last_known_direction() == DIRN_UP || !is_active_order_below()))
			|| (get_button_pressed_matrix(floor, BUTTON_CALL_DOWN) && (get_last_known_direction() == DIRN_DOWN || !is_active_order_above())));
}

int
calculate_next_state()
{

	int current_floor = get_floor_sensor_signal(); // Forsikrer oss om at vi har samme verdi for get_floor_sensor_signal() i løpet av hele funksjonen. 


	if(get_stop_button())
	{
		return EMERGENCY; 
	}

	// STATE IS EMERGENCY - stop button not pressed
	if(get_state() == EMERGENCY) 
	{
		if(on_floor())
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		return STANDING_STILL_DOOR_CLOSED;
	}

	// OPEN DOOR
	if(get_state() == STANDING_STILL_DOOR_OPEN)
	{
		if(get_door_open_time() <= 3)
		{
			return STANDING_STILL_DOOR_OPEN;
		}
		return STANDING_STILL_DOOR_CLOSED;
	}


	// BETWEEN FLOORS
	if(current_floor == -1) //Hvis vi er mellom etasjer
	{

		// if moving between floors - keep moving
		if(get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN) 
		{
			return get_state(); 
		}


		// state() is STANDING_STILL_DOOR_CLOSED.
        // This will only happen after EMERGENCY is called between floors.
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
		return STANDING_STILL_DOOR_CLOSED; 
	}

	
	// ON FLOOR - MOVING
	if ( check_stop_on_current_floor(current_floor) )
	{
		return STANDING_STILL_DOOR_OPEN; 
	}

	if(get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN)
	{	
		return get_state(); 
	}




	// ON FLOOR STANDING STILL - checking for orders
	if(is_active_order_on_floor(get_last_known_floor())) 
	{
		return STANDING_STILL_DOOR_OPEN;
	}

	
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
	

	// NO ORDERS
	return STANDING_STILL_DOOR_CLOSED;
}
