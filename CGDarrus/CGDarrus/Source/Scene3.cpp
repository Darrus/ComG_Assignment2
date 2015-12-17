#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "MeshBuilder.h"
#include "Application.h"

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Initialize camera settings
	
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference",1000,1000,1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1,0,0), 1, 1, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(1,0,0), 1, 1);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("Circle", Color(1,0,0), 36);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("Ring", Color(1, 0, 0), 3.f, 36);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", Color(1, 0, 1), 18, 36);

	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene3::Update(double dt)
{
	camera.Update(dt);
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	
}

void Scene3::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 translate, rotate, scale;
	Mtx44 MVP;

	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//Set view matrix using camera settings
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
					);

	//Set projection matrix to perspective mode
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane
	
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	//scale.SetToScale(1, 1, 1);
	//rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToIdentity();
	//model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	//MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	//glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	////Render call setup
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CUBE]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CUBE]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////Actual render call
	////glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[GEO_CUBE]);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	model.SetToIdentity();
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();

	/*model.settoidentity();
	translate.settotranslation(2, 0, 0);
	scale.settoscale(0.5, 0.5, 0.5);
	model = translate * scale;
	mvp = projection * view * model;
	gluniformmatrix4fv(m_parameters[u_mvp], 1, gl_false, &mvp.a[0]);
	meshlist[geo_cube]->render();*/

	/*model.settoidentity();
	scale.settoscale(0.5, 0.5, 0.5);
	model = scale;
	mvp = projection * view * model;
	gluniformmatrix4fv(m_parameters[u_mvp], 1, gl_false, &mvp.a[0]);
	meshlist[geo_quad]->render();*/

	/*model.SetToIdentity();
	scale.SetToScale(0.5, 0.5, 0.5);
	model = scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_CIRCLE]->Render();*/

	/*model.SetToIdentity();
	scale.SetToScale(0.5, 0.5, 0.5);
	model = scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_RING]->Render();*/

	model.SetToIdentity();
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
