#ifndef GAMETIME_H
#define GAMETIME_H

#include <time.h>

/**
* GameTime class - Plentoon Games
* Tracking the time update and frame refresh rate of the game
*/
class GameTime{
	public:
		/**
		* Ctor
		*/
		GameTime(){
			last_clock = 0;
			last_clock_fps = 0;
		};

		/**
		* get the time in second spended for 1 game loop
		* @return time in second
		*/
		double GetElapsedTimeSecond();

		/**
		* get the amount of frame refreshed in 1 second
		* @return frame refresh rate 
		*/
		int GetFps();

		private:
			/// records previous time
			clock_t last_clock;

			/// records the difference between previous time and current time
			double delta_time;

			/// records previous time for fps calculation
			clock_t last_clock_fps;

			/// records the difference between previous time and current time for fps calculation
			double delta_time_fps;
			
			/// counter for fps calculation
			int frame_count;

			/// frame per second
			int fps;
};


#endif