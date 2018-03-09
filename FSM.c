#include "FSM.h"

int
calculate_next_state();

void 
STANDING_STILL_DOOR_OPEN_procedure();

void 
STANDING_STILL_DOOR_CLOSED_procedure();

void 
ELEVATOR_MOVING_UP_procedure();

void 
ELEVATOR_MOVING_DOWN_procedure();

void 
EMERGENCY_procedure();


void initialize()
{
		set_motor_direction(DIRN_DOWN);
		while(get_floor_sensor_signal() != 0) {}
		set_motor_direction(DIRN_STOP);	
}


void 
STANDING_STILL_DOOR_OPEN_procedure()
{
	set_state(STANDING_STILL_DOOR_OPEN);
	turn_off_lights_on_floor(get_last_known_floor());
	delete_orders_from_floor(get_last_known_floor());
	set_motor_direction(DIRN_STOP);
	set_door_open_lamp(1);
	reset_door_open_time(); 
}

void
STANDING_STILL_DOOR_CLOSED_procedure()
{
	set_state(STANDING_STILL_DOOR_CLOSED);
	set_door_open_lamp(0);
	set_motor_direction(DIRN_STOP);
}


void 
ELEVATOR_MOVING_UP_procedure()
{
	set_motor_direction(DIRN_UP);
	set_last_known_direction(DIRN_UP);
	set_state(ELEVATOR_MOVING_UP);
}

void 
ELEVATOR_MOVING_DOWN_procedure()
{
	set_state(ELEVATOR_MOVING_DOWN);	 			
	set_motor_direction(DIRN_DOWN);
	set_last_known_direction(DIRN_DOWN);
}

void 
EMERGENCY_procedure()
{
	set_state(EMERGENCY);

	delete_all_orders(); 
	turn_off_all_order_lights(); 
	set_motor_direction(DIRN_STOP);

 	if( on_floor() )
 		{
 			set_door_open_lamp(1);
 			reset_door_open_time(); 
		}
}

void state_machine()
{	
	elev_state next_state = calculate_next_state(); 

	switch(get_state())
 	{
	 	case STANDING_STILL_DOOR_CLOSED:
	 	{
	 		//printf("case:STANDING_STILL_DOOR_CLOSED");
	 		switch(next_state)
	 		{
	 			case ELEVATOR_MOVING_UP: 
	 			{
	 					
	 				printf("\nwas STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_UP\n" );
	 				ELEVATOR_MOVING_UP_procedure(); 
	 				break; 
	 			}
	 			case ELEVATOR_MOVING_DOWN: 
	 			{
	 				printf("\nwas STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_DOWN\n" );
	 				ELEVATOR_MOVING_DOWN_procedure(); 

	 				break; 
	 			}
	 			case STANDING_STILL_DOOR_OPEN: 
	 			{
	 				printf("\nwas STANDING_STILL_DOOR_CLOSED- now STANDING_STILL_DOOR_OPEN\n" );
	 				STANDING_STILL_DOOR_OPEN_procedure(); 

	 				break; 
	 			}
	 			
	 			case STANDING_STILL_DOOR_CLOSED: 
	 			{
	 				//printf("was STANDING_STILL_DOOR_CLOSED - now STANDING_STILL_DOOR_CLOSED\n");
	 				break; 
	 			}

	 			case EMERGENCY: 
	 			{
	 				printf("\nwas STANDING_STILL_DOOR_CLOSED - now EMERGENCY\n" );
	 				EMERGENCY_procedure();
	 				break; 
	 			}
	 			default:
	 				break;
	 		}
	 		break;	
	 	}


	 	case STANDING_STILL_DOOR_OPEN:
	 	{
	 		switch(next_state)
			{
	 			case STANDING_STILL_DOOR_CLOSED: 
	 			{
	 				printf("\nwas STANDING_STILL_DOOR_OPEN - now STANDING_STILL_DOOR_CLOSED\n" );
	 				STANDING_STILL_DOOR_CLOSED_procedure(); 
	 				break; 
	 			}
	 			case EMERGENCY: 
	 			{
	 				printf("\nwas STANDING_STILL_DOOR_OPEN-  now EMERGENCY\n" );
	 				EMERGENCY_procedure();
	 				break; 
	 			}
	 			case STANDING_STILL_DOOR_OPEN: 
	 			{
                    //printf("Get get_last_known_floor: %d\n", get_last_known_floor());
	 				if(is_active_order_on_floor(get_last_known_floor()))  // DENNE SKILLER SEG LITT UT FRA DE ANDRE. DETTE BØR VEL ORDER MODULE TA SEG AV?
	 				{
                        //printf("There is an active order on floor: %d\n", get_last_known_floor());
	 					STANDING_STILL_DOOR_OPEN_procedure();
	 				}
                    turn_off_lights_on_floor(get_last_known_floor());
	 				break; 
	 			}

	 			default:
	 				break;
	 		}
	 		break;
	 	}
	 	

	 	case ELEVATOR_MOVING_UP:
	 	{
	 		switch(next_state)
	 		{
	 			
	 			case ELEVATOR_MOVING_UP: 
	 			{

	 				break; 
	 			}

	 			case STANDING_STILL_DOOR_OPEN: 
	 			{
	 				printf("\nwas  ELEVATOR_MOVING_UP - now STANDING_STILL_DOOR_OPEN\n" );
	 				STANDING_STILL_DOOR_OPEN_procedure(); 

	 				break; 
	 			}
	 			case EMERGENCY: 
	 			{
	 				printf("\nwas ELEVATOR_MOVING_UP - now EMERGENCY\n" );
	 				EMERGENCY_procedure();
	 				break; 
	 			}
	 			default:
	 				break;
	 		}
	 		break; 
	 	}


	 	case ELEVATOR_MOVING_DOWN:
	 	{
	 		switch(next_state)
	 		{

	 			case ELEVATOR_MOVING_DOWN: 
	 			{

	 				break; 
	 			}
	 			case STANDING_STILL_DOOR_OPEN: 
	 			{
	 				printf("\nwas ELEVATOR_MOVING_DOWN - now STANDING_STILL_DOOR_OPEN\n" );
					STANDING_STILL_DOOR_OPEN_procedure();  
	 				break; 
	 			}
	 			case EMERGENCY: 
	 			{
	 				printf("\nwas ELEVATOR_MOVING_DOWN - now EMERGENCY\n" );
	 				EMERGENCY_procedure();
	 				break; 
	 			}
	 			default:
	 				break;
	 		}
	 		break;
 		}


 		case EMERGENCY:
	 	{
	 		switch(next_state)
	 		{
	 			case STANDING_STILL_DOOR_CLOSED: 
	 			{	
	 				printf("\nwas EMERGENCY - now STANDING_STILL_DOOR_CLOSED\n");
	 				STANDING_STILL_DOOR_CLOSED_procedure(); 
	 				break; 
	 			}
	 			case STANDING_STILL_DOOR_OPEN: 
	 			{	
	 				printf("\nwas EMERGENCY - now STANDING_STILL_DOOR_OPEN\n");
	 				STANDING_STILL_DOOR_OPEN_procedure(); 
	 				break; 
	 			}
	 			case EMERGENCY: 
	 			{
	 				if( on_floor() )
	 				{
	 					reset_door_open_time(); 
	 				}

	 				break; 
	 			}
	 			default:
	 				break;
	 		}
	 		break;
 		}


 		default:
	 		break;

		} //Main switch end
 	
} //FSM ended




