#ifndef WATER_H
#define WATER_H
#include <GL/glut.h>
#include "math/GameMathHelp.h"

class water
{
public:
	water();

	void LoadWater();

	void RenderWater();

	void ShowWater();

	void setPosition(Vector3 pos){ position.x = pos.x; position.y = pos.y; position.z = pos.z; }
	void setScale(Vector3 sca){ scale.x = sca.x; scale.y = sca.y; scale.z = sca.z; }

private:
	GLint  waternum[6];
	Vector3 position;
	Vector3 scale;
};
#endif