#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameAsset.h"
#include "GameMathHelp.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	private:
		//static ObjectLoader OL;
		bool res;
		const char * pathName;

		Vector3 position;
		Vector3 scale;
		GameAssetFactory gameAssetFactory_factory;
		GameAsset* gameAssetFactory_handler;
};

#endif