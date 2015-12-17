#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MyMath.h"
#include "Mtx44.h"
#include "Utility.h"
#include "MeshBuilder.h"
#include "Application.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	enableLight = true;
	readyToUse = 2.f;
	cForward.Set(0, 0, 1);
	cPosition.Set(0, -5.5f, 0);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Camera Init
	camera.Init(Vector3(0, 0, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Matrix Stack Init
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 10, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	light[1].position.Set(0, 10, 0);
	light[1].color.Set(1, 0, 0);
	light[1].power = 5;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;

	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Lightball", Color(1, 1, 1), 18, 36);
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("Floor", Color(0, 1, 0), 500, 500);

	//Full Clock
	meshList[GEO_CLOCK] = MeshBuilder::GenerateCyclinder("Clock", Color(1, 1, 1), 36, 1);
	meshList[GEO_HANDLE] = MeshBuilder::GenerateCone("Rod", Color(0, 0, 1), 36, 5);
	meshList[GEO_CPART] = MeshBuilder::GenerateTorus("Clock Torus", Color(0.635f, 0.58f, 0.475f), 36, 36, 1, 0.5);
	meshList[GEO_CLOCKRIM] = MeshBuilder::GenerateCyclinder("Clock Rim", Color(0.635f, 0.58f, 0.475f), 36, 1, true, 1.f, 0.2f);
	meshList[GEO_CLOCKBTN] = MeshBuilder::GenerateCyclinder("Clock Button", Color(0.635f, 0.58f, 0.475f), 36, 1);
	meshList[GEO_HILT] = MeshBuilder::GenerateTorus2("Clock Hilt", Color(0.635f, 0.58f, 0.475f), 180, 4, 2.5f, 1);
	meshList[GEO_DIAMOND] = MeshBuilder::GenerateSphere("Diamond", Color(0.957f, 0.66f, 0.824f), 2, 4);
	meshList[GEO_DIAMOND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_DIAMOND]->material.kShininess = 1;
	meshList[GEO_CLOCKHAND] = MeshBuilder::GenerateCube("Clock Hand", Color(0, 0, 0), 4, 1, 1);
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateSphere("Hemisphere", Color(0, 0, 0), 36, 36, true);

	//Enviroments
	meshList[GEO_TRUNK] = MeshBuilder::GenerateCyclinder("Tree Trunk", Color(0, 1, 0), 36, 4);
	meshList[GEO_LEAF] = MeshBuilder::GenerateSphere("Tree Leaves", Color(0, 1, 0), 36, 36, true);
	meshList[GEO_ROOT] = MeshBuilder::GenerateTorus2("Tree Roots", Color(0, 1, 0), 180, 36, 2, 1);
	
	//Moogle
	meshList[GEO_WHITESPHERE] = MeshBuilder::GenerateSphere("Moogle Head", Color(1, 1, 1), 36, 36);
	meshList[GEO_REDSPHERE] = MeshBuilder::GenerateSphere("Moogle Nose", Color(1, 0, 0), 36, 36);
	meshList[GEO_WINGFRAME] = MeshBuilder::GenerateCyclinder("Wing Frame", Color(0, 0, 1), 36, 10);
	meshList[GEO_WINGFRAME2] = MeshBuilder::GenerateCone("Wing Frame 2", Color(0, 0, 1), 36, 10);
	meshList[GEO_WING] = MeshBuilder::GenerateCyclinder("Wing", Color(0, 0, 1), 3, 0.2f);
	meshList[GEO_ANTENNA] = MeshBuilder::GenerateTorus2("Antenna", Color(0, 0, 0), 45, 36, 10, 0.1f);
	meshList[GEO_EARS] = MeshBuilder::GenerateHollowHemiSphere("Ear", Color(1, 1, 1), 36, 36, 1);

}

static float LSPEED = 10.f;

void Assignment2::Update(double dt)
{
	camera.Update(dt);
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('U'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y += (float)(LSPEED * dt);

	//Enable Light
	if (Application::IsKeyPressed(VK_SPACE) && readyToUse >= 3.f)
	{
		readyToUse = 0.f;
		if (enableLight)
			enableLight = false;
		else
			enableLight = true;
	}
	else if(readyToUse < 3.f)
		readyToUse += (float)(10 * dt);

	//Enable Axis
	if (Application::IsKeyPressed('X') && readyToUse >= 3.f)
	{
		readyToUse = 0.f;
		if (enableAxis)
			enableAxis = false;
		else
			enableAxis = true;
	}
	else if (readyToUse < 3.f)
		readyToUse += (float)(10 * dt);

	//Clock Rotation
	smallHandRotation -= (float)(10 * dt);
	bigHandRotation -= (float)(30 * dt);

	//Flying Animation
	if (Application::IsKeyPressed(VK_NUMPAD9))
	{
		if (leftWingFlap * leftWingDirection > 20)
			leftWingDirection = -leftWingDirection;
		leftWingFlap += (float)(leftWingDirection * 800 * dt);

		if (rightWingFlap * rightWingDirection > 20)
			rightWingDirection = -rightWingDirection;
		rightWingFlap += (float)(rightWingDirection * 800 * dt);

		y += (float)(15 * dt);
	}
	else
	{
		if (y >= 0)
		{
			if (leftWingFlap * leftWingDirection > 20)
				leftWingDirection = -leftWingDirection;
			leftWingFlap += (float)(leftWingDirection * 250 * dt);

			if (rightWingFlap * rightWingDirection > 20)
				rightWingDirection = -rightWingDirection;
			rightWingFlap += (float)(rightWingDirection * 250 * dt);

			y -= (float)(20 * dt);
		}
		else
		{
			rightWingFlap = 0;
			leftWingFlap = 0;
		}
	}

	if (Application::IsKeyPressed(VK_NUMPAD6))
	{
		rotateY -= (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_NUMPAD4))
	{
		rotateY += (float)(100 * dt);
	}

	//Walking Animation
	if (Application::IsKeyPressed(VK_NUMPAD8) || Application::IsKeyPressed(VK_NUMPAD5))
	{
		if (rotateHand1 * directionObject1 > 15)
			directionObject1 = -directionObject1;
		rotateHand1 += (float)(directionObject1 * 100 * dt);

		if (rotateHand2 * directionObject2 > 15)
			directionObject2 = -directionObject2;
		rotateHand2 += (float)(directionObject2 * 100 * dt);
		
		if (Application::IsKeyPressed(VK_NUMPAD8))
		{
			Mtx44 rotation;
			rotation.SetToRotation(rotateY, 0, 1, 0);
			cPosition += (rotation * cForward) * 10 * dt;
		}
		else if (Application::IsKeyPressed(VK_NUMPAD5))
		{
			Mtx44 rotation;
			rotation.SetToRotation(rotateY, 0, 1, 0);
			cPosition -= (rotation * cForward) * 10 * dt;
		}
		
	}
	else
	{
		rotateHand1 = 0;
		rotateHand2 = 0;
	}

	//Nose Wiggle
	if (noseWaitTime >= 4)
	{
		if (nose * noseDirection > 0.05)
			noseDirection = -noseDirection;
		nose += (float)(noseDirection * 2 * dt);
		noseWaitTime += (float)(1 * dt);
		if (noseWaitTime >= 5)
		{
			noseWaitTime = 0;
		}
	}
	else
	{
		noseWaitTime += (float)(1 * dt);
	}

	//Ears Wiggle
	if (earWaitTime >= 2)
	{
		if (leftEar * leftEarDirection > 30)
			leftEarDirection = -leftEarDirection;
		leftEar += (float)(leftEarDirection * 60 * dt);

		if (rightEar * rightEarDirection > 30)
			rightEarDirection = -rightEarDirection;
		rightEar += (float)(rightEarDirection * 60 * dt);

		earWaitTime += (float)(1 * dt);

		if (earWaitTime >= 4)
		{
			earWaitTime = 0;
		}
	}
	else
	{
		earWaitTime += (float)(1 * dt);
	}

}

void Assignment2::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void Assignment2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	/*lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);*/

	//Standard Inits
	if (enableAxis == true)
	{
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_AXES], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//Enviromental
	generateEnviroment();

	


	modelStack.PushMatrix();
	modelStack.Translate(cPosition.x, cPosition.y + y, cPosition.z);
	modelStack.Rotate(rotateY, 0, 1, 0);

	//Full Clock
	modelStack.PushMatrix();
	modelStack.Rotate(-rotateHand1, 1, 0, 0);
	modelStack.Translate(-4, -4, 4);
	modelStack.Rotate(90, 1, 0, 0);
	generateWand();
	modelStack.PopMatrix();

	//Moogle!
	modelStack.PushMatrix();
	modelStack.Translate(0, 4.5f, 0);
	generateHead();
	modelStack.PopMatrix();

	//Body
	modelStack.PushMatrix();
	modelStack.Translate(0, -3.2f, 0);
	modelStack.Scale(3.0f, 3.8f, 3.2f);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack.PopMatrix();

	//Right Hand
	modelStack.PushMatrix();
	modelStack.Translate(3.f, -2.2f, 0);
	modelStack.Rotate(30, 0, 0, 1);
	modelStack.Translate(2, 2.2f, 0);
	modelStack.Rotate(rotateHand1, 1, 0, 0);
	modelStack.Translate(-2, -2.2f, 0);
	modelStack.Scale(1, 2.5f, 1);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack.PopMatrix();

	//Left Hand
	modelStack.PushMatrix();
	modelStack.Translate(-3.f, -2.2f, 0);
	modelStack.Rotate(-30, 0, 0, 1);
	modelStack.Translate(-2, 2.2f, 0);
	modelStack.Rotate(rotateHand2, 1, 0, 0);
	modelStack.Translate(2, -2.2f, 0);
	modelStack.Scale(1, 2.5f, 1);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack.PopMatrix();

	//Left Leg
	modelStack.PushMatrix();
	modelStack.Translate(-1.7f, -7.5f, 0);
	modelStack.Translate(1.7f, 3.f, 0);
	modelStack.Rotate(rotateHand1, 1, 0, 0);
	modelStack.Translate(-1.7f, -3.f, 0);
	modelStack.Scale(1.3f, 2.f, 1.3f);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack .PopMatrix();

	//Right Leg
	modelStack.PushMatrix();
	modelStack.Translate(1.7f, -7.5f, 0);
	modelStack.Translate(-1.7f, 3.f, 0);
	modelStack.Rotate(rotateHand2, 1, 0, 0);
	modelStack.Translate(1.7f, -3.f, 0);
	modelStack.Scale(1.3f, 2.f, 1.3f);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack.PopMatrix();
	
	//Left Wing
	modelStack.PushMatrix();
	modelStack.Translate(-1.4f, -0.3f, -1.2f);
	modelStack.Rotate(leftWingFlap, 0, 1, 0);
	generateLeftWing();
	modelStack.PopMatrix();

	//Right Wing
	modelStack.PushMatrix();
	modelStack.Translate(1.4f, -0.3f, -1.2f);
	modelStack.Rotate(rightWingFlap, 0, 1, 0);
	generateRightWing();
	modelStack.PopMatrix();

	//Antenna
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 9.5f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_ANTENNA], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 13, 3);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_REDSPHERE], enableLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	
	
	
}

