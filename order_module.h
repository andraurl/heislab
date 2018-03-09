
#pragma once
#include <stdio.h>
#include <time.h>

#include "hardware_driver.h"
#include "memory.h"

// This module searches for active orders on given floors. 


int
is_active_order_above();

int
is_active_order_below();

int 
is_active_order_on_floor(int floor);

int 
check_stop_on_current_floor();