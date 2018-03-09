
#pragma once
#include <stdio.h>
#include <time.h>
// #include "time_module.h"
#include "FSM.h"
// #include "elev.h"
#include "hardware_driver.h"
#include "memory.h"

// This module calculates the next state for the elevator. 



int
is_active_order_above();

int
is_active_order_below();

int 
is_active_order_on_floor(int floor);

int 
check_stop_on_current_floor();