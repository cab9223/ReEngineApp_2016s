#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;

	//Set the percentage for the translation
	static float fPercentageT = 0.0f;

	//Set the quaternion rotation angles
	quaternion qz1 = glm::angleAxis(0.0f, REAXISZ);
	quaternion qz2 = glm::angleAxis(359.9f, REAXISZ);

	//Map the timer with the amount of Z rotation
	float fPercentageZ = MapValue(fTimer, 0.0f, 2.0f, 0.0f, 2.0f);

	//Map the timer with the amount of translation depending on the timer
	if (fTimer < 1.0) {
		fPercentageT = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 3.0f);
	}
	else if (fTimer < 2.0) {
		fPercentageT = MapValue(fTimer, 1.0f, 2.0f, 3.0f, 0.0f);
	}
	else {
		fTimer = 0;
	}

	//slerp the quaternions with by the percentage
	quaternion rotZ = glm::mix(qz1, qz2, fPercentageZ);

	//Multiply everything together for the modelMatrix
	modelMatrix = glm::translate(modelMatrix, vector3(0.0f,fPercentageT, 0.0f)) *  glm::mat4_cast(rotZ);
#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

