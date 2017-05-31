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
		void LoadGameObject(const char* Files[], char* type);
		/**
		* Render object
		*/
		void ShowGameObject();

		Vector3 getPosition(){ return position; }

		void setPosition(Vector3 pos){position.x = pos.x;position.y = pos.y;position.z = pos.z;}

	private:
		//static ObjectLoader OL;
		bool res;
		const char * pathName;

		Vector3 position;
		GameAssetFactory gameAssetFactory_factory;
		GameAsset* gameAssetFactory_handler;
};

#endif