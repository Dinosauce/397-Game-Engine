#ifndef TERRAIN_H
#define TERRAIN_H
#include "textureHandler/textureGenerator.h"
#include <GL/glut.h>
#include <time.h>
class terrain

{
public:
	terrain();

	void loadHeightfield(const char *filename, const int size);

	void setNumTerrainTexRepeat(int num);

	void setNumDetailMapRepeat(int num);

	void setScalingFactor(float xScale, float yScale, float zScale);

	float getHeight(int xpos, int zpos);
	float getUnscaledHeight(int xpos, int zpos);

	unsigned char getHeightColor(int xpos, int zpos);

	int getSize(){ return size; };

	bool inbounds(int xpos, int zpos);

	inline void DoTextureMapping(bool map){ textureMapping = map; }

	bool createProceduralTexture();

	bool addProceduralTexture(const char* filename);

	bool loadDetailMap(const char* filename);

	bool DoDetailMapping(bool DM);

	void render();

	bool generateHeightfield(const int size, float weight, int iterations);

	float getPointHeight(int x, int z);

	void LoadLightMap(const char *filename, const int size);

	unsigned char getBrightnessAtPoint(int x, int z);

	RGB<float> getLightMapColor();

	bool DoLightMapping(bool LM);

	float getAverageHight(int x, int z);

protected:
	unsigned char *terrainData; //data of the heightfield
	unsigned char *lightmapData;
	float scaleX; //how much we want to scale by
	float scaleY;
	float scaleZ;
	bool Loaded;
	GLuint texID;
	GLuint detailMapTexID;
	textureGenerator tex;
	int numTerrainTexRepeat;
	int numDetailMapRepeat;

private:
	int size; //the size of the heightfield along x and z - power of 2
	int LightMapSize;
	bool textureMapping;
	bool detailMap;
	bool isLightMapped=true;
	RGB<float> lightColor;

	void filterPass(float* dataP, int increment, float weight);

	void addFilter(float* terrainData, float weight);

	void normalise(float* terrainData);

	void  genFaultForm(float* terrainData, int iterations, float weight);

};

#endif
