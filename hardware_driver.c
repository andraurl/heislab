#include "hardware_driver.h"



void 
change_stop_button_value();

void 
change_button_value_to_button_input(int floor, elev_button_type_t button_type );

int 
check_button_change(int floor, elev_button_type_t button_type);

int 
check_stop_button_change();

void
set_elevator_button_lamp(int light_value, elev_button_type_t button, int floor);





int
get_floor_sensor_signal()
{
	return elev_get_floor_sensor_signal();
}

int
get_stop_button_signal()
{
	return elev_get_stop_signal();
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
	return (get_order_matrix(floor, button_type) != elev_get_button_signal(button_type, floor));

}


void 
change_button_value_to_button_input(int floor, elev_button_type_t button_type )
{
	int value = elev_get_button_signal(button_type, floor);
	set_order_matrix(floor,button_type, value); 
}


void
set_elevator_button_lamp(int light_value, elev_button_type_t button, int floor)
{
	elev_set_button_lamp(button, floor, light_value);
}


void 
update_last_known_floor_and_illuminate_floor_indicator() 
{
	int current_floor = elev_get_floor_sensor_signal();
	if(current_floor != -1)
	{
		set_last_known_floor(current_floor); 
		elev_set_floor_indicator(current_floor);
	}
}

void
update_stop_button_and_illuminate_light()
{
	if (check_stop_button_change())
		{	
			change_stop_button_value();
			elev_set_stop_lamp(get_stop_button());
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
turn_off_all_order_lights()
{
	for(int floor = 0; floor <4; floor++)
	{
		turn_off_lights_on_floor(floor); 
	}
}

void
set_motor_direction(elev_motor_direction_t dir)
{
	elev_set_motor_direction(dir);
}


void
set_door_open_lamp(int value)
{
	elev_set_door_open_lamp(value);
}


int 
get_obstruction_signal()
{
	return elev_get_obstruction_signal(); 
}


int 
on_floor()
{
	return (elev_get_floor_sensor_signal() != -1); 
} 


void update_order_matrix_and_illuminate_button_lights()
{

	int button_value_change;
	
	// 

	//BUTTON_CALL_UP
	for(int floor = 0; floor<3; floor++)
	{

		button_value_change = check_button_change(floor, BUTTON_CALL_UP) && get_order_matrix(floor, BUTTON_CALL_UP) == 0;
		if(button_value_change)
		{
			change_button_value_to_button_input(floor, BUTTON_CALL_UP);
			set_elevator_button_lamp(1, BUTTON_CALL_UP, floor);

		}
	}
	
	//BUTTON_CALL_DOWN
	for(int floor = 1; floor<4; floor++)
	{
		button_value_change = check_button_change(floor, BUTTON_CALL_DOWN) && get_order_matrix(floor, BUTTON_CALL_DOWN) == 0;
		if(button_value_change)
		{
			change_button_value_to_button_input(floor, BUTTON_CALL_DOWN);
			set_elevator_button_lamp(1, BUTTON_CALL_DOWN, floor);
		}
	}

	//BUTTON_COMMAND
	for(int floor = 0; floor<4; floor++)
	{
		button_value_change = check_button_change(floor, BUTTON_COMMAND) && get_order_matrix(floor, BUTTON_COMMAND) == 0;
		if(button_value_change)
		{
			change_button_value_to_button_input(floor, BUTTON_COMMAND);
			set_elevator_button_lamp(1, BUTTON_COMMAND, floor);
		}
	}
	
}
