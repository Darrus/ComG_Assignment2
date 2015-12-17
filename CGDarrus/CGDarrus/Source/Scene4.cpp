#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "MeshBuilder.h"
#include "Application.h"

Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Camera Init
	camera.Init(Vector3(camera.position.x, camera.position.y, camera.position.z), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[0]);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Initialize camera settings

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1, 0, 0), 1, 1, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(1, 0, 0), 1, 1);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("Circle", Color(1, 0, 0), 36);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("Ring", Color(1, 0, 0), 3.f, 36);
	meshList[GEO_SUN1] = MeshBuilder::GenerateSphere("Sun", Color(1, 1, 0), 18, 36);
	meshList[GEO_PLANET1] = MeshBuilder::GenerateSphere("Mercury", Color(0.416f, 0.416f, 0.416f), 18, 36);
	meshList[GEO_PLANET2] = MeshBuilder::GenerateSphere("Venus", Color(0.988f, 0.427f, 0.027f), 18, 36);
	meshList[GEO_PLANET3] = MeshBuilder::GenerateSphere("Earth", Color(0.035f, 0.216f, 0.49f), 18, 36);
	meshList[GEO_PLANET4] = MeshBuilder::GenerateSphere("Mars", Color(0.851f, 0.592f, 0.365f), 18, 36);
	meshList[GEO_PLANET5] = MeshBuilder::GenerateSphere("Jupiter", Color(0.769f, 0.718f, 0.627f), 18, 36);
	meshList[GEO_PLANET6] = MeshBuilder::GenerateSphere("Saturn", Color(0.933f, 0.706f, 0.325f), 18, 36);
	meshList[GEO_PLANET7] = MeshBuilder::GenerateSphere("Uranus", Color(0.588f, 0.898f, 0.914f), 18, 36);
	meshList[GEO_PLANET8] = MeshBuilder::GenerateSphere("Neptune", Color(0.266f, 0.439f, 0.996f), 18, 36);
	meshList[GEO_PLANET9] = MeshBuilder::GenerateSphere("Pluto", Color(0.855f, 0.682f, 0.537f), 18, 36);
	meshList[GEO_MOON1] = MeshBuilder::GenerateSphere("Moon", Color(0.682f, 0.639f, 0.635f), 18, 36);
	meshList[GEO_RING1] = MeshBuilder::GenerateRing("SaturnRing", Color(0.506f, 0.38f, 0.298f), 0.8f, 20);
	meshList[GEO_RING2] = MeshBuilder::GenerateRing("SaturnRing", Color(0.506f, 0.38f, 0.298f), 0.8f, 20);
	
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene4::Update(double dt)
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

	planetRotAngle += (float)(10 * dt);

	planet1RevAngle += (float)(20 * dt);
	planet2RevAngle += (float)(15 * dt);
	planet3RevAngle += (float)(13 * dt);
	planet4RevAngle += (float)(10 * dt);
	planet5RevAngle += (float)(8 * dt);
	planet6RevAngle += (float)(7 * dt);
	planet7RevAngle += (float)(6 * dt);
	planet8RevAngle += (float)(5 * dt);
	planet9RevAngle += (float)(4 * dt);

	moon1RevAngle -= (float)(20 * dt);
	moon1RotAngle += (float)(10 * dt);
}

void Scene4::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	Mtx44 MVP;

	//Axes
	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();
	modelStack.PopMatrix();

	//Sun
	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SUN1]->Render();
	modelStack.PopMatrix();

	//Mecury
	modelStack.PushMatrix();
	modelStack.Rotate(planet1RevAngle, 0, 1, 0);
	modelStack.Translate(15, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET1]->Render();
	modelStack.PopMatrix();

	//Venus
	modelStack.PushMatrix();
	modelStack.Rotate(planet2RevAngle, 0, 1, 0);
	modelStack.Translate(20, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET2]->Render();
	modelStack.PopMatrix();

	//Earth
	modelStack.PushMatrix();
	modelStack.Rotate(planet3RevAngle, 0, 1, 0);
	modelStack.Translate(27, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET3]->Render();
	modelStack.PopMatrix();

	//Mars
	modelStack.PushMatrix();
	modelStack.Rotate(planet4RevAngle, 0, 1, 0);
	modelStack.Translate(35, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(2.5f, 2.5f, 2.5f);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET4]->Render();
	modelStack.PopMatrix();

	//Jupiter
	modelStack.PushMatrix();
	modelStack.Rotate(planet5RevAngle, 0, 1, 0);
	modelStack.Translate(45, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(6, 6, 6);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET5]->Render();
	modelStack.PopMatrix();

	//Saturn
	modelStack.PushMatrix();
	modelStack.Rotate(planet6RevAngle, 0, 1, 0);
	modelStack.Translate(60, 0, 0);

	modelStack.PushMatrix();
	modelStack.Rotate(moon1RotAngle, 0, 0, 1);
	modelStack.Rotate(moon1RevAngle, 0, 0, 1);
	modelStack.Translate(0, 10, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_MOON1]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	
	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET6]->Render();
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Scale(7, 7, 7);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_RING1]->Render();
	

	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_RING1]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	
	//Uranus
	modelStack.PushMatrix();
	modelStack.Rotate(planet7RevAngle, 0, 1, 0);
	modelStack.Translate(73, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET7]->Render();
	modelStack.PopMatrix();

	//Neptune
	modelStack.PushMatrix();
	modelStack.Rotate(planet8RevAngle, 0, 1, 0);
	modelStack.Translate(84, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);
	modelStack.Scale(4, 4, 4);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET8]->Render();
	modelStack.PopMatrix();

	//Pluto
	modelStack.PushMatrix();
	modelStack.Rotate(planet9RevAngle, 0, 1, 0);
	modelStack.Translate(90, 0, 0);
	modelStack.Rotate(planetRotAngle, 0, 1, 0);;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_PLANET9]->Render();
	modelStack.PopMatrix();

}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
