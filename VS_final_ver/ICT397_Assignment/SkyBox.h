#ifndef SKYBOX_H
#define SKYBOX_H
#include <GL/glut.h>
#include "math/GameMathHelp.h"

class SkyBox
{
public:
	SkyBox();

	void loadSkyBox();

	void RenderSkyBox();

	void ShowSkyBox();

	void setPosition(Vector3 pos){ position.x = pos.x; position.y = pos.y; position.z = pos.z; }
	void setScale(Vector3 sca){ scale.x = sca.x; scale.y = sca.y; scale.z = sca.z; }

private:
	GLint  skybox[6];
	Vector3 position;
	Vector3 scale;
};
#endif