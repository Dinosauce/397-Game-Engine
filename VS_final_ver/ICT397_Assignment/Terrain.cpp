#include "Terrain.h"
#include <SDL/SDL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include "../singletons.h"
#include "textureHandler/multitexture.h"
#include "stb_image.h"
using namespace std;

terrain::terrain()
{

}

void terrain::loadHeightfield(const char *filename, const int size) {
	//open for binary read
	ifstream infile(filename, ios::binary);
	if (!infile) {
		cout << "Cannot open file :" << filename << endl;
		Loaded = false;
	}
	//allocate memory
	if (terrainData)
		delete[] terrainData;
	if (size>0)
		terrainData = new unsigned char[size*size];
	if (terrainData == NULL)
		Loaded = false;
	//read in heightfield.
	// get length of file:
	infile.seekg(0, ios::end);
	int length = infile.tellg();
	// read data as a block:
	infile.seekg(0, ios::beg);
	infile.read(reinterpret_cast<char *>(terrainData), length);

	infile.close();
	this->size = size;
	Loaded = true;
}


bool  terrain::genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random)
{
	int x1, x2, z1, z2;
	float* heights = NULL;
	int displacement;
	if (hSize <= 0)
		return false;
	if (random) //create truly random map
		srand(time(NULL));
	// allocate memory for heightfield array
	size = hSize;
	heights = new float[size*size]; //allocate memory
	terrainData = new unsigned char[size*size];
	if (heights == NULL || terrainData == NULL)
		return false;
	// initialise the heightfield array to all zeros
	for (int i = 0; i<size*size; i++)
		heights[i] = 0;
	// generate heightfield
	for (int j = 0; j<iterations; j++) {
		//calculate reducing displacement value - how much to alter height
		displacement = maxHeight - ((maxHeight - minHeight)*j) / iterations;

		//pick the first point P1(x1, z1) at random from the height map
		x1 = (rand() % size);
		z1 = (rand() % size);
		// pick up the second random point P2(x2, z2) and make sure it is
		// different from the first point
		do {
			x2 = (rand() % size);
			z2 = (rand() % size);
		} while (x2 == x1 && z2 == z1);
		//for each point P(x, z) in the field, calculate the new height values
		for (int z = 0; z<size; z++) {
			for (int x = 0; x<size; x++) {
				// determine which side of the line P1P2 the point P lies in
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
					heights[(z*size) + x] += (float)displacement;
				}
			}
		}
		addFilter(heights, weight);
	}
	// normalise the heightfield
	normalise(heights);
	// copy the float heightfield to terrainData (in unsign char)
	for (int z = 0; z<size; z++) {
		for (int x = 0; x<size; x++) {
			terrainData[(z*size) + x] = (unsigned char)heights[z*size + x];
		}
	}
	// dispose of the temporary array heights
	delete[] heights;
	return true;

}

void terrain::setNumTerrainTexRepeat(int num)
{
	numTerrainTexRepeat = num;
}

void terrain::setNumDetailMapRepeat(int num)
{
	numDetailMapRepeat = num;
}

void terrain::setScalingFactor(float xScale, float yScale, float zScale) {
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
}

float terrain::getHeight(int xpos, int zpos) {
	if (inbounds(xpos, zpos)) {
		return ((float)(terrainData[(zpos*size) + xpos])*scaleY);
	}
}

float terrain::getPointHeight(int x, int z)
{
	if (x < 0)
		x = 0;
	else if (x >= size)
		x = size - 1;
	if (z < 0)
		z = 0;
	else if (z >= size)
		z = size - 1;

	return (float)terrainData[z * size + x];
}

float terrain::getAverageHight(int x, int z)
{
	x /= scaleX;
	z /= scaleZ;

	int ix = (int)x;
	int iz = (int)z;

	float A, B, C, D, E, F, G;
	A = getPointHeight(ix, iz);
	B = getPointHeight(ix, iz + 1);
	C = getPointHeight(ix + 1, iz);
	D = getPointHeight(ix + 1, iz + 1);

	E = A + ((z - iz) * (B - A));
	F = C + ((z - iz) * (D - C));
	G = E + ((x - ix) * (F - E));

	return G * scaleY;
}

