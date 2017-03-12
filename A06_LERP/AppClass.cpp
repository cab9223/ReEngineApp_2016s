#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

	//Array of vector3 points
	vector3 points[11] =
	{
		vector3(-4.0f,-2.0f, 5.0f),
		vector3(1.0f,-2.0f, 5.0f),
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};


	//Display spheres at all points
	for (int i = 0; i < 11; i++) {
		matrix4 m4SpherePosition = glm::translate(points[i]) * glm::scale(vector3(0.1));
		m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, RERED, SOLID);
	}


	//Setup the timer
	static DWORD timerSinceBoot = GetTickCount();
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot;
	float fTimer = timerSinceStart / 1000.0f;


	//declare some varibles
	vector3 v3Start;
	vector3 v3End;
	vector3 v3Current;
	matrix4 m4Creeper;


	//Use the map value to make 2 seconds an entire movement from point to point
	percentage = MapValue(fmod(fTimer, 2.0f), 0.0f, 2.0f, 0.0f, 1.0f);
	

	//If the percentage equals the next point, switch to the following point and restart percentage
	if (percentage > 0.99f) {
		percentage -= 1.0f;
		trigger = trigger + 1;
		if (trigger == 11) {
			trigger = 0;
		}
	}

	
	//Massive switch statement to handle each case of point to point movement
	switch (trigger) {
	case 0:
		v3Start = points[0]; //Set the start point
		v3End = points[1]; //Set the end point
		v3Current = glm::lerp(v3Start, v3End, percentage); //Use lerp to find the current location
		m4Creeper = glm::translate(v3Current); //Translate the matrix to the current location
		break;
	case 1:
		v3Start = points[1];
		v3End = points[2];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;       
	case 2:
		v3Start = points[2];
		v3End = points[3];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 3:
		v3Start = points[3];
		v3End = points[4];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 4:
		v3Start = points[4];
		v3End = points[5];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 5:
		v3Start = points[5];
		v3End = points[6];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 6:
		v3Start = points[6];
		v3End = points[7];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 7:
		v3Start = points[7];
		v3End = points[8];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 8:
		v3Start = points[8];
		v3End = points[9];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 9:
		v3Start = points[9];
		v3End = points[10];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	case 10:
		v3Start = points[10];
		v3End = points[0];
		v3Current = glm::lerp(v3Start, v3End, percentage);
		m4Creeper = glm::translate(v3Current);
		break;
	}


		//Apply the matrix onto the model in 3D space
		m_pMeshMngr->SetModelMatrix(m4Creeper, "WallEye");

		

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	//m_pMeshMngr->Print(std::to_string(percentage), REGREEN);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}