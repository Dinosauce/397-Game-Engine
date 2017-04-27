#include "GameTime.h"

double GameTime::GetElapsedTimeSecond(){
	delta_time = (double)(clock() - last_clock) / CLOCKS_PER_SEC;
	last_clock = clock();
	
	return delta_time;
}

int GameTime::GetFps(){
	delta_time_fps = (double)(clock() - last_clock_fps) / CLOCKS_PER_SEC;
	frame_count++;

	//reset after 1 s

	if (delta_time_fps > 1.0){
		fps = frame_count;
		frame_count = 0;
		last_clock_fps = clock();
	}


	return fps;
}