float terrain::getUnscaledHeight(int xpos, int zpos) {
	if (inbounds(xpos, zpos)) {
		return ((float)(terrainData[(zpos*size) + xpos]));
	}
}

unsigned char terrain::getHeightColor(int xpos, int zpos) {
	if (inbounds(xpos, zpos)) {
		return terrainData[zpos*size + xpos];
	}
	return 1;
}

bool terrain::inbounds(int xpos, int zpos)
{
	return((xpos >= 0 && xpos <= 128) && (zpos >= 0 && zpos <= 128));
}

void terrain::normalise(float* terrainData)
{
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = terrainData[0];
	fMax = terrainData[0];

	for (i = 1; i < size*size; i++)
	{
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}

	if (fMax <= fMin)
		return;

	fHeight = fMax - fMin;

	for (i = 0; i < size*size; i++)
		terrainData[i] = ((terrainData[i] - fMin) / fHeight) * 255.0f;
}

void terrain::filterPass(float* dataP, int increment, float weight)
{
	float yprev = dataP[0]; // for yi-1
	int j = increment; // +1, -1, +size, -size
	float k = weight;
	// loop through either
	// one row from left to right (increment = +1), or
	// one row from right to left (increment = -1), or
	// one column from top to bottom (increment = +size), or
	// one column from bottom to top (increment = -size)
	for (int i = 1; i<size; i++) {
		// yi= k yi-1+ (1-k) xi
		*(dataP + j) = k*yprev + (1 - k)*(*(dataP + j)); //
		yprev = *(dataP + j);
		j += increment;
	}
}

void terrain::addFilter(float* terrainData, float weight) {
	int i;
	//erode left to right, starting at the beginning of each row
	for (i = 0; i<size; i++)
		filterPass(&terrainData[size*i], 1, weight);
	//erode right to left, starting at the end of each row
	for (i = 0; i<size; i++)
		filterPass(&terrainData[size*i + size - 1], -1, weight);
	//erode top to bottom, starting at the beginning of each column
	for (i = 0; i<size; i++)
		filterPass(&terrainData[i], size, weight);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i<size; i++)
		filterPass(&terrainData[size*(size - 1) + i], -size, weight);
}

bool terrain::createProceduralTexture()
{
	if (!terrainData || tex.getNumTextures() == 0)
		return false;
	unsigned char curHeight; //current height in the heightmap
	float weight; //weight of influence of tex to height
	//setup room for the new texture
	tex.setupNewTexture(size, size);
	RGB<unsigned char> color;
	RGB<unsigned char> totalColor;
	float range = tex.getRange();
	//loop through each point in the heightmap and get height value
	for (int z = 0; z<size; z++) {
		for (int x = 0; x<size; x++) {
			totalColor.reset();
			curHeight = getUnscaledHeight(x, z); //get unscaled heightmap value
			for (int i = 0; i<tex.getNumTextures(); i++)
			{ //calculate weight for each texture map
				weight = (range - abs((float)curHeight - tex.getTextureMax(i))) / range;
				if (weight>0.0) { //texture is influenced by the height, calculate its color weighting
					color = tex.getColor(i, x, z);
					totalColor.r += color.r*weight;
					totalColor.g += color.g*weight;
					totalColor.b += color.b*weight;
				}
			} //add the combined color weightings to the new texture.
			tex.setColor(x, z, totalColor);
		}
	}
	
	//load the new texture into memory ready for use
	texID = texMan.createNewTexture(tex.getTex(), size, size);
	cout << texID;
	textureMapping = true;
	return true;
}

bool terrain::addProceduralTexture(char* filename)
{
	tex.addTexture(filename);
	return true;
}

bool terrain::loadDetailMap(char* filename)
{
	detailMapTexID = texMan.loadTexture(filename);
	return true;
}

bool terrain::DoDetailMapping(bool DM)
{
	detailMap = DM;
	return detailMap;
}