void Assignment2::generateWand()
{
	//Clock
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.55f, -0.4f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2.1f, 0.8f, 2.1f);
	RenderMesh(meshList[GEO_CLOCK], enableLight);
	modelStack.PopMatrix();

	//Outer Rim
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.58f, -0.6f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2.f, 1.2f, 2.f);
	RenderMesh(meshList[GEO_CLOCKRIM], enableLight);
	modelStack.PopMatrix();

	//Rod
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(0.5f, 3.f, 0.5f);
	RenderMesh(meshList[GEO_HANDLE], enableLight);
	modelStack.PopMatrix();

	//Rod Rings
	modelStack.PushMatrix();
	modelStack.Scale(0.4f, 0.4f, 0.4f);
	RenderMesh(meshList[GEO_CPART], enableLight);

	modelStack.Translate(0, -0.8f, 0);
	modelStack.Scale(0.95f, 0.95f, 0.95f);
	RenderMesh(meshList[GEO_CPART], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.25f, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.5f, 0.2f, 0.2f);
	RenderMesh(meshList[GEO_HILT], enableLight);
	modelStack.PopMatrix();


	//Clock Buttons
	modelStack.PushMatrix();
	modelStack.Translate(-2.4f, 2.6f, 0.f);
	modelStack.Rotate(90, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Scale(0.4f, 0.15f, 0.4f);
	RenderMesh(meshList[GEO_CLOCKBTN], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.3f, 0.35f, 0.3f);
	RenderMesh(meshList[GEO_CLOCKBTN], enableLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//Diamond
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 6.f, 0.f);
	modelStack.Scale(0.5f, 0.8f, 0.5f);
	RenderMesh(meshList[GEO_DIAMOND], enableLight);
	modelStack.PopMatrix();

	//Clock Hand
	modelStack.PushMatrix();
	modelStack.Translate(0.6f, 2.55f, 0.4f);
	modelStack.Translate(-0.6f, 0.f, 0.f);
	modelStack.Rotate(smallHandRotation, 0, 0, 1);
	modelStack.Translate(0.6f, 0, 0);
	modelStack.Scale(0.15f, 0.15f, 0.1f);
	RenderMesh(meshList[GEO_CLOCKHAND], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.75f, 2.55f, 0.4f);
	modelStack.Translate(-0.75f, 0.f, 0.f);
	modelStack.Rotate(bigHandRotation, 0, 0, 1);
	modelStack.Translate(0.75f, 0, 0);
	modelStack.Scale(0.2f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_CLOCKHAND], enableLight);
	modelStack.PopMatrix();

	//Clock knob
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.5f, 0.4f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.25f, 0.25f, 0.25f);
	RenderMesh(meshList[GEO_HEMISPHERE], enableLight);
	modelStack.PopMatrix();
}

