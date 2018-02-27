#include <stdio.h>
#include "FSM.h"
#include "order_module.h"

void initialize()
{
		if (elev_get_floor_sensor_signal() == 1)
		{
			return; 
		}
		else 
			{
				elev_set_motor_direction(DIRN_DOWN);
			}
		
		while(1)
			{
				if (elev_get_floor_sensor_signal() == 0){
					elev_set_motor_direction(DIRN_STOP);
					return; 
				}
			}


}




FSM(int* state, int button_pressed_matrix[4][3], int stop_button, time_t* open_time, int* last_known_floor, int* last_known_direction);
{
	next_state = order_module(*state,button_pressed_matix, stop_button, *last_known_floor, *last_known_direction); 
	if (next_state == EMERGENCY) 
	{
		*state = EMERGENCY
		elev_set_motor_direction(DIRN_STOP);
 		if( get_floor_signal() != -1)
 			{
 				elev_set_door_open_lamp(1);
 				open_time=time(NULL);
 			}
	}

	else
	{	

		switch(*state)
	 	{
		 	case STANDING_STILL_DOOR_CLOSED:
		 	{
		 		switch(next_state)
		 		{
		 			case ELEVATOR_MOVING_UP: 
		 			{
		 				*state = ELEVATOR_MOVING_UP;	
		 				elev_set_motor_direction(DIRN_UP);
		 				break; 
		 			}
		 			case : 
		 			{
		 				*state = ELEVATOR_MOVING_DOWN;
		 				elev_set_motor_direction(DIRN_DOWN);	
		 				break; 
		 			}
		 			case STANDING_STILL_DOOR_OPEN: 
		 			{
		 				*state = STANDING_STILL_DOOR_OPEN
		 				elev_set_door_open_lamp(1);
		 				open_time=time(NULL);
		 				break; 
		 			}
		 			
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{

		 				break; 
		 			}
		 			default:
		 				break;
		 		}	
		 	}


		 	case STANDING_STILL_DOOR_OPEN:
		 	{
		 		switch(next_state)
				{
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{
		 				*state = STANDING_STILL_DOOR_CLOSED
		 				elev_set_door_open_lamp(0);
		 				break; 
		 			}
		 			
		 			case STANDING_STILL_DOOR_OPEN: 
		 			{
		 				break; 
		 			}
		 			default:
		 				break;
		 		}
		 	}
		 	

		 	case ELEVATOR_MOVING_UP:
		 	{
		 		switch(next_state)
		 		{
		 			
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{
		 				*state = STANDING_STILL_DOOR_CLOSED;
		 				elev_set_motor_direction(DIRN_STOP);	
		 				break; 
		 			}
		 			
		 			case ELEVATOR_MOVING_UP: 
		 			{

		 				break; 
		 			}
		 			default:
		 				break;
		 		}
		 	}


		 	case ELEVATOR_MOVING_DOWN:
		 	{
		 		switch(next_state)
		 		{
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{
		 				*state = STANDING_STILL_DOOR_CLOSED;
		 				elev_set_motor_direction(DIRN_STOP);	
		 				break; 
		 			}
		 			case ELEVATOR_MOVING_DOWN: 
		 			{

		 				break; 
		 			}
		 			default:
		 				break;
		 		}
	 		}


	 		case EMERGENCY:
		 	{
		 		switch(next_state)
		 		{
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{
		 				*state = STANDING_STILL_DOOR_CLOSED;	
		 				break; 
		 			}
		 			case EMERGENCY: 
		 			{

		 				break; 
		 			}
		 			default:
		 				break;
		 		}
	 		}


	 		default:
		 		break;
 		} //Main switch end
 	} //else ended
} //FSM ended