void terrain::LoadLightMap(const char *filename, const int size)
{
	//lightmapData = stbi_load(filename, &LightMapWidth, &LightMapHeight, &LightMapBPP, 3);
	
	//open for binary read
	ifstream infile(filename, ios::binary);
	if (!infile) {
		cout << "Cannot open file :" << filename << endl;
		Loaded = false;
	}
	//allocate memory
	if (lightmapData)
		delete[] lightmapData;
	if (size>0)
		lightmapData = new unsigned char[size*size];
	if (lightmapData == NULL)
		Loaded = false;
	//read in heightfield.
	// get length of file:
	infile.seekg(0, ios::end);
	int length = infile.tellg();
	// read data as a block:
	infile.seekg(0, ios::beg);
	infile.read(reinterpret_cast<char *>(lightmapData), length);

	infile.close();
	this->LightMapSize = size;
}

RGB<float> terrain::getLightMapColor()
{
	RGB<float> color = { 0, 0, 0 };

	color.r =1;
	color.g =1;
	color.b = 1;

	return color;
}


unsigned char terrain::getBrightnessAtPoint(int x, int z)
{
	if (isLightMapped)
		return (lightmapData[(z*size) + x]);
	else
		return 0;
}

bool terrain::DoLightMapping(bool LM)
{
	isLightMapped = LM;
	return LM;
}

void terrain::render() {
	unsigned char hcolor = 255;
	unsigned char hcolor2 = 255; //color of the height
	//float texLeft, texBottom, texTop;
	float tLeft = 0.0f;
	float tBottom = 0.0f;
	float tTop = 0.0f;
	bool texturesEnabled = true;

	RGB<float> lightmapColor;
	unsigned char shadeLow;
	unsigned char shadeHigh;

	//cout <<"ID:"<< detailMapTexID << "  " << texID<<endl;
	
	if (initMultiTextures())
	{
		//cout << "ARB!!" << endl;
	}

	glDisable(GL_BLEND);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	//bind texture 0
	texMan.setActiveTexture(texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	//bind texture 1
	texMan.setActiveTexture(detailMapTexID);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

	
	for (int z = 0; z<size - 2; z++) {
		//loop through the x axis
		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x<size - 1; x++) {
			if (textureMapping)
			{
				tLeft = (float)x / (float)size;
				tBottom = (float)z / (float)size;
				tTop = (float)(z + 1) / (float)size;
			}
			else
			{
				hcolor = getHeightColor(x, z);
				hcolor2 = getHeightColor(x, z + 1);
			}

			if (isLightMapped)
			{
				lightmapColor = getLightMapColor();
				shadeLow = getBrightnessAtPoint(x, z);
				shadeHigh = getBrightnessAtPoint(x, z + 1);
			}
			else
			{
				lightmapColor = {1,1,1};
				shadeLow = 255;
				shadeHigh = 255;
			}


			glColor4ub(shadeLow*lightmapColor.r, shadeLow*lightmapColor.g,shadeLow*lightmapColor.b, 255);
			//glColor3ub(hcolor, hcolor, hcolor);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, tLeft*numTerrainTexRepeat, tBottom*numTerrainTexRepeat);
			if (detailMap)
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB, tLeft*numDetailMapRepeat, tBottom*numDetailMapRepeat);
			glVertex3f((float)x*scaleX, getHeight(x, z), (float)z*scaleZ);

			glColor4ub(shadeHigh*lightmapColor.r, shadeHigh*lightmapColor.g,shadeHigh*lightmapColor.b, 255);
			//glColor3ub(hcolor2, hcolor2, hcolor2);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, tLeft*numTerrainTexRepeat, tTop*numTerrainTexRepeat);
			if (detailMap)
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB, tLeft*numDetailMapRepeat, tTop*numDetailMapRepeat);
			glVertex3f((float)x*scaleX, getHeight(x, z + 1), (float)(z + 1)*scaleZ);
		}
		glEnd();
	}


	if (detailMap){
		glActiveTextureARB(GL_TEXTURE1_ARB); glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, 0);
}