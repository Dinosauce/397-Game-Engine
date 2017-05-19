#include "Texture.h"
#include <iostream>

GLuint* Texture2D::m_texture;
int Texture2D::screen_width;
int Texture2D::screen_height;

void Texture2D::LoadRawTexture2D(char* img_src, const int & width, const int & height, const int & texture_no){
	FILE* file;
	unsigned char* image;
	
	// create memory
	image = (GLubyte*)malloc(sizeof(GLubyte) * width * height * 3);
	fopen_s(&file, img_src, "rb");
	// exit program if cannot read image 
	if (file == NULL)
	{
		exit(1);
	}
	fread(image, width * height * 3, 1, file);
	fclose(file);

	// create the texture and set mapping
	glBindTexture(GL_TEXTURE_2D, m_texture[texture_no]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
}

void Texture2D::Clear(){
	m_texture = NULL;
	if (m_texture == NULL){
		delete[] m_texture;
	}
}

void Texture2D::Display2DTexture(const int & width, const int & height, const int & pos_x, const int & pos_y, const int & temp_img_no){
	// clear the color draw b4
	glColor4f(1.0, 1.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screen_width, 0, screen_height);
	glScalef(1, -1, 1);

	// move to centre of screen
	glTranslatef(screen_width / 2 - 256.0, -screen_height / 2 - 256.0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// display exit screen or welcome screen
	glBindTexture(GL_TEXTURE_2D, m_texture[temp_img_no]);
	
	// display image
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(pos_x, pos_y, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(pos_x, pos_y+height, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(pos_x+width, pos_y+height, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(pos_x+width, pos_y, 0.0);
	glEnd();
	
	// Reset Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}