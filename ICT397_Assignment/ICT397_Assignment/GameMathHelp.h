#ifndef GAMEMATHHELP_H
#define GAMEMATHHELP_H

#include <math.h>

#define _PI 3.14159265359f
#define _TWO_PI 6.28318530717f

class GameMathHelp{
	public:

		// Converts degrees to radians
		static float ToRadians(float degrees);

		// Restricts a value to be within a specified range
		static float Clamp(float value, float min, float max);

		// Float modulo function (remainder has same sign as the divisor)
		static float FloatMod(float var1, float var2);

		// Reduces a given angle to a value between pi and -pi
		static float WrapAngle(float angle);
};

inline float GameMathHelp::ToRadians(float degrees){
	return (degrees * _PI / 180);
}

inline float GameMathHelp::Clamp(float value, float min, float max){
	if (value < min){
		return min;
	}
	if (value > max){
		return max;
	}
	return value;
}

inline float GameMathHelp::FloatMod(float var1, float var2){
	if (var2 == 0.0)
		return var1;

	float rem = var1 - var2 * floor(var1/var2);

	// Handle boundary cases resulted from float cut off
	if (var2 > 0){
		if (rem >= var2)
			return 0;

		if (rem < 0){
			if ((var2 + rem) == var2)
				return 0;
			else
				return (var2 + rem);
		}
	}

	else{
		if (rem <= var2)
			return 0;

		if (rem > 0){
			if ((var2 + rem) == var2)
				return 0;
			else
				return (var2 + rem);
		}
	}

	return rem;
}

inline float GameMathHelp::WrapAngle(float angle){
	return (FloatMod((angle + _PI), _TWO_PI) - _PI);
}

#endif