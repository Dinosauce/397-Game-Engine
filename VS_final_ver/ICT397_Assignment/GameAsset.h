#ifndef GAMEASSET_H
#define GAMEASSET_H
#include "AssimpLoader.h"
#include "MD2Loader/md2Loader.h"

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
	virtual void LoadAsset(char * path[])=0;

	/**
	* Render asset
	*/
	virtual void RenderAsset() = 0;

private:


};

class OBJAsset :public GameAsset
{
	void LoadAsset(char * path[]);
	void RenderAsset();
private:
	AssimpLoader ALoader;
};

class MD2Asset :public GameAsset
{
	void LoadAsset(char * path[]);
	void RenderAsset();
private:
	md2Loader md2;
};



class GameAssetFactory{
public:
	GameAsset* Create(char* type);
};

#endif
