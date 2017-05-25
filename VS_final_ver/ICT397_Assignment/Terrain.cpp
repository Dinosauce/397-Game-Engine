#include "Terrain.h"
#include <SDL/SDL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include "../singletons.h"
using namespace std;

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

void terrain::setNumTerrainTexRepeat(int num)
{
	numTerrainTexRepeat = num;
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
	//dont repeat this texture
	numTerrainTexRepeat = 0;
	return true;
}

bool terrain::addProceduralTexture(char* filename)
{
	tex.addTexture(filename);
	return true;
}

void terrain::render() {
	unsigned char hcolor = 255;
	unsigned char hcolor2 = 255; //color of the height
	//float texLeft, texBottom, texTop;
	float tLeft = 0.0f;
	float tBottom = 0.0f;
	float tTop = 0.0f;
	bool texturesEnabled = true;

	if (texturesEnabled)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texID);
		//cout << "Textures Enabled" << endl;
	}

	if (Loaded)
	{

		//loop through the z axis
		for (int z = 0; z<getSize() - 1; z++) {
			//loop through the x axis
			glBegin(GL_TRIANGLE_STRIP);
			for (int x = 0; x<getSize(); x++) {
				if (texturesEnabled)
				{
					tLeft = (float)x / (float)size;
					tBottom = (float)z / (float)size;
					tTop = (float)(z + 1) / (float)size;
				}
				else
				{
					hcolor = getHeightColor(x, z);
					hcolor2 =getHeightColor(x, z + 1);
				}

				glColor3ub(hcolor, hcolor, hcolor);
				glTexCoord2f(tLeft, tBottom);
				glVertex3f((float)x*scaleX, getHeight(x, z)*0.1, (float)z*scaleZ);

				//create the next point in the triangle strip
				glColor3ub(hcolor2, hcolor2, hcolor2);
				glTexCoord2f(tLeft, tTop);
				glVertex3f((float)x*scaleX, getHeight(x, z + 1)*0.1, (float)(z + 1)*scaleZ);
			}
			glEnd();
		}
	}
	else
	{
		cout << "failed to load" << endl;
	}
}