void Assignment2::generateEnviroment()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -15, 0);
	RenderMesh(meshList[GEO_FLOOR], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -15, -50);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_TRUNK], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 50, -50);
	modelStack.Scale(100, 100, 100);
	RenderMesh(meshList[GEO_LEAF], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, -18, -20);
	modelStack.Rotate(45, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROOT], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30, -18, -20);
	modelStack.Rotate(-45, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROOT], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, -18, -90);
	modelStack.Rotate(135, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_ROOT], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30, -18, -90);
	modelStack.Rotate(-135, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_ROOT], enableLight);
	modelStack.PopMatrix();
}

void Assignment2::generateHead()
{
	//Head
	modelStack.PushMatrix();
	modelStack.Scale(4.5f, 4.5f, 4.7f);
	RenderMesh(meshList[GEO_WHITESPHERE], enableLight);
	modelStack.PopMatrix();

	//Nose
	modelStack.PushMatrix();
	modelStack.Translate(0, nose, 5);
	modelStack.Scale(2.f, 1.5f, 1.5f);
	RenderMesh(meshList[GEO_REDSPHERE], enableLight);
	modelStack.PopMatrix();

	//Eyes
	modelStack.PushMatrix();
	modelStack.Translate(-2.3f, 1, 4.4f);
	modelStack.Scale(0.2f, 0.05f, 0.05f);
	RenderMesh(meshList[GEO_CLOCKHAND], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.3f, 1, 4.4f);
	modelStack.Scale(0.2f, 0.05f, 0.05f);
	RenderMesh(meshList[GEO_CLOCKHAND], enableLight);
	modelStack.PopMatrix();


	//Ears
	modelStack.PushMatrix();
	modelStack.Translate(-3, 3.5f, 0);
	modelStack.Translate(0, -0.3f, 0);
	modelStack.Rotate(50 + leftEar, 0, 0, 1);
	modelStack.Translate(0, 0.4f, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.7);
	RenderMesh(meshList[GEO_EARS], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3, 3.5f, 0);
	modelStack.Translate(0, -0.3f, 0);
	modelStack.Rotate(-50 + rightEar, 0, 0, 1);
	modelStack.Translate(0, 0.4f, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.7);
	RenderMesh(meshList[GEO_EARS], enableLight);
	modelStack.PopMatrix();
}

