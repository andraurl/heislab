#pragma once
#include <stdio.h>
#include "time_module.h"
#include <time.h>

#include "elev.h"
#include "FSM.h"


// A memory location for all variables used in this applicaton. Has set() and get() functions for those variables. 

int
get_order_matrix(int floor, elev_button_type_t button); 

void 
set_order_matrix(int floor, elev_button_type_t button, int value);

time_t 
get_door_open_time();

void
reset_door_open_time();

int 
get_state();

void 
set_state(int e_state);

int 
get_next_state();

void 
set_next_state(int e_state);

int 
get_last_known_floor();

void 
set_last_known_floor(int floor);

elev_motor_direction_t 
get_last_known_direction();

void 
set_last_known_direction(elev_motor_direction_t dir);

int 
get_stop_button();

void 
set_stop_button(int value);

void 
delete_orders_from_floor(int floor);

void
delete_all_orders();


