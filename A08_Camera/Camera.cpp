#include "Camera.h"


//Camera class constructor
Camera::Camera()
{
	positionV3 = vector3(0.0f, 2.5f, 15.0f);
	targetV3 = vector3(0.0f, 2.5f, 0.0f);
	upV3 = vector3(0.0f, 1.0f, 0.0f);
	projectionM4 = glm::perspective(90.0f, 1024.0f / 768.0f, 0.01f, 1000.0f);
	viewM4 = glm::lookAt(positionV3, targetV3, upV3);
}

//Function to Get the view matrix
matrix4 Camera::GetView(void)
{
	viewM4 = glm::lookAt(positionV3, targetV3, upV3);
	return viewM4;
}

//Function to get the Projection matrix in ortho or perspective mode
matrix4 Camera::GetProjection(bool bOrthographic)
{
	if (bOrthographic == true) 
	{
		projectionM4 = glm::ortho(0.0f, 4.0f, 0.0f, 2.5f, 0.01f, 1000.0f);
		return projectionM4;
	}
	else 
	{
		projectionM4 = glm::perspective(90.0f, 4.0f / 2.5f, 0.01f, 1000.0f);
		return projectionM4;
	}
}

//Set the position vector for the view matrix
void Camera::SetPosition(vector3 v3Position)
{
	positionV3 = v3Position;
}

//Set the target vector for the view matrix
void Camera::SetTarget(vector3 v3Target)
{
	targetV3 = v3Target;
}

//Set the up vector for the view matrix
void Camera::SetUp(vector3 v3Up)
{
	upV3 = v3Up;
}

//Move the camera forward by an increment
void Camera::MoveForward(float fIncrement)
{
	positionV3.z += fIncrement;
}

//Move the camera sideways by an increment
void Camera::MoveSideways(float fIncrement)
{
	positionV3.x += fIncrement;
}

//Move the camera vertical depending on the up vector by an increment
void Camera::MoveVertical(float fIncrement)
{
	if (upV3.x == 1) {
		positionV3.x += fIncrement;
	} else if (upV3.y == 1) {
		positionV3.y += fIncrement;
	} else if (upV3.z == 1) {
		positionV3.z += fIncrement;
	} else if (upV3.x == -1) {
		positionV3.x -= fIncrement;
	} else if (upV3.y == -1) {
		positionV3.y -= fIncrement;
	} else if (upV3.z == -1) {
		positionV3.z -= fIncrement;
	}
	
}

//Rotate the cameras pitch
void Camera::ChangePitch(float fIncrement)
{

}

//Rotate the cameras roll
void Camera::ChangeRoll(float fIncrement)
{

}

//Rotate the cameras yaw
void Camera::ChangeYaw(float fIncrement)
{

}

Camera::~Camera()
{
}
