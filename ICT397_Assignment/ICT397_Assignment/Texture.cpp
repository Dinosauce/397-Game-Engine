#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
{
	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

	cout << "call texture";
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}

/*
Texture::~Texture()
{
	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif

	UnloadAllTextures();
	m_inst = 0;
}*/

bool Texture::Load(const char* filename, const unsigned int texID, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	int width, height, n;
	//OpenGL's image ID to map to
	GLuint gl_texID;

	unsigned char *data = stbi_load(filename, &width, &height, &n, 3);

	if (data != NULL)
	{
		//generate an OpenGL texture ID for this texture
		glGenTextures(1, &gl_texID);
		//store the texture ID mapping
		m_texID[texID] = gl_texID;
		//bind to the new texture ID
		glBindTexture(GL_TEXTURE_2D, gl_texID);
		//store the texture data for OpenGL use
		glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, border, image_format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	


	//return success
	return true;
}



void Texture::Bind(const unsigned int texID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texID[texID]);

}

