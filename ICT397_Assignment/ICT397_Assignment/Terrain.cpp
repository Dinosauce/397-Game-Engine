#include "Terrain.h"

using namespace std;

Terrain::Terrain()
{
	setScale(1.0);
	texturesEnabled = false;
	texID = -1;
}

Terrain::~Terrain()
{
	delete[] terrainData;
}

bool Terrain::loadHeightfield(char *filename, const int size) {
	//open for binary read
	ifstream infile(filename,ios::binary);
	if(!infile) {
		cerr<<"Cannot open file :"<<filename<<endl;
		return false;
	}
	//allocate memory
	if(terrainData)
		delete[] terrainData;

	if(size>0)
		terrainData=new unsigned char[size*size];

	if(terrainData==NULL)
		return false;

	//read in heightfield.
	// get length of file:
	infile.seekg (0, ios::end);
	int length = infile.tellg();

	// read data as a block:
	infile.seekg (0, ios::beg);
	infile.read(reinterpret_cast<char *>(terrainData),length);
	infile.close();
	this->size=size;

	return true;
}

bool Terrain::generateHeightfield(const int size, float weight, int iterations)
{
	float* data = NULL;

	if(size <= 0)
		return false;

	this->size = size;

	data = new float[size*size];
	terrainData=new unsigned char[size*size];

	if(data == NULL || terrainData == NULL)
		return false;

	//Generate and filter random terrain
	genFaultForm(data, iterations, weight);

	//Smooth out and normalize generated terrain
	normalise(data);

	//Copy temp data
	for (int z=0; z<size; z++)
	{
		for (int x=0; x<size; x++)
		{
			terrainData[(z*size) + x] = (unsigned char) data[z*size + x];
		}
	}

	//free temp data
	delete[] data;
	return true;

}//createFractalHeight

void Terrain::genFaultForm(float* terrainData, int iterations, float weight)
{
	//Set to flat plane
	for (int z=0; z<size; z++)
	{
		for (int x=0; x<size; x++)
		{
			terrainData[(z*size) + x] = 0;
		}
	}

	//Displace
	for (int iter = 0; iter < iterations; iter++)
	{
		float displacement = (255*((float)iter/(iterations)));

		int x1, x2, z1, z2;

		//Set random line
		x1 = rand() % size;
		z1 = rand() % size;

		do {
			x2 = rand() % size;
			z2 = rand() % size;
		} while (x1 == x2 && z1 == z2);

		//Display terrain on one side of line
		for (int z=0; z<size; z++)
		{
			for (int x=0; x<size; x++)
			{
				int y = (x2 - x1) * (z - z1) - (z2 - z1) * (x - x1);
				if (y > 0)
					terrainData[(z*size) + x] += (float)displacement;
			}
		}//For each terrainpoint

		addFilter(terrainData, weight);
	}//For each iteration
}

unsigned char Terrain::getHeightColor( int x, int z)
{
	return terrainData[z * size + x];
}

float Terrain::getPointHeight(int x, int z)
{
	if (x < 0)
		x = 0;
	else if (x >= size)
		x = size - 1;
	if (z < 0)
		z = 0;
	else if (z >= size)
		z = size - 1;

	return (float) terrainData[z * size + x];
}

float Terrain::getHeight(float x, float z)
{
	//TODO: divide by scale?????
	x /= scaleX;
	z /= scaleZ;

	int ix = (int) x;
	int iz = (int) z;

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

//void Terrain::render() {
//	unsigned char hcolor = 255;
//	unsigned char hcolor2 = 255; //color of the height
//
//	float tLeft = 0.0f;
//	float tBottom = 0.0f;
//	float tTop = 0.0f;
//
//	if (texturesEnabled)
//	{
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, (GLuint)texID);
//		//cout << "Textures Enabled" << endl;
//	}
//
//	//loop through the z axis
//	for(int z=0; z<size-1; z++) {
//		//loop through the x axis
//		glBegin( GL_TRIANGLE_STRIP );
//
//		for(int x=0; x<size; x++) {
//			if (texturesEnabled)
//			{
//				tLeft = (float)x/(float)size;
//				tBottom = (float)z/(float)size;
//				tTop = (float)(z+1)/(float)size;
//			}
//			else
//			{
//				hcolor=getHeightColor(x,z);
//				hcolor2=getHeightColor(x,z+1);
//			}
//
//			//create the the first point in the triangle strip
//			glColor3ub(hcolor,hcolor,hcolor);
//			glTexCoord2f(tLeft, tBottom);
//			glVertex3f( (float)x*scaleX, (float)getHeight( x, z )*scaleY, (float)z*scaleZ );
//
//			//create the next point in the triangle strip
//			glColor3ub(hcolor,hcolor,hcolor);
//			glTexCoord2f(tLeft, tTop);
//			glVertex3f( (float)x*scaleX, getHeight( x, z+1 )*scaleY, (z+1)*scaleZ );
//		}
//	glEnd();
//	}
//}

void Terrain::setTexture(int id)
{
	if (id != -1)
	{
		texID = id;
		texturesEnabled = true;
		cout << texID;
	}
	else
		cout << "Invalid Texture!";
}

void Terrain::setScale(float scale)
{
	scaleX = scale;
	scaleY = scale;
	scaleZ = scale;
}

void Terrain::setScale(float x, float y, float z)
{
	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void Terrain::dispTexture()
{
	dispTexture(!texturesEnabled);
}

void Terrain::dispTexture(bool displayTextures)
{
	if (displayTextures && texID != -1)
	{
		texturesEnabled = true;
		glBindTexture(GL_TEXTURE_2D, texID);
	}
	else
	{
		texturesEnabled = false;
		glBindTexture(GL_TEXTURE_2D, 0);
	}
		
}

void Terrain::addFilter(float* terrainData, float weight)
{
	int i;

	//L to R
	for (i = 0; i < size; i++)
		filterPass( &terrainData[size*i], 1, weight);

	//R to L
	for (i = 0; i < size; i++)
		filterPass( &terrainData[size*i + size-1], -1, weight);

	//T to B
	for (i = 0; i < size; i++)
		filterPass(&terrainData[i], size, weight);

	//B to T
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * (size-1) + i], -size, weight);
}

void Terrain::filterPass(float* terrainData, int increment, float weight)
	{
		if (weight > 1)
			weight = 1;
		else if (weight < 0)
			weight = 0;

		float yPrev = terrainData[0];
		int j = increment;
		
		for (int i = 1; i < size; i++)
		{
			*(terrainData+j) = weight * yPrev + (1 - weight) * (*(terrainData+j));
			yPrev = *(terrainData+j);
			j += increment;
		}
	}

void Terrain::normalise(float* terrainData)
{
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = terrainData[0];
	fMax = terrainData[0];

	for( i = 1; i < size*size; i++)
	{
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}

	if(fMax <= fMin)
		return;

	fHeight = fMax - fMin;

	for (i = 0; i < size*size; i++)
		terrainData[i] = ( ( terrainData[i] - fMin) / fHeight) * 255.0f;
}