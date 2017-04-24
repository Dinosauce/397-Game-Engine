#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix.h"

class Camera{
	public:
		Camera();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();

	private:
		void MoveTo(Vector3 new_pos, Vector3 new_rot);
		void UpdateLookAt();
		Vector3 PreviewMove(Vector3 amount);
		void Move(Vector3 scale);
		void PreventFastDiagMove();

		Vector3 camera_pos;
		Vector3 camera_rot;
		float camera_mov_spd;
		float camera_rot_spd;
		Vector3 camera_look_at;

		Vector3 move_vector;
};

#endif