

#include "time_module.h"


time_t 
get_door_open_time() 
{
	return time(NULL) - get_open_time();
}


void 
reset_open_time() 
{
	set_open_time(time(NULL));
}
