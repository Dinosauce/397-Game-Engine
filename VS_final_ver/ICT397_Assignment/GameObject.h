#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameAsset.h"
#include "math/GameMathHelp.h"
#include "AABB.h"
#include "State.h"
#include "StateMachine.h"


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
			if(!obj_fsm) delete obj_fsm;
		};

		/**
		* Draw Terrain Model
		* @param file name and GameAssetFactory type
		*/
		void LoadGameObject(char* Files[], char* type);
		/**
		* Render object
		*/
		void ShowGameObject();
		void ShowAnimation(int framStart, int framEnd);

		Vector3 getPosition(){ return position; };
		Vector3 getScale(){ return position; };
		double getRotation(){ return rotation_angle; };

		void setPosition(Vector3 pos){position.x = pos.x;position.y = pos.y;position.z = pos.z;}
		void setScale(Vector3 sca){ scale.x = sca.x; scale.y = sca.y; scale.z = sca.z; }
		void setRotation(double rot){ rotation_angle = rot; }

		void SetBoundingBox(double size);

		bool processCollision(GameObject &obj);

		// state machine
		void UpdateState();
		StateMachine<GameObject>* GetFSM() const { return obj_fsm; };

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

		// state machine
		StateMachine<GameObject>* obj_fsm;
};

#endif