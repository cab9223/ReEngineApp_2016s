#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera
{
private:
	glm::mat4 viewM4; //The camera view matrix
	glm::mat4 projectionM4; //The camera projection matrix
	vector3 positionV3; //Position vector for the view matrix
	vector3 targetV3; //Target vector for the view matrix
	vector3 upV3; //Up vector for the view matrix

public:
	//Function to Get the view matrix
	matrix4 GetView(void);
	//Function to get the Projection matrix in ortho or perspective mode
	matrix4 GetProjection(bool bOrthographic);
	//Set the position vector for the view matrix
	void SetPosition(vector3 v3Position);
	//Set the target vector for the view matrix
	void SetTarget(vector3 v3Target);
	//Set the up vector for the view matrix
	void SetUp(vector3 v3Up);
	//Move the camera forward by an increment
	void MoveForward(float fIncrement);
	//Move the camera sideways by an increment
	void MoveSideways(float fIncrement);
	//Move the camera vertical depending on the up vector by an increment
	void MoveVertical(float fIncrement);
	//Rotate the cameras pitch
	void ChangePitch(float fIncrement);
	//Rotate the cameras roll
	void ChangeRoll(float fIncrement);
	//Rotate the cameras yaw
	void ChangeYaw(float fIncrement);
	
	//Constructor
	Camera();
	//Destructor
	~Camera();
};

