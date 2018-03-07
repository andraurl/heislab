#include "hardware_driver.h"


int
get_floor_signal()
{
	return elev_get_floor_sensor_signal();
}


int 
check_stop_button_change()
{
	return (get_stop_button() != elev_get_stop_signal());

}


void 
change_stop_button_value()
{
	set_stop_button(elev_get_stop_signal());
}


int 
check_button_change(int floor, elev_button_type_t button_type)
{
	return (get_button_pressed_matrix(floor, button_type) != elev_get_button_signal(button_type, floor));
	
}


void 
change_button_value(int floor, elev_button_type_t button_type )
{
	int value = elev_get_button_signal(button_type, floor);
	set_button_pressed_matrix(floor,button_type, value); 
}


void
set_lamp(int light_value, elev_button_type_t button, int floor)
{
	elev_set_button_lamp(button, floor, light_value);
}


void 
update_elev_last_floor_and_illuminate_floor_indicator() 
{
	int current_floor = elev_get_floor_sensor_signal();
	if(current_floor != -1)
	{
		set_last_known_floor(current_floor); 
		elev_set_floor_indicator(current_floor);
	}
}


void 
turn_off_lights_on_floor(int floor)
{
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	if (floor < 3)
	{
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	}
	if (floor > 0)
	{
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	}
	
	
}

void 
delete_orders_from_floor(int floor)
{
	set_button_pressed_matrix(floor, BUTTON_COMMAND, 0);
	set_button_pressed_matrix(floor, BUTTON_CALL_UP, 0);
	set_button_pressed_matrix(floor, BUTTON_CALL_DOWN, 0);

}



void update_button_matrix_and_illuminate_lights()
{
	
	//BUTTON_CALL_UP
	for(int floor = 0; floor<3; floor++)
	{

		if(check_button_change(floor, BUTTON_CALL_UP) && get_button_pressed_matrix(floor, BUTTON_CALL_UP) == 0)
		{
			change_button_value(floor, BUTTON_CALL_UP);
			set_lamp(1, BUTTON_CALL_UP, floor);

		}
	}
	
	//BUTTON_CALL_DOWN
	for(int floor = 1; floor<4; floor++)
	{
		if(check_button_change(floor, BUTTON_CALL_DOWN) && get_button_pressed_matrix(floor, BUTTON_CALL_DOWN) == 0)
		{
			change_button_value(floor, BUTTON_CALL_DOWN);
			set_lamp(1, BUTTON_CALL_DOWN, floor);
		}
	}

	//BUTTON_COMMAND
	for(int floor = 0; floor<4; floor++)
	{
		if(check_button_change(floor, BUTTON_COMMAND) && get_button_pressed_matrix(floor, BUTTON_COMMAND) == 0)
		{
			change_button_value(floor, BUTTON_COMMAND);
			set_lamp(1, BUTTON_COMMAND, floor);
		}
	}
	
}
