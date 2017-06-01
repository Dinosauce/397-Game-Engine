#include "GameAsset.h"



void OBJAsset::LoadAsset(char * path[])
{
	ALoader.loadModel(path[0]);
}

void OBJAsset::RenderAsset()
{
	//Terrain.normalise();
	ALoader.Draw();
}

void MD2Asset::LoadAsset(char * path[])
{
	char *md2File = path[0];
	char *PCXFile = path[1];
	md2.loadModel(md2File, PCXFile);
	md2.setAnimationSpeed(10);
	md2.printHeader();
}

void MD2Asset::RenderAsset()
{
	//md2.render();
	md2.animate(40, 46);
}


GameAsset* GameAssetFactory::Create(char* type)
{
	std::string type_str = type;
	if (type_str == "OBJ"){
		return new OBJAsset;
	}
	else if (type_str == "MD2"){
		return new MD2Asset;
	}
	else{
		return NULL;
	}
}



