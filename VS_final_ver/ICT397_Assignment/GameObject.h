#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameAsset.h"
#include "math/GameMathHelp.h"
#include "AABB.h"


class GameObject
{
	public:

		/**
		* Default constructor
		*/
		GameObject();

		/**
		* Draw Terrain Model
		* @param file name and GameAssetFactory type
		*/
		void LoadGameObject(char* Files[], char* type);
		/**
		* Render object
		*/
		void ShowGameObject();

		Vector3 getPosition(){ return position; }
		Vector3 getScale(){ return position; }

		void setPosition(Vector3 pos){position.x = pos.x;position.y = pos.y;position.z = pos.z;}
		void setScale(Vector3 sca){ scale.x = sca.x; scale.y = sca.y; scale.z = sca.z; }

		bool processCollision(GameObject &obj);


	private:
		//static ObjectLoader OL;
		bool res;
		const char * pathName;
		Vector3 model[8];

		static AABB boundingBox;

		Vector3 position;
		Vector3 scale;
		GameAssetFactory gameAssetFactory_factory;
		GameAsset* gameAssetFactory_handler;
};

#endif