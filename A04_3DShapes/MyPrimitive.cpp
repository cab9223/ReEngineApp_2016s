#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

//C
//|\
//| \
//A--B
//This will make the triang A->B->C
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//Initial variables and vectors
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / a_nSubdivisions;

	//First point
	point.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));

	for (int i = 0; i < a_nSubdivisions; i++) //Loop to create points
	{
		point.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), a_fHeight / -2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)//Loop to create geometric shapes for the points
	{
		AddQuad(point[0], point[i], point[i + 1], vector3(0,0, a_fHeight/2));
	}

	AddQuad(point[0], point[a_nSubdivisions], point[1], vector3(0, 0, a_fHeight/2));//Last geometric shape

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//Initial variables and vectors
	std::vector<vector3> point;
	std::vector<vector3> point2;
	float theta = 0;
	float steps = 2 * PI / a_nSubdivisions;

	//Each first point
	point.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));
	point2.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));

	for (int i = 0; i < a_nSubdivisions; i++)//Loop to create points
	{
		point.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), a_fHeight/2));
		point2.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), a_fHeight / -2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)//Loop to create geometric shapes for the points
	{
		AddTri(vector3(0, 0, a_fHeight/2), point[i], point[i+1]);
		AddTri(point2[i+1], point2[i], point2[0]);
		AddQuad(point[i + 1], point[i], point2[i + 1], point2[i]);
	}

	//Final geometric shapes
	AddTri(vector3(0, 0, a_fHeight/2), point[a_nSubdivisions], point[1]);
	AddTri(point2[1], point2[a_nSubdivisions], point2[0]);
	AddQuad(point[1], point[a_nSubdivisions], point2[1], point2[a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//Initial variables and vectors
	std::vector<vector3> point;
	std::vector<vector3> point2;
	std::vector<vector3> point3;
	std::vector<vector3> point4;
	float theta = 0;
	float steps = 2 * PI / a_nSubdivisions;

	//Each first point
	point.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));
	point2.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));
	point3.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));
	point4.push_back(vector3(0.0f, 0.0f, a_fHeight / -2));

	for (int i = 0; i < a_nSubdivisions; i++)//Loop to create points
	{
		point.push_back(vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), a_fHeight/2));
		point2.push_back(vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), a_fHeight / -2));
		point3.push_back(vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), a_fHeight/2));
		point4.push_back(vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), a_fHeight / -2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)//Loop to create geometric shapes for the points
	{
		AddQuad(point3[i+1], point3[i], point[i+1], point[i]);
		AddQuad(point4[i], point4[i + 1], point2[i], point2[i + 1]);
		AddQuad(point[i + 1], point[i], point2[i + 1], point2[i]);
		AddQuad(point3[i], point3[i+1], point4[i], point4[i+1]);
	}

	//Final geometric shapes
	AddQuad(point3[1], point3[a_nSubdivisions], point[1], point[a_nSubdivisions]);
	AddQuad(point4[a_nSubdivisions], point4[1], point2[a_nSubdivisions], point2[1]);
	AddQuad(point[1], point[a_nSubdivisions], point2[1], point2[a_nSubdivisions]);
	AddQuad(point3[a_nSubdivisions], point3[1], point4[a_nSubdivisions], point4[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 36)
		a_nSubdivisions = 36;

	Release();
	Init();

	//Your code starts here

	//Initial variables and vectors
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / a_nSubdivisions;

	point.push_back(vector3(0.0f, 0.0f, a_fRadius * -1));//First point

	for (int i = 0; i < a_nSubdivisions; i++)//Loop to create points
	{
		point.push_back(vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), 0));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)//Loop to create geometric shapes for the points
	{
		AddQuad(point[0], point[i], point[i + 1], vector3(0, 0, a_fRadius));
	}

	AddQuad(point[0], point[a_nSubdivisions], point[1], vector3(0, 0, a_fRadius));//Last geometric shape

	//Your code ends here
	CompileObject(a_v3Color);
}