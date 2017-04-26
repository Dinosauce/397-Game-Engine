#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix.h"
#include "GameMathHelp.h"

class Camera{
	public:
		Camera();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();

		bool IsMovingFB(){ return is_moving_fb; };
		bool IsMovingLR(){ return is_moving_lr; };
		void SetIsMovingFB(bool new_state){ is_moving_fb = new_state; };
		void SetIsMovingLR(bool new_state){ is_moving_lr = new_state; };
		void SetIsRotating(bool new_state){ is_rotating = new_state; };
		void CheckCamera();
		

		Vector3 GetCameraPos(){ return camera_pos; };

		Vector3 GetCameraLookAt(){ return camera_look_at; };

		void SetCameraRotation(float delta_x, float delta_y);

		void SetCameraSpdWithDT(float new_delta_time){ 
			camera_mov_spd_with_dt = camera_mov_spd * new_delta_time; 
			camera_rot_spd_with_dt = camera_rot_spd * new_delta_time;
		};

	private:
		void MoveTo(Vector3 new_pos, Vector3 new_rot);
		void UpdateLookAt();
		Vector3 PreviewMove(Vector3 amount);
		void Move(Vector3 scale);
		void PreventFastDiagMove();

		Vector3 camera_pos;
		Vector3 camera_rot;

		const float camera_mov_spd = 50.0;
		float camera_mov_spd_with_dt;
		const float camera_rot_spd = 20.0;
		float camera_rot_spd_with_dt;
		Vector3 camera_look_at;

		// movement
		Vector3 move_vector;
		bool is_moving_fb;
		bool is_moving_lr;

		// rotation
		Vector3 rotation_buffer;
		bool is_rotating;
};

#endif