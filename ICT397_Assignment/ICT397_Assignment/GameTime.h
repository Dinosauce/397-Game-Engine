#ifndef GAMETIME_H
#define GAMETIME_H

#include <time.h>

class GameTime{
	public:
		GameTime(){
			last_clock = 0.0;
			last_clock_fps = 0.0;
		};

		double GetElapsedTimeSecond();
		int GetFps();

		clock_t last_clock;
		double delta_time;

		double delta_time_fps;
		clock_t last_clock_fps;
		int frame_count;
		int fps;
};


#endif