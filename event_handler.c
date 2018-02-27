#include "event_handler.h"
#include <stdio.h>
#include <time.h>
#include "FSM.h"



// Hovedløkke


void 
event_handler_loop()
{
	time_t open_time; 
	elev_state state; 
	int stop_button = 0; 
	int last_known_floor = 0;
	int last_known_direction = 1; 
	int button_pressed_matrix[4][3] = 
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};


	elev_set_motor_direction(DIRN_UP);
	//initialize(); 

	
	while (1)
	{
	
		// 1 - Ta inn events fra hardware
		if (check_stop_button_change(stop_button))
		{	
			change_stop_button_value(&stop_button);
			elev_set_stop_lamp(stop_button);
		}

		update_button_matrix_and_illuminate_lights(button_pressed_matrix); 
		
		update_elev_last_floor_and_illuminate_floor_indicator(&elev_last_floor);
		


		//Changes direction on top and bottom floor

		if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }


        FSM(&state, button_pressed_matrix, stop_button, &open_time, &last_known_floor, &last_known_direction);


        // Stop elevator and exit program if the stop button is pressed
    
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }


	



		// 2 - Oppdatere order module

		// 3 - Kalle fsm 

	
	




	}


}
