// Jayden Grant - 32670206

#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <map>

class Terrain
{
  public:
	  //Texture tex1;

	Terrain();
	~Terrain();

	bool loadHeightfield(char *filename, const int size);
	/**
	 * Generates a normalized heightmap of size size*size.
	 * @param weight - Alters the smoothness of the terrain (0 rough - 1 smooth)
	 * @param iterations - number of faultlines used to generate heightfield.
	 */
	bool generateHeightfield(const int size, float weight = 0.7f, int iterations = 16);

	void setTexture(int id);
	void dispTexture();
	void dispTexture(bool displayTextures);

	void setScale(float scale);
	void setScale(float x, float y, float z);

	/**
	 *	Returns the interpolated height at x, y. (Assuming Terrain positioned at 0,0)
	 */
	float getHeight(float x, float z);

	int getTexID(){ return texID; };
	int getSize(){ return size; };
	int getScaleX(){ return scaleX; };
	int getScaleY(){ return scaleY; };
	int getScaleZ(){ return scaleZ; };

	/** Sets a texture and the maximum height at which it is displayed.
	 * @param texID - id of the texture
	 * @param cap - (0-255) the height at which this texture stops displaying.
	 */
	void addTexture(int texId, int cap);
	void setTextureBlending(int pixels);

	unsigned char getHeightColor(int x, int z);
	float getPointHeight(int x, int z);
	//void render();
  private:
	unsigned char *terrainData; //data of the heightfield
	float scaleX; //how much we want to scale by
	float scaleY;
	float scaleZ;
	int size; //the size of the heightfield along x and z - power of 2

	//map<int, int> textureList; //cap texId
	GLuint texID; //OpenGL TexID
	
	bool texturesEnabled;
	
	//Private heightmap generations funcs
	void genFaultForm(float* terrainData, int iterations, float weight);
	void addFilter(float* terrainData, float weight);
	void filterPass(float* terrainData, int increment, float weight);
	void normalise(float* terrainData);
};

