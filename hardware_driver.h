#pragma once

#include <stdio.h>
#include "memory.h"
#include "elev.h"




int 
check_stop_button_change();

void 
change_stop_button_value();

void 
update_button_matrix_and_illuminate_lights();


void 
update_last_known_floor_and_illuminate_floor_indicator();


void 
turn_off_lights_on_floor(int floor);


void
set_motor_direction(elev_motor_direction_t dir);

void
set_door_open_lamp(int value);


int 
check_button_change(int floor, elev_button_type_t button_type);

void
update_stop_button_and_illuminate_light();


void 
change_button_value_to_button_input(int floor, elev_button_type_t button_type );



void
set_lamp(int light_value, elev_button_type_t button, int floor);

int
get_floor_sensor_signal();

int 
get_obstruction_signal();

void
deluminate_all_order_lights(); 

int 
on_floor(); 