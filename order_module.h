
#pragma once
#include <stdio.h>
#include <time.h>
#include "FSM.h"
#include "elev.h"

int
order_module(int state, int button_pressed_matix[4][3], int stop_button, int last_known_floor, int last_known_direction);


int 
check_next_direction(int state, int button_pressed_matix[4][3],int last_known_floor, int last_known_direction);
