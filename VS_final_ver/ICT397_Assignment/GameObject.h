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
		* Destructure - delete fsm
		*/
		~GameObject(){
			//if(!obj_fsm) delete obj_fsm;
		};

		/**
		* Draw Terrain Model
		* @param file name and GameAssetFactory type
		*/
		virtual void LoadGameObject(char* Files[], char* type);
		/**
		* Render object
		*/
		virtual void ShowGameObject();
		virtual void ShowAnimation(int framStart, int framEnd);

		virtual Vector3 getPosition(){ return position; };
		virtual Vector3 getScale(){ return position; };
		virtual double getRotation(){ return rotation_angle; };

		virtual void setPosition(Vector3 pos){ position.x = pos.x; position.y = pos.y; position.z = pos.z; }
		virtual void setScale(Vector3 sca){ scale.x = sca.x; scale.y = sca.y; scale.z = sca.z; }
		virtual void setRotation(double rot){ rotation_angle = rot; }

		virtual void SetBoundingBox(double size);

		virtual bool processCollision(GameObject &obj);




	private:
		//static ObjectLoader OL;
		bool res;
		const char * pathName;
		Vector3 model[8];

		static AABB boundingBox;

		Vector3 position;
		double rotation_angle;
		Vector3 scale;
		GameAssetFactory gameAssetFactory_factory;
		GameAsset* gameAssetFactory_handler;


};

#endif