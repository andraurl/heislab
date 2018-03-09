#include "memory.h"

static int order_matrix[4][3] = 
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};


static time_t open_time; 

static elev_state state = STANDING_STILL_DOOR_CLOSED;

static int stop_button = 0; 

static int last_known_floor = 0;

static elev_motor_direction_t last_known_direction = DIRN_UP;



int
get_order_matrix(int floor, elev_button_type_t button)
{
	return order_matrix[floor][button];
}


void 
set_order_matrix(int floor, elev_button_type_t button, int value)
{
	order_matrix[floor][button] = value;
}




time_t 
get_door_open_time() 
{
	return (get_time_NULL() - open_time);
}

void
reset_door_open_time()
{
	open_time = get_time_NULL(); 
}





int 
get_state() 
{
	return state;
}


void 
set_state(int e_state) 
{
	state = e_state;
}



int 
get_last_known_floor() 
{
	return last_known_floor;
}

void 
set_last_known_floor(int floor) 
{
	last_known_floor = floor;
}


int 
get_last_known_direction()
{
	return last_known_direction;
}

void 
set_last_known_direction(elev_motor_direction_t dir)  
{
	last_known_direction = dir;
}



int 
get_stop_button()
{
	return stop_button;
}

void 
set_stop_button(int value) 
{
	stop_button = value;
}





void 
delete_all_orders()
{
	for(int floor = 0; floor<4; floor++)
	{
		delete_orders_from_floor(floor);
	}
}


void 
delete_orders_from_floor(int floor)
{
	set_order_matrix(floor, BUTTON_COMMAND, 0);
	set_order_matrix(floor, BUTTON_CALL_UP, 0);
	set_order_matrix(floor, BUTTON_CALL_DOWN, 0);
}
