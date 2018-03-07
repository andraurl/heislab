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
update_elev_last_floor_and_illuminate_floor_indicator();


void 
turn_off_lights_on_floor(int floor);


int 
check_button_change(int floor, elev_button_type_t button_type);


void 
change_button_value(int floor, elev_button_type_t button_type );

void 
delete_orders_from_floor(int floor);

void
set_lamp(int light_value, elev_button_type_t button, int floor);

int
get_floor_signal();