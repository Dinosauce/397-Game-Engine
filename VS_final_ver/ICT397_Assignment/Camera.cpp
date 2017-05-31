#include "Camera.h"
#include <iostream>

Camera::Camera(){
	camera_mov_spd_with_dt = 0.0;
	camera_rot_spd_with_dt = 0.0;

	MoveTo(Vector3(-1.0, 50, -1.0), Vector3());
	is_moving_fb = false;
	is_moving_lr = false;
	is_rotating = false;
}

void Camera::CheckCamera(){
	if (is_moving_fb || is_moving_lr || is_rotating){
		PreventFastDiagMove();
	}
	
	if (!is_moving_fb)
		move_vector.z = 0.0;
	if (!is_moving_lr)
		move_vector.x = 0.0;
}

void Camera::SetCameraRotation(const double & delta_x, const double & delta_y){
	// Cache mouse location
	rotation_buffer.x -= 0.01f * delta_x * camera_rot_spd_with_dt;
	rotation_buffer.y -= 0.01f * delta_y * camera_rot_spd_with_dt;

	// No move over the ground and back to the top
	if (rotation_buffer.y < MathHelp::ToRadians(-75.0))
		rotation_buffer.y = rotation_buffer.y - (rotation_buffer.y - MathHelp::ToRadians(-75.0));

	if (rotation_buffer.y > MathHelp::ToRadians(75.0))
		rotation_buffer.y = rotation_buffer.y - (rotation_buffer.y - MathHelp::ToRadians(75.0));

	camera_rot = Vector3(
		-MathHelp::Clamp(rotation_buffer.y, MathHelp::ToRadians(-75.0), MathHelp::ToRadians(75.0)),
		-MathHelp::WrapAngle(rotation_buffer.x),
		0.0
		);
	UpdateLookAt();
}

void Camera::MoveForward(){
	move_vector.z = 1;
	is_moving_fb = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero()){
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd_with_dt;
		Move(move_vector);
	}
}

void Camera::MoveBackward(){
	move_vector.z = -1;
	is_moving_fb = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero()){
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd_with_dt;
		Move(move_vector);
	}
}

void Camera::MoveLeft(){
	move_vector.x = 1;
	is_moving_lr = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero()){
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd_with_dt;
		Move(move_vector);
	}
}

void Camera::MoveRight(){
	move_vector.x = -1;
	is_moving_lr = true;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero()){
		move_vector.Normalize();
		move_vector = move_vector * camera_mov_spd_with_dt;
		Move(move_vector);
	}
}

void Camera::MoveTo(const Vector3 & new_pos, const Vector3 & new_rot){
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

Vector3 Camera::PreviewMove(const Vector3 & amount){
	//Create a rotate matrix
	Matrix rotate = Matrix::CreateRotationY(camera_rot.y);

	// Create a movement vector
	Vector3 movement(amount.x, amount.y, amount.z);
	movement = Vector3::Transform(movement, rotate);

	// Return the value of camera position + movement vector
	return camera_pos + movement;
}

void Camera::Move(const Vector3 & scale){
	MoveTo(PreviewMove(scale), camera_rot);
}

void Camera::PreventFastDiagMove(){
	move_vector.Normalize();
	move_vector = move_vector * camera_mov_spd_with_dt;
	Move(move_vector);
}

void Camera::isTerrainCollision(int H)
{
	camera_pos.y = H;
}