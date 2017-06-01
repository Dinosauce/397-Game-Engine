#include "water.h"
#include "../singletons.h"


water::water()
{
	position.x = 1;
	position.y = 1;
	position.z = 1;

	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
}

void water::LoadWater()
{
	waternum[0] = texMan.loadTexture("pictures/water.tga");
}

void water::ShowWater()
{
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			glTranslatef((position.x + 230 * j), position.y, (position.z + 230 * i));
			glScalef(scale.x, scale.y, scale.z);
			RenderWater();
			glPopMatrix();
		}
	}
	

}


void water::RenderWater()
{
	glPushMatrix();
	//glLoadIdentity();
	//glPushAttrib(GL_ENABLE_BIT);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);
	//glDepthRange(1, 1);
	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 0.5);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, waternum[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();


	// Restore enable bits and matrix
	//glPopAttrib();
	//glDepthRange(0, 1);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}