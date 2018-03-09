#include "event_handler.h"

void 
event_handler_loop()
{


	while (1)
	{
	
		update_stop_button_and_illuminate_light(); 


		if (!get_stop_button_signal())
		{
			update_order_matrix_and_illuminate_button_lights(); 
			update_last_known_floor_and_illuminate_floor_indicator();
		}




        state_machine();


        


        // Stop elevator and exit program if there is an obstruction. 
        if (get_obstruction_signal() )
        {
            set_motor_direction(DIRN_STOP);
            break;

        }
		
	}


}
