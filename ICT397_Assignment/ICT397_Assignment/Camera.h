#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix.h"
#include "GameTime.h"

class Camera{
	public:
		Camera();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();

		bool IsMoving(){ return is_moving; };
		void SetIsMoving(bool new_state){ is_moving = new_state; };
		void PreventFastDiagMove();

		Vector3 GetCameraPos(){ return camera_pos; };

		Vector3 GetCameraLookAt(){ return camera_look_at; };

		void SetGameTimePtr(GameTime* new_game_time_ptr){ game_time = new_game_time_ptr; };

		void SetCameraMovSpd(float new_spd){ camera_mov_spd = new_spd; };

	private:
		void MoveTo(Vector3 new_pos, Vector3 new_rot);
		void UpdateLookAt();
		Vector3 PreviewMove(Vector3 amount);
		void Move(Vector3 scale);

		Vector3 camera_pos;
		Vector3 camera_rot;
		float camera_mov_spd;
		float camera_rot_spd;
		Vector3 camera_look_at;

		Vector3 move_vector;
		bool is_moving;

		GameTime* game_time;
		float delta_time;
};

#endif