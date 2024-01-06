/*
Camera class
Includes initializing camera position (input current camera position and lift Angle, yaw Angle, roll Angle and world direction vector/current camera position and camera direct target coordinates, world direction vector)
To calculate the Forward vector (normalized vector pointing from the camera to the target, that is, the camera's forward direction vector), the Right vector (right direction vector), the Up vector (up direction vector)
Note that all three above need to be normalized
Encapsulates access to ViewMatrix to convert from world coordinate system to camera coordinate system (view space)
Encapsulates the function of updating the camera's three unit direction vectors and camera position, for manipulating camera movement and rotation Angle through qweasd and mouse (but the rotation Angle should be aware of the gimblock problem)
*/

#include "Camera.h"

Camera::~Camera() {}

//The parameters are, in order, the camera position, the position of the object you want to see, and the vector of direction in the world
Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Forward = glm::normalize(_target - _position);	
	Right = glm::normalize(glm::cross(Forward, WorldUp));	
	Up = glm::normalize(glm::cross(Right, Forward));
}

//Instead of target, give it two Ola horns. pitch is the lift Angle (direction up, around the X-axis), yaw is the yaw Angle (clockwise from the top, around the Y-axis), roll is the roll Angle (around the z axis, counterclockwise from the positive Z-axis)
Camera::Camera(glm::vec3 _position, float _pitch, float _yaw, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Pitch = _pitch;
	Yaw = _yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix() {			//Parameters: camera position, viewing target position, world orientation
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessInputForCamera(glm::vec3 _position, glm::vec3 _target, glm::vec3 _worldup) {
	Position = _position;
	WorldUp = _worldup;
	Forward = glm::normalize(_target - _position);	
	Right = glm::normalize(glm::cross(Forward, WorldUp));	
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SenseY;
	Yaw -= deltaX * SenseX;
	printf("Pitch = %lf, yaw = %lf\n", Pitch, Yaw);
	UpdateCameraVectors();
}

void Camera::UpdateCameraPosition() {
	Position += Forward * speedZ * SenseZ + Right * speedX * SenseX + Up * speedY * SenseY;
}
