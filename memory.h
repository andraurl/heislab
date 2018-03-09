#pragma once
#include <stdio.h>
#include "time_module.h"
#include <time.h>
#include "elev.h" // for elev_button_type_t
#include "FSM.h"
// #include "order_module.h"


int
get_button_pressed_matrix(int floor, elev_button_type_t button); 

void 
set_button_pressed_matrix(int floor, elev_button_type_t button, int value);





time_t 
get_door_open_time();

void
reset_door_open_time();




int 
get_state();

void 
set_state(int e_state);

// A memory location for all variables used in this applicaton. Has set() and get() functions for those variables. 

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