#pragma once

#include <stdio.h>
#include "elev.h"




int 
check_stop_button_change(int stop_button);

void 
change_stop_button_value(int*  stop_button);

void 
update_button_matrix_and_illuminate_lights(int button_matrix[4][3]);


void 
update_elev_last_floor_and_illuminate_floor_indicator(int *elev_last_floor);






int 
check_button_change(int button_value, int floor, elev_button_type_t button_type);


void 
change_button_value(int button_matrix[4][3], int floor, elev_button_type_t button_type );



void
set_lamp(int light_value, elev_button_type_t button, int floor);

int
get_floor_signal();