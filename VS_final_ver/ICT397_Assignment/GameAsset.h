#ifndef GAMEASSET_H
#define GAMEASSET_H
#include "AssimpLoader.h"

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
	virtual void LoadAsset(const char * path[])=0;

	/**
	* Render asset
	*/
	virtual void RenderAsset() = 0;

private:


};

class OBJAsset :public GameAsset
{
	void LoadAsset(const char * path[]);
	void RenderAsset();
private:
	AssimpLoader ALoader;
};

class MD2Asset :public GameAsset
{
	void LoadAsset(const char * path[]);
	void RenderAsset();
private:
	AssimpLoader ALoader;
};



class GameAssetFactory{
public:
	GameAsset* Create(char* type);
};

#endif
