#include <stdio.h>

#include "elev.h"
#include "FSM.h"
#include "event_handler.h"

// This module initializes the elevator and starts the event_handler_loop. 


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Make an obstruction to stop elevator and exit program.\n");
    printf("Initializing elevator. Moving to first floor. \n");
    
	initialize(); 
    printf("Done initializing elevator. \n");
    event_handler_loop(); 
    


    return 0;
}
