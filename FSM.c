#include <stdio.h>
#include "FSM.h"
#include "order_module.h"
#include <stdlib.h>


void initialize()
{
		elev_set_motor_direction(DIRN_DOWN);
		
		while(elev_get_floor_sensor_signal() != 0)
		{
			//printf("initialize");	
			
			//printf("moving");
		}
		//printf("lol");
		
		elev_set_motor_direction(DIRN_STOP);	

}




void FSM(int* state, int button_pressed_matrix[4][3], int stop_button, time_t* open_time, int* last_known_floor, int* last_known_direction)
{
	int next_state = calculate_next_state(); 
	//printf("Get floor signal: %d\n",get_floor_signal()); 
	//printf("%d\n",next_state);

	if(next_state == ERROR)
	{
		printf("ERROR, next_state error");
		exit(1);
	}
	if (next_state == EMERGENCY) 
	{
		*state = EMERGENCY;
		elev_set_motor_direction(DIRN_STOP);
 		if( get_floor_signal() != -1)
 			{
 				elev_set_door_open_lamp(1);
 				*open_time=time(NULL);
 			}
	}

	else
	{	

		switch(*state)
	 	{
		 	case STANDING_STILL_DOOR_CLOSED:
		 	{
		 		//printf("case:STANDING_STILL_DOOR_CLOSED");
		 		switch(next_state)
		 		{
		 			case ELEVATOR_MOVING_UP: 
		 			{
		 				*state = ELEVATOR_MOVING_UP;	
		 				printf("was STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_UP\n" );
		 				elev_set_motor_direction(DIRN_UP);
		 				*last_known_direction = DIRN_UP; 
		 				break; 
		 			}
		 			case ELEVATOR_MOVING_DOWN: 
		 			{
		 				*state = ELEVATOR_MOVING_DOWN;
		 				printf("was STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_DOWN\n" );
		 				elev_set_motor_direction(DIRN_DOWN);
		 				*last_known_direction = DIRN_DOWN;	
		 				break; 
		 			}
		 			case STANDING_STILL_DOOR_OPEN: 
		 			{
		 				//
		 				printf("was STANDING_STILL_DOOR_CLOSED- now STANDING_STILL_DOOR_OPEN\n" );
		 				*state = STANDING_STILL_DOOR_OPEN;
		 				turn_off_lights_on_floor(*last_known_floor);
		 				printf("Just turned off light on floor %d\n", *last_known_floor);
		 				delete_orders_from_floor(*last_known_floor,button_pressed_matrix);
		 				elev_set_door_open_lamp(1);
		 				*open_time=time(NULL);
		 				break; 
		 			}
		 			
		 			case STANDING_STILL_DOOR_CLOSED: 

		 			{
		 				//printf("was STANDING_STILL_DOOR_CLOSED - now STANDING_STILL_DOOR_CLOSED\n");
		 				//printf("was STANDING_STILL_DOOR_CLOSED - now STANDING_STILL_DOOR_CLOSED");
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
		 				printf("was STANDING_STILL_DOOR_OPEN- now STANDING_STILL_DOOR_CLOSED\n" );
		 				*state = STANDING_STILL_DOOR_CLOSED;
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
		 				printf("was MVOING UP- now STANDING_STILL_DOOR_OPEN\n" );
		 				*state = STANDING_STILL_DOOR_OPEN;
		 				turn_off_lights_on_floor(*last_known_floor);
		 				printf("Last known floor when turn off lights::: %d\n", *last_known_floor);
		 				delete_orders_from_floor(*last_known_floor, button_pressed_matrix);
		 				elev_set_motor_direction(DIRN_STOP);
		 				elev_set_door_open_lamp(1);
		 				*open_time=time(NULL);
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
		 				printf("was ELEVATOR_MOVING_DOWN- now STANDING_STILL_DOOR_OPEN\n" );
		 				*state = STANDING_STILL_DOOR_OPEN;
		 				turn_off_lights_on_floor(*last_known_floor);
		 				printf("Last known floor when turn off lights::: %d\n", *last_known_floor);
		 				delete_orders_from_floor(*last_known_floor, button_pressed_matrix);
		 				elev_set_motor_direction(DIRN_STOP);
		 				elev_set_door_open_lamp(1);
		 				*open_time=time(NULL);
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
		 		break;
	 		}


	 		default:
		 		break;

 		} //Main switch end
 	} //else ended
} //FSM ended
