#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameAsset.h"
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
		void LoadGameObject(const char *path, char* type);

		/**
		* Render object
		*/
		void ShowGameObject();

	private:
		static ObjectLoader OL;
		bool res;
		const char * pathName;

		GameAssetFactory gameAssetFactory_factory;
		GameAsset* gameAssetFactory_handler;
};

#endif