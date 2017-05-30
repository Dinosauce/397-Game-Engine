#include "GameAsset.h"



void TerrianAsset::LoadAsset(const char * path1)
{
	Terrain.loadHeightfield(path1, 128);
	Terrain.setScalingFactor(5, 0.5, 5);
	Terrain.generateHeightfield(128,0.3,150);
	Terrain.addProceduralTexture("pictures/lowestTile.tga");
	Terrain.addProceduralTexture("pictures/lowTile.tga");
	Terrain.addProceduralTexture("pictures/highTile.tga");
	Terrain.addProceduralTexture("pictures/highestTile.tga");
	Terrain.createProceduralTexture();
	Terrain.setNumTerrainTexRepeat(1);
	Terrain.DoTextureMapping(true);
	Terrain.loadDetailMap("pictures/detailMap.tga");
	Terrain.setNumDetailMapRepeat(8);
	Terrain.DoDetailMapping(true);
	Terrain.LoadLightMap("pictures/lightmap.raw",128);
	Terrain.DoLightMapping(true);
}

void TerrianAsset::RenderAsset()
{
	//Terrain.normalise();
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



