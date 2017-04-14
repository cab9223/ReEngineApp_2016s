#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bobadilla, Alberto - Gimbal Lock");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}
void AppClass::InitVariables(void)
{
	//Loading the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");

	//Set the axis of Steve visible
	m_pMeshMngr->SetVisibleAxis(true, "Steve");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Rotation matrices
	//matrix4 rotX = glm::rotate(IDENTITY_M4, m_v3Orientation.x, REAXISX);
	//matrix4 rotY = glm::rotate(IDENTITY_M4, m_v3Orientation.y, REAXISY);
	//matrix4 rotZ = glm::rotate(IDENTITY_M4, m_v3Orientation.z, REAXISZ);


	quaternion qx1 = glm::angleAxis(0.0f, REAXISX);
	quaternion qy1 = glm::angleAxis(0.0f, REAXISY);
	quaternion qz1 = glm::angleAxis(0.0f, REAXISZ);

	quaternion qx2 = glm::angleAxis(359.9f, REAXISX);
	quaternion qy2 = glm::angleAxis(359.9f, REAXISY);
	quaternion qz2 = glm::angleAxis(359.9f, REAXISZ);

	float fPercentageX = MapValue(m_v3Orientation.x, 0.0f, 360.0f, 0.0f, 1.0f);
	float fPercentageY = MapValue(m_v3Orientation.y, 0.0f, 360.0f, 0.0f, 1.0f);
	float fPercentageZ = MapValue(m_v3Orientation.z, 0.0f, 360.0f, 0.0f, 1.0f);

	//linear combination
	//m_mToWorld = rotX * rotY * rotZ;


	quaternion rotX = glm::mix(qx1, qx2, fPercentageX);
	quaternion rotY = glm::mix(qy1, qy2, fPercentageY);
	quaternion rotZ = glm::mix(qz1, qz2, fPercentageZ);

	quaternion quatFinal = rotX * rotY * rotZ;

	//Setting the model matrix
	m_pMeshMngr->SetModelMatrix(ToMatrix4(quatFinal), "Steve");

	//Adding the instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve");

	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("X:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.x), RERED);
	m_pMeshMngr->Print("Y:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.y), RERED);
	m_pMeshMngr->Print("Z:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.z), RERED);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	m_pMeshMngr->Render(); //renders the list of meshes in the system.
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release();
}