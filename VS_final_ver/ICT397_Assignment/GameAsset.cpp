#include "GameAsset.h"



void TerrianAsset::LoadAsset(const char * path1)
{
	Terrain.loadHeightfield(path1, 128);
}

void TerrianAsset::RenderAsset()
{
	Terrain.render();
}

void NPCAsset::LoadAsset(const char * path2)
{
	NPCsLoader.loadModel(path2);
}

void NPCAsset::RenderAsset()
{
	NPCsLoader.Draw();
}

void ObjectAsset::LoadAsset(const char * path3)
{
	ObjectsLoader.loadModel(path3);
}

void ObjectAsset::RenderAsset()
{
	ObjectsLoader.Draw();
}

GameAsset* GameAssetFactory::Create(char* type)
{
	std::string type_str = type;
	if (type_str == "Terrain"){
		return new TerrianAsset;
	}
	else if (type_str == "Objects"){
		return new ObjectAsset;
	}
	else if (type_str == "NPC"){
		return new NPCAsset;
	}
	else{
		return NULL;
	}
}



