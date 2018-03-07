
#pragma once
#include <stdio.h>
#include <time.h>
#include "FSM.h"
#include "elev.h"
#include "memory.h"



int
calculate_next_state();


int 
check_next_direction();


int
is_active_order_above();


int
is_active_order_below();