void Assignment2::generateLeftWing()
{
	modelStack.PushMatrix();
	modelStack.Rotate(-25, 0, 1, 0);
	modelStack.Rotate(70, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.55f, 1, -1.2f);
	modelStack.Rotate(-25, 0, 1, 0);
	modelStack.Rotate(130, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.55f, 1, -1.2f);
	modelStack.Rotate(-25, 0, 1, 0);
	modelStack.Rotate(-48, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.4f, 0.9f, -1.1f);
	modelStack.Rotate(-30, 0, 1, 0);
	modelStack.Rotate(168.5f, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.3f, 0.9f, -1.07f);
	modelStack.Rotate(-28, 0, 1, 0);
	modelStack.Rotate(210, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3.1f, -0.2f, -1.5f);
	modelStack.Rotate(-24, 0, 1, 0);
	modelStack.Rotate(60, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.15f, -0.45f, -1.f);
	modelStack.Rotate(-28, 0, 1, 0);
	modelStack.Rotate(99, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1.25f, 0.f, -0.55f);
	modelStack.Rotate(-25, 0, 1, 0);
	modelStack.Rotate(140, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();
}

void Assignment2::generateRightWing()
{
	modelStack.PushMatrix();
	modelStack.Rotate(25, 0, 1, 0);
	modelStack.Rotate(-70, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.55f, 1, -1.2f);
	modelStack.Rotate(25, 0, 1, 0);
	modelStack.Rotate(-130, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.55f, 1, -1.2f);
	modelStack.Rotate(25, 0, 1, 0);
	modelStack.Rotate(48, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.4f, 0.9f, -1.1f);
	modelStack.Rotate(30, 0, 1, 0);
	modelStack.Rotate(-168.5f, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(2.3f, 0.9f, -1.07f);
	modelStack.Rotate(28, 0, 1, 0);
	modelStack.Rotate(-210, 0, 0, 1);
	modelStack.Scale(0.1f, 0.3f, 0.1f);
	RenderMesh(meshList[GEO_WINGFRAME2], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3.1f, -0.2f, -1.5f);
	modelStack.Rotate(24, 0, 1, 0);
	modelStack.Rotate(122, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.15f, -0.45f, -1.f);
	modelStack.Rotate(28, 0, 1, 0);
	modelStack.Rotate(82, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.25f, 0.f, -0.55f);
	modelStack.Rotate(25, 0, 1, 0);
	modelStack.Rotate(40, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1.5f, 0.2f, 1.f);
	RenderMesh(meshList[GEO_WING], enableLight);
	modelStack.PopMatrix();
}

void Assignment2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
