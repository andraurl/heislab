#pragma once
#include <stdio.h>
#include "FSM.h"
#include "order_module.h"

int** 
get_button_pressed_matrix();

void 
set_button_pressed_matrix(int floor, elev_button_type_t button, int value);

time_t 
get_open_time() const;

void 
set_open_time();

elev_state 
get_state() const;

void 
set_state(elev_state e_state);

elev_state 
get_next_state() const;

void 
set_next_state(elev_state e_state);

int 
get_last_known_floor() const;

void 
set_last_known_floor(int floor);

elev_motor_direction_t 
get_last_known_direction() const;

void 
set_last_known_direction(elev_motor_direction_t dir);

int 
get_stop_button() const;

void 
set_stop_button(int value);