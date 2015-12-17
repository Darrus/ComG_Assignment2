#include "MeshBuilder.h"
#include "Vertex.h"
#include "MyMath.h"
#include <GL\glew.h>
#include <vector>


/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, -lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, -lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 6;
	mesh->mode = Mesh::DRAW_LINES;
	
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//Front
	v.pos.Set(lengthX, 0, -lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, 0, -lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, 0, lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);


	for (int a = 0; a < 4; a++)
	{
		index_buffer_data.push_back(a);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 4;
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//Front
	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	

	//Back
	v.pos.Set(-lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);


	//Right
	v.pos.Set(lengthX, -lengthY, lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);
	v.normal.Set(1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	//Left
	v.pos.Set(-lengthX, lengthY, lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);
	v.normal.Set(-1, 0, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	//Bottom
	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, -lengthY, -lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	//Top
	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, lengthY, lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	for (int a = 0; a < 36; a++)
	{
		index_buffer_data.push_back(a);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float CircleX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}

float CircleZ(float theta)
{
	return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0 , CircleZ(theta));
		v.normal.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0, 0, 0);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(slice);
		index_buffer_data.push_back(numSlices + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		float theta = slice * anglePerSlice;

		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.normal.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerRadius * CircleX(theta), 0, innerRadius * CircleZ(theta));
		v.normal.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlices + 1; slice++)
	{
		index_buffer_data.push_back(2 * slice);
		index_buffer_data.push_back(2 * slice + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices, float height)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(0, 0, 0);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, height, 0);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.normal.Set(0, -1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}
	

	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.normal.Set(height * CircleX(theta), 1, height * CircleZ(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}
	
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 2);
	}
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(slice + (numSlices + 3));
		index_buffer_data.push_back(1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone2(const std::string &meshName, Color color, unsigned numSlices, float height, float degree)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(0, 0, 0);
	v.normal.Set(0, -1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, height, 0);
	v.normal.Set(0, 1, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	float anglePerSlice = 360.f / numSlices;
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.normal.Set(0, -1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}


	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.normal.Set(height * CircleX(theta), 1, height * CircleZ(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 2);
	}
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(slice + (numSlices + 3));
		index_buffer_data.push_back(1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float SphereY(float phi)
{
	return sin(Math::DegreeToRadian(phi));
}
float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices , bool hemi)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	float anglePerStack = 180.f / numStacks;
	float anglePerSlice = 360.f / numSlices;
	if (hemi == false)
	{
		for (unsigned stack = 0; stack <= numStacks; stack++)
		{
			float phi = -90 + stack * anglePerStack;
			for (unsigned slice = 0; slice <= numSlices; slice++)
			{
				float theta = slice * anglePerSlice;
				v.pos.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
				v.color = color;
				v.normal.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
				vertex_buffer_data.push_back(v);
			}
		}

		for (unsigned stack = 0; stack <= numStacks; stack++)
		{
			for (unsigned slice = 0; slice <= numSlices; slice++)
			{
				index_buffer_data.push_back(stack * (numSlices + 1) + slice);
				index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
			}
		}
	}
	else
	{
		for (unsigned stack = 0; stack <= numStacks; stack++)
		{
			float phi = stack * anglePerStack;
			for (unsigned slice = 0; slice <= numSlices; slice++)
			{
				float theta = slice * anglePerSlice;
				v.pos.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
				v.color = color;
				v.normal.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
				vertex_buffer_data.push_back(v);
			}
		}

		v.pos.Set(0, 0, 0);
		v.normal.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta), 0, CircleZ(theta));
			v.normal.Set(0, 1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);
		}

		for (unsigned stack = 0; stack < numStacks; stack++)
		{
			for (unsigned slice = 0; slice <= numSlices; slice++)
			{
				index_buffer_data.push_back(stack * (numSlices + 1) + slice);
				index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
			}
		}
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			index_buffer_data.push_back(((numStacks)+1) * (numSlices + 1));
			index_buffer_data.push_back(((numStacks) + 1) * (numSlices + 1) + slice + 1);
		}
	}
	

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
Mesh* MeshBuilder::GenerateHollowHemiSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float thickness)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	float anglePerStack = 180.f / numStacks;
	float anglePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack <= numStacks; stack++)
	{
		float phi = stack * anglePerStack;
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
			v.color = color;
			v.normal.Set(SphereX(phi, theta), SphereY(phi), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float Radius, float Thickness)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	float anglePerStack = 360.f / numStacks;
	float anglePerSlice = 360.f / numSlices;
	for (unsigned stack = 0; stack <= numStacks; stack++)
	{
		float phi = stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; slice++)
		{
			float theta = slice * anglePerSlice;
			float x = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * cos(Math::DegreeToRadian(phi));
			float y = Thickness * sin(Math::DegreeToRadian(theta));
			float z = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * -sin(Math::DegreeToRadian(phi));
			v.pos.Set(x, y, z);
			v.normal.Set(x, y, z);
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus2(const std::string &meshName, Color color, unsigned degree, unsigned numSlices, float Radius, float Thickness)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	float anglePerStack = 10.f;
	float anglePerSlice = 360.f / numSlices;
	unsigned numStacks = degree / 10;

	v.pos.Set(Radius, 0, 0);
	v.normal.Set(0, 0, 1);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(Radius * cos(Math::DegreeToRadian(degree)), 0, Radius * -sin(Math::DegreeToRadian(degree)));
	v.normal.Set(0, 0, -1);
	v.color = color;
	vertex_buffer_data.push_back(v);


	//Start Cover
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(Radius + Thickness * CircleX(theta), Thickness * CircleZ(theta), 0);
		v.normal.Set(0, 0, 1);
		v.color = color;
		vertex_buffer_data.push_back(v);

		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 2);
	}

	for (unsigned stack = 0; stack <= numStacks; stack++)
	{
		float phi = stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; slice++)
		{
			float theta = slice * anglePerSlice;
			float x = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * cos(Math::DegreeToRadian(phi));
			float y = Thickness * sin(Math::DegreeToRadian(theta));
			float z = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * -sin(Math::DegreeToRadian(phi));
			v.pos.Set(x, y, z);
			v.normal.Set(x, y, z);
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice + (numSlices + 3));
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice + (numSlices + 3));
		}
	}


	//Back Cover
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		float x = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * cos(Math::DegreeToRadian(degree));
		float y = Thickness * sin(Math::DegreeToRadian(theta));
		float z = (Radius + Thickness * cos(Math::DegreeToRadian(theta))) * -sin(Math::DegreeToRadian(degree));
		v.pos.Set(x,y,z);
		v.normal.Set(0, 0, -1);
		v.color = color;
		vertex_buffer_data.push_back(v);

		index_buffer_data.push_back(numStacks * (numSlices + 1) + (numSlices + 4) + slice);
		index_buffer_data.push_back(1);
		
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCyclinder(const std::string &meshName, Color color, unsigned numSlices, float height, bool innerCyclinder, float innerRadius, float thickness)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.f / numSlices;
	if (innerCyclinder == false)
	{
		v.pos.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height, 0);
		v.normal.Set(0, 1, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);


		//Bottom
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta), 0, CircleZ(theta));
			v.normal.Set(0, -1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(0);
			index_buffer_data.push_back(slice + 2);
		}

		//Sides
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta), 0, CircleZ(theta));
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(CircleX(theta), height, CircleZ(theta));
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back((slice * 2) + (numSlices + 3));
			index_buffer_data.push_back((slice * 2) + (numSlices + 4));
		}

		//Top
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta), height, CircleZ(theta));
			v.normal.Set(0, 1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(slice + (numSlices * 3 + 5));
			index_buffer_data.push_back(1);
		}
	}
	else
	{
		//Lower Ring
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta) * innerRadius, 0, CircleZ(theta) * innerRadius);
			v.normal.Set(0, -1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(CircleX(theta) * (innerRadius + thickness), 0, CircleZ(theta) * (innerRadius + thickness));
			v.normal.Set(0, -1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

	     	index_buffer_data.push_back(index_buffer_data.size());
			index_buffer_data.push_back(index_buffer_data.size());

		}

		//Outer Cylinder
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta) * (innerRadius + thickness), 0, CircleZ(theta) * (innerRadius + thickness));
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(CircleX(theta) * (innerRadius + thickness), height, CircleZ(theta) * (innerRadius + thickness));
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(index_buffer_data.size());
			index_buffer_data.push_back(index_buffer_data.size());
		}

		//Upper Ring
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta) * (innerRadius + thickness), height, CircleZ(theta) * (innerRadius + thickness));
			v.normal.Set(0, 1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(CircleX(theta) * innerRadius, height, CircleZ(theta) * innerRadius);
			v.normal.Set(0, 1, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(index_buffer_data.size());
			index_buffer_data.push_back(index_buffer_data.size());
		}

		//Inner Cylinder
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(CircleX(theta) * innerRadius, height, CircleZ(theta) * innerRadius);
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(CircleX(theta) * innerRadius, 0, CircleZ(theta) * innerRadius);
			v.normal.Set(CircleX(theta), 0, CircleZ(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			

			index_buffer_data.push_back(index_buffer_data.size());
			index_buffer_data.push_back(index_buffer_data.size());
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}