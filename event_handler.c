#include "event_handler.h"

void 
event_handler_loop()
{


	while (1)
	{
	
		// Ta inn knappetrykk fra hardware. 
		update_stop_button_and_illuminate_light(); 

		// Dersom STOP knappen er trykket inn skal en ikke ta inn bestillinger.
		if (!get_stop_button_signal())
		{
            // Oppdaterer memory med aktive bestillinger. 
            // Setter lys høy dersom aktiv bestilling. 
			update_button_matrix_and_illuminate_lights(); 
			update_last_known_floor_and_illuminate_floor_indicator();
		}

        FSM();


        


        // Stop elevator and exit program if there is an obstruction. 

        
        if (get_obstruction_signal() )
        {
            set_motor_direction(DIRN_STOP);
            break;

        }
		
	}


}
