#ifndef GAMETIME_H
#define GAMETIME_H

#include <time.h>

class GameTime{
	public:
		GameTime(){};

		double GetElapsedTime();

		clock_t last_clock;
		int frame_count;
		double delta_time;
		int fps;
};


#endif