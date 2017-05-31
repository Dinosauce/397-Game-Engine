#include "GameAsset.h"



void OBJAsset::LoadAsset(const char * path[])
{
	ALoader.loadModel(path[0]);
}

void OBJAsset::RenderAsset()
{
	//Terrain.normalise();
	ALoader.Draw();
}

void MD2Asset::LoadAsset(const char * path[])
{
	ALoader.loadModel(path[0]);
}

void MD2Asset::RenderAsset()
{
	ALoader.Draw();
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