int
calculate_next_state()
{

    int current_floor = get_floor_sensor_signal(); // Forsikrer oss om at vi har samme verdi for get_floor_sensor_signal() i løpet av hele funksjonen.

    int 
    HOLD_EMERGENCY
     = (get_stop_button_signal());

    int 
    BREAK_EMERGENCY
     = (get_state() == EMERGENCY && !get_stop_button_signal()); // STATE IS EMERGENCY - stop button not pressed

    int 
    OPEN_DOOR
     = (get_state() == STANDING_STILL_DOOR_OPEN);

    int
    BETWEEN_FLOORS
     = current_floor == -1;

    int 
    ON_FLOOR_MOVING
     = (current_floor != -1 && (get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN));
    
    int 
    ON_FLOOR_STANDING_STILL
     = (get_state() == STANDING_STILL_DOOR_OPEN || get_state() == STANDING_STILL_DOOR_CLOSED);


    if(HOLD_EMERGENCY)
    {
        return EMERGENCY; 
    }

    if(BREAK_EMERGENCY) 
    {
        if( current_floor != -1 )
        {
            return STANDING_STILL_DOOR_OPEN;
        }
        return STANDING_STILL_DOOR_CLOSED;
    }

    if(OPEN_DOOR)
    {
        if(get_door_open_time() <= 3)
        {
            return STANDING_STILL_DOOR_OPEN;
        }
        return STANDING_STILL_DOOR_CLOSED;
    }

    if(BETWEEN_FLOORS)
    {

        // if moving between floors - keep moving
        if(get_state() == ELEVATOR_MOVING_UP || get_state() == ELEVATOR_MOVING_DOWN) 
        {
            return get_state(); 
        }


        // state() is STANDING_STILL_DOOR_CLOSED.
        // This will only happen after EMERGENCY is called between floors.
        if(is_active_order_below())
        {
            return  ELEVATOR_MOVING_DOWN;
        }
        if(is_active_order_above())
        {
            return ELEVATOR_MOVING_UP;
        }

        if(is_active_order_on_floor(get_last_known_floor()))
        {
            if(get_last_known_direction() == DIRN_DOWN)
            {
                return ELEVATOR_MOVING_UP;
            }
            return ELEVATOR_MOVING_DOWN; 
        }
        return STANDING_STILL_DOOR_CLOSED; 
    }

    
    // ON FLOOR - MOVING
    if (ON_FLOOR_MOVING)
    {   
        if (check_stop_on_current_floor(current_floor))
        {
            return STANDING_STILL_DOOR_OPEN; 
        }
        return get_state(); 
    }


    // ON FLOOR STANDING STILL - checking for orders
    if (ON_FLOOR_STANDING_STILL)
    {
        if(is_active_order_on_floor(get_last_known_floor())) 
        {
            return STANDING_STILL_DOOR_OPEN;
        }

        
        if(get_last_known_direction() == DIRN_UP)
        {
            if(is_active_order_above())
            {
                return ELEVATOR_MOVING_UP;
            }
            if(is_active_order_below())
            {
                return ELEVATOR_MOVING_DOWN;
            }
        }

        if(get_last_known_direction() == DIRN_DOWN)
        {

            if(is_active_order_below())
            {
                return ELEVATOR_MOVING_DOWN;
            }

            if(is_active_order_above())
            {
                return ELEVATOR_MOVING_UP;
            }
            
        }
    }

    // NO ORDERS
    return STANDING_STILL_DOOR_CLOSED;
}

