#pragma once

#include <stdio.h>
#include "memory.h"
#include "elev.h"




int 
check_stop_button_change();


// This module communicates directly with the hardware, through the "elev.h" module. 



void 
update_button_matrix_and_illuminate_lights();

void 
update_last_known_floor_and_illuminate_floor_indicator();

void
update_stop_button_and_illuminate_light();


void
set_motor_direction(elev_motor_direction_t dir);

void
set_door_open_lamp(int value);

void
set_lamp(int light_value, elev_button_type_t button, int floor);

int
get_floor_sensor_signal();

int
get_stop_button_signal();

int 
get_obstruction_signal();

void
deluminate_all_order_lights(); 

void 
turn_off_lights_on_floor(int floor);

int 
on_floor(); 