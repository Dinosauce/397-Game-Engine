#ifndef CAMERA_H
#define CAMERA_H

#include "GameMathHelp.h"
#include "Terrain.h"
/**
* Camera class - Plentoon Games
* Stores the camera position and look at vector
* Calculates the movement and rotation
*/
class Camera{
	public:
		/**
		* Ctor
		* Set the spd with dt variables to 0.0
		* Set the initial cam pos to default pos
		* bool variables set to false as default
		*/
		Camera();

		/**
		* Move the camera to the front
		*/
		void MoveForward();

		/**
		* Move the camera to the back
		*/
		void MoveBackward();

		/**
		* Move the camera to the left
		*/
		void MoveLeft();

		/**
		* Move the camera to the right
		*/
		void MoveRight();

		/**
		* See whether the camera is moving front back or not
		* @return True if is moving, False if is not moving
		*/
		bool IsMovingFB(){ return is_moving_fb; };
		
		/**
		* See whether the camera is moving left right or not
		* @return True if is moving, False if is not moving
		*/
		bool IsMovingLR(){ return is_moving_lr; };

		/**
		* Check whether the camera is moving or not
		* If is moving, move to the next position
		* If isn't, reset the move vector to zero
		*/
		void CheckCamera();


		/**
		* Set methods for private variables
		* @param new value to be set
		*/

		void SetIsMovingFB(const bool & new_state){ is_moving_fb = new_state; };
		void SetIsMovingLR(const bool & new_state){ is_moving_lr = new_state; };
		void SetIsRotating(const bool & new_state){ is_rotating = new_state; };
		void SetCameraRotation(const double & delta_x, const double & delta_y);
		void SetCameraSpdWithDT(const double & new_delta_time){
			camera_mov_spd_with_dt = camera_mov_spd * new_delta_time;
			camera_rot_spd_with_dt = camera_rot_spd * new_delta_time;
		};
		
		/**
		* Get methods for private variables
		* @return the value of the private variables
		*/

		Vector3 GetCameraPos(){ return camera_pos; };
		Vector3 GetCameraLookAt(){ return camera_look_at; };

		void isTerrainCollision(int H);

	private:
		/**
		* Set the camera pos and rot to the new values and update camera look at
		* @param new position vector of the camera
		* @param new rotation vector of the camera
		*/
		void MoveTo(const Vector3 & new_pos, const Vector3 & new_rot);

		/**
		* Update camera look at vector
		*/
		void UpdateLookAt();

		/**
		* Simulate the movement
		* @param the amount of the movement
		*/
		Vector3 PreviewMove(const Vector3 & amount);

		/**
		* Call MoveTo function passing the scale value(simulate movement of move_vec) and rotation
		* @param vector that simulated movement with move_vec
		*/
		void Move(const Vector3 & scale);

		/**
		* Run through all the movement calculation, with no fast movement on diag move(FB + LR move together -> spd up)
		* Normalize the move vector and multiply the movement spd with dt
		* Call Move() function and calculate through all the movement calculation
		*/
		void PreventFastDiagMove();

		/// camera position x,y,z
		Vector3 camera_pos;

		/// camera rotation x,y,z
		Vector3 camera_rot;

		/// camera movement speed without delta time - different pc cause different spd
		const double camera_mov_spd = 50.0;

		/// camera movement speed with delta time - different pc cause different spd
		double camera_mov_spd_with_dt;

		/// camera rotate speed without delta time - different pc cause different spd
		const double camera_rot_spd = 20.0;

		/// camera rotate speed with delta time - different pc cause different spd
		double camera_rot_spd_with_dt;

		/// vector that the camera is looking at
		Vector3 camera_look_at;

		/// vector that the camera is going to move to
		Vector3 move_vector;

		/// true if is having front back movement, false otherwise
		bool is_moving_fb;

		/// true if is having left right movement, false otherwise
		bool is_moving_lr;

		/// vector that the camera is going to rotate to
		Vector3 rotation_buffer;

		/// true if is having camera rotation, false otherwise
		bool is_rotating;
};

#endif