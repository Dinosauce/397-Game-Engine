#include "GameTime.h"
#include <iostream>

double GameTime::GetElapsedTime(){
	delta_time = ((double)clock() - (double)last_clock) / CLOCKS_PER_SEC;
	//last_clock = clock();
	frame_count++;

	//reset after t
	
	if (delta_time > 0.1){
		fps = frame_count;
		frame_count = 0;
		last_clock = clock();
	}
	
	return delta_time;
}