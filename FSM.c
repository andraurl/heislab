#include "FSM.h"



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
	deluminate_all_order_lights(); 
	set_motor_direction(DIRN_STOP);

 	if( on_floor() )
 		{
 			set_door_open_lamp(1);
 			reset_door_open_time(); 
		}
}

void FSM()
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
	 				if(is_active_order_on_floor(get_last_known_floor()))  // DENNE SKILLER SEG LITT UT FRA DE ANDRE. DETTE BØR VEL ORDER MODULE TA SEG AV?
	 				{
	 					STANDING_STILL_DOOR_OPEN_procedure();
	 				}
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
