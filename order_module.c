
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


	for(int floor = 0; floor < get_last_known_floor(); floor++)
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
	for(int button_type = 0; button_type < 3 ; button_type++)
	{

		if(get_button_pressed_matrix(floor, button_type) == 1)
		{
			return 1; 
		}
	}
	return 0;
}


int 
check_stop_on_current_floor(int floor)
{
	int stop_for_BUTTON_COMMAND = get_button_pressed_matrix(floor, BUTTON_COMMAND) ; 
	int stop_for_BUTTON_CALL_UP = (get_button_pressed_matrix(floor, BUTTON_CALL_UP) && (get_last_known_direction() == DIRN_UP || !is_active_order_below())); 
	int stop_for_BUTTON_CALL_DOWN = (get_button_pressed_matrix(floor, BUTTON_CALL_DOWN) && (get_last_known_direction() == DIRN_DOWN || !is_active_order_above())); 
	
	return (stop_for_BUTTON_COMMAND || stop_for_BUTTON_CALL_DOWN || stop_for_BUTTON_CALL_UP);
}
