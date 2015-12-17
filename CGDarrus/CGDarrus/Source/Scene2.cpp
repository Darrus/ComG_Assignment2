#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here

	rotateAngle = 1.0f;
	translateX = 10.0f;
	scaleAll = 0.5f;

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		-10.0f, 0.0f, 0.0f, //vertex 0 of triangle
		0.0f, 10.0f, 0.0f,
		10.0f, 0.0f, 0.0f,
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");

	// Use our shader
	glUseProgram(m_programID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		scaleAll += (float)(1 * dt);
		if (scaleAll > 3)
		{
			scaleAll = 1;
		}
		if (rotateAngle > 45)
		{
			left = false;
			right = true;
		}
		else if (rotateAngle < 0)
		{
			right = false;
			left = true;
		}
		if (left == true)
		{
			rotateAngle += (float)(10 * dt);
		}
		else if (right == true)
		{
			rotateAngle -= (float)(10 * dt);
		}
		translateX += (float)(10 * dt);
		if (translateX > 40)
		{
			translateX = -40;
		}
	}
}

void Scene2::Render()
{
	// Render VBO here
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-40, 40, -30, 30, -10, 10);

	///////////////////// First Triangle /////////////////////////////

	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex)
		3, // Size
		GL_FLOAT, // Type
		GL_TRUE, // Normalized
		0, // Stride
		0 // array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 Vertices = 1 Triangle

	///////////////////// Second Triangle /////////////////////////////

	translate.SetToTranslation(translateX, 0, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex)
		3, // Size
		GL_FLOAT, // Type
		GL_TRUE, // Normalized
		0, // Stride
		0 // array buffer offset
		);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 Vertices = 1 Triangle


	///////////////////// Third Triangle /////////////////////////////

	scale.SetToScale(scaleAll, scaleAll, 0);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(30, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex)
		3, // Size
		GL_FLOAT, // Type
		GL_TRUE, // Normalized
		0, // Stride
		0 // array buffer offset
		);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 Vertices = 1 Triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
