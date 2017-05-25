#ifndef TERRAIN_H
#define TERRAIN_H
#include "textureHandler/textureGenerator.h"
#include <GL/glut.h>
class terrain

{
public:

	void loadHeightfield(const char *filename, const int size);

	void setNumTerrainTexRepeat(int num);

	void setScalingFactor(float xScale, float yScale, float zScale);

	float getHeight(int xpos, int zpos);
	float getUnscaledHeight(int xpos, int zpos);

	unsigned char getHeightColor(int xpos, int zpos);

	int getSize(){ return size; };

	bool inbounds(int xpos, int zpos);

	inline void DoTextureMapping(bool map){ textureMapping = map; }

	bool createProceduralTexture();

	bool addProceduralTexture(char* filename);

	void render();

protected:
	unsigned char *terrainData; //data of the heightfield
	float scaleX; //how much we want to scale by
	float scaleY;
	float scaleZ;
	bool Loaded;
	GLuint texID;
	textureGenerator tex;
	int numTerrainTexRepeat;

private:
	int size; //the size of the heightfield along x and z - power of 2
	bool textureMapping;
};

#endif
