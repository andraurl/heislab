#pragma once
#include <stdio.h>
#include "FSM.h"
#include "ordrer_module.h"

time_t get_open_time();

void set_open_time();

elev_state get_state();

void set_state(elev_state e_state);

elev_state get_next_state();

void set_next_state(elev_state e_state);

int get_last_known_floor();

void set_last_known_floor(int floor);

elev_motor_direction_t get_last_known_direction();

void set_last_known_direction(elev_motor_direction_t dir);

int get_stop_button();

void set_stop_button(int value);