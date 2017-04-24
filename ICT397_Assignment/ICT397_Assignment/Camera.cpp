#include "Camera.h"

Camera::Camera(){
	camera_mov_spd = 10.0;
	camera_rot_spd = 5.0;
	move_vector.x = 0.0f; move_vector.y = 0.0f; move_vector.z = 0.0;

	MoveTo(Vector3(), Vector3());
}

void Camera::MoveForward(){
	move_vector.z = 1;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		PreventFastDiagMove();
}

void Camera::MoveBackward(){
	move_vector.z = -1;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		PreventFastDiagMove();
}

void Camera::MoveLeft(){
	move_vector.x = 1;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		PreventFastDiagMove();
}

void Camera::MoveRight(){
	move_vector.x = -1;

	// Normalize the vector so that it does not move faster diagonally
	if (move_vector != Vector3::Zero())
		PreventFastDiagMove();
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

	// Reset back to zero and wait for next movement
	//move_vector = Vector3::Zero();
}