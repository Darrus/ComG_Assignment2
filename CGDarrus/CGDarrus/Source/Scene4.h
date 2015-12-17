#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene4 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,
		GEO_PLANET1,
		GEO_PLANET2,
		GEO_PLANET3,
		GEO_PLANET4,
		GEO_PLANET5,
		GEO_PLANET6,
		GEO_PLANET7,
		GEO_PLANET8,
		GEO_PLANET9,
		GEO_SUN1,
		GEO_MOON1,
		GEO_RING1,
		GEO_RING2,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float planet1RevAngle, planetRotAngle, moon1RevAngle, moon1RotAngle, planet2RevAngle, planet3RevAngle,
		planet4RevAngle, planet5RevAngle, planet6RevAngle, planet7RevAngle, planet8RevAngle, planet9RevAngle;
	Camera camera;

	MS modelStack, viewStack, projectionStack;
};

#endif