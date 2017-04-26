#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <gl/gl.h>
#include <map>
#include <iostream>
using namespace std;

class Texture
{
public:
	Texture();
	//~Texture();

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	bool Load(const char* filename,	const unsigned int texID,GLenum image_format,GLint internal_format,GLint level,GLint border);					

	//free the memory for a texture
	//bool UnloadTexture(const unsigned int texID);

	//set the current texture
	void Bind(const unsigned int texID);

protected:
	
	//Texture(const Texture& tm);
	//Texture& operator=(const Texture& tm);

	//static Texture* m_inst;
	map<unsigned int, GLuint> m_texID;
};

#endif