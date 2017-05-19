#ifndef GAMEASSET_H
#define GAMEASSET_H
#include "ObjectLoader.h"

class GameAsset
{
public:

	/**
	* Default constructor
	*/
	GameAsset(){};

	/**
	* Deconstructor
	*/
	~GameAsset(){};

	/**
	* Load asset 
	* @param file pathname
	*/
	virtual void LoadAsset(const char * path)=0;

	/**
	* Render asset
	*/
	virtual void RenderAsset() = 0;

private:


};

class TerrianAsset :public GameAsset
{
	void LoadAsset(const char * path1);
	void RenderAsset();
private:
	 ObjectLoader TerrianLoader;
};

class ObjectAsset :public GameAsset
{
	void LoadAsset(const char * path2);
	void RenderAsset();
private:
	 ObjectLoader ObjectsLoader;
};

class NPCAsset :public GameAsset
{
	void LoadAsset(const char * path3);
	void RenderAsset();
private:
	 ObjectLoader NPCsLoader;
};

class GameAssetFactory{
public:
	GameAsset* Create(char* type);
};

#endif
