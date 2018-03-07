#include <stdio.h>
#include "FSM.h"
#include "order_module.h"
#include <stdlib.h>


void initialize()
{
		elev_set_motor_direction(DIRN_DOWN);
		while(elev_get_floor_sensor_signal() != 0) {}
		elev_set_motor_direction(DIRN_STOP);	
}




void 
STANDING_STILL_DOOR_OPEN_procedure()
{
	
	set_state(STANDING_STILL_DOOR_OPEN);
	turn_off_lights_on_floor(get_last_known_floor());
	printf("Just turned off light on floor %d\n", get_last_known_floor());
	delete_orders_from_floor(get_last_known_floor());
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	reset_open_time(); 

}

void
STANDING_STILL_DOOR_CLOSED_procedure()
{
	set_state(STANDING_STILL_DOOR_CLOSED);
	elev_set_door_open_lamp(0);
	elev_set_motor_direction(DIRN_STOP);
}


void 
ELEVATOR_MOVING_UP_procedure()
{
	elev_set_motor_direction(DIRN_UP);
	set_last_known_direction(DIRN_UP);
	set_state(ELEVATOR_MOVING_UP);
}

void 
ELEVATOR_MOVING_DOWN_procedure()
{
	set_state(ELEVATOR_MOVING_DOWN);	 			
	elev_set_motor_direction(DIRN_DOWN);
	set_last_known_direction(DIRN_DOWN);
}


void FSM()
{
	elev_state next_state = calculate_next_state(); 

	//printf("Get floor signal: %d\n",get_floor_signal()); 
	//printf("%d\n",next_state);

	if(next_state == ERROR)
	{
		printf("ERROR, next_state error");
		exit(1);
	}
	if (next_state == EMERGENCY) 
	{
		set_state(EMERGENCY); 
		elev_set_motor_direction(DIRN_STOP);
 		if( get_floor_signal() != -1)
 			{
 				elev_set_door_open_lamp(1);
 				reset_open_time(); 

 			}
	}

	else
	{	

		switch(get_state())
	 	{
		 	case STANDING_STILL_DOOR_CLOSED:
		 	{
		 		//printf("case:STANDING_STILL_DOOR_CLOSED");
		 		switch(next_state)
		 		{
		 			case ELEVATOR_MOVING_UP: 
		 			{
		 					
		 				printf("was STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_UP\n" );
		 				ELEVATOR_MOVING_UP_procedure(); 
		 				break; 
		 			}
		 			case ELEVATOR_MOVING_DOWN: 
		 			{
		 				printf("was STANDING_STILL_DOOR_CLOSED- now ELEVATOR_MOVING_DOWN\n" );
		 				ELEVATOR_MOVING_DOWN_procedure(); 

		 				break; 
		 			}
		 			case STANDING_STILL_DOOR_OPEN: 
		 			{
		 				printf("was STANDING_STILL_DOOR_CLOSED- now STANDING_STILL_DOOR_OPEN\n" );
		 				STANDING_STILL_DOOR_OPEN_procedure(); 

		 				break; 
		 			}
		 			
		 			case STANDING_STILL_DOOR_CLOSED: 
		 			{
		 				//printf("was STANDING_STILL_DOOR_CLOSED - now STANDING_STILL_DOOR_CLOSED\n");
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
		 				STANDING_STILL_DOOR_CLOSED_procedure(); 
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
		 				STANDING_STILL_DOOR_OPEN_procedure(); 

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
						STANDING_STILL_DOOR_OPEN_procedure();  
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
		 				printf("was EMERGENCY - now STANDING_STILL_DOOR_CLOSED");
		 				STANDING_STILL_DOOR_CLOSED_procedure(); 
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
