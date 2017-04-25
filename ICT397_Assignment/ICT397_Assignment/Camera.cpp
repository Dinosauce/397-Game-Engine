#include "Camera.h"
#include <iostream>

Camera::Camera(){
	camera_mov_spd = 1.0;
	camera_rot_spd = 5.0;
	//move_vector.x = 0.0f; move_vector.y = 0.0f; move_vector.z = 0.0;

	MoveTo(Vector3(-1.0, 0.0, -1.0), Vector3());
	is_moving_fb = false;
	is_moving_lr = false;
}

void Camera::CheckCamera(){
	if (is_moving_fb || is_moving_lr){
		PreventFastDiagMove();
	}
	
	if (!is_moving_fb)
		move_vector.z = 0.0;
	if (!is_moving_lr)
		move_vector.x = 0.0;
	
}

void Camera::MoveForward(){
	move_vector.z = 1;
	is_moving_fb = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd;
		Move(move_vector);
}

void Camera::MoveBackward(){
	move_vector.z = -1;
	is_moving_fb = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd;
		Move(move_vector);
}

void Camera::MoveLeft(){
	move_vector.x = 1;
	is_moving_lr = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd;
		Move(move_vector);
}

void Camera::MoveRight(){
	move_vector.x = -1;
	is_moving_lr = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd;
		Move(move_vector);
}

void Camera::MoveTo(Vector3 new_pos, Vector3 new_rot){
	camera_pos = new_pos;
	camera_rot = new_rot;
	UpdateLookAt();
}

void Camera::UpdateLookAt(){
	// Build a rotation matrix
	Matrix rotation_matrix = Matrix::CreateRotationX(camera_rot.x) * Matrix::CreateRotationY(camera_rot.y);

	// Build look at offset vector
	Vector3 look_at_offset = Vector3::Transform(Vector3::UnitZ(), rotation_matrix);

	// Update the camera's look at vector
	camera_look_at = camera_pos + look_at_offset;
}

Vector3 Camera::PreviewMove(Vector3 amount){
	//Create a rotate matrix
	Matrix rotate = Matrix::CreateRotationY(camera_rot.y);

	// Create a movement vector
	Vector3 movement(amount.x, amount.y, amount.z);
	movement = Vector3::Transform(movement, rotate);

	// Return the value of camera position + movement vector
	return camera_pos + movement;
}

void Camera::Move(Vector3 scale){
	MoveTo(PreviewMove(scale), camera_rot);
}

void Camera::PreventFastDiagMove(){
	move_vector.Normalize();
	move_vector = move_vector * camera_mov_spd;
	Move(move_vector);
}
