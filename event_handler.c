#include "event_handler.h"
#include <stdio.h>
#include <time.h>
#include "FSM.h"
#include "memory.h"



// Hovedløkke







void 
event_handler_loop()
{


	while (1)
	{
	
		// 1 - Ta inn events fra hardware
		if (check_stop_button_change())
		{	
			change_stop_button_value();
			elev_set_stop_lamp(get_stop_button());
		}

		update_button_matrix_and_illuminate_lights(); 
		
		update_elev_last_floor_and_illuminate_floor_indicator();
	
		

        FSM();


        


        // Stop elevator and exit program if the stop button is pressed


        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

	}


}
