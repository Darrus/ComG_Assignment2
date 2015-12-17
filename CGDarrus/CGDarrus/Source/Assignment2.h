#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_TRUNK,
		GEO_LEAF,
		GEO_ROOT,
		GEO_FLOOR,

		GEO_CLOCK,
		GEO_CLOCKRIM,
		GEO_CLOCKBTN,
		GEO_CPART,
		GEO_HANDLE,
		GEO_CLOCKHAND,
		GEO_HILT,
		GEO_DIAMOND,
		GEO_HEMISPHERE,

		GEO_WHITESPHERE,
		GEO_REDSPHERE,
		GEO_EARS,
		GEO_ANTENNA,
		GEO_WINGFRAME,
		GEO_WINGFRAME2,
		GEO_WING,

		GEO_TEST,

		
		
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	Assignment2();
	~Assignment2();

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
	void RenderMesh(Mesh* mesh, bool enableLight);

	void generateWand();
	void generateEnviroment();
	void generateLeftWing();
	void generateRightWing();
	void generateHead();

	bool enableLight;
	bool enableAxis = true;
	float readyToUse;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	//Clock Rotation
	float smallHandRotation;
	float bigHandRotation;
	
	//Nose Wiggle
	float nose;
	float noseDirection = 1;
	float noseWaitTime;

	//Ears Wiggle
	float leftEar = 0;
	float leftEarDirection = 1;
	float rightEar;
	float rightEarDirection = -1;
	float earWaitTime;

	//Wings Flap
	float leftWingFlap = 0;
	float rightWingFlap = 0;

	int leftWingDirection = 1;
	int rightWingDirection = -1;

	//Moogle Rotation on Y
	float rotateY = 0;
	float moveX = 0;
	float moveZ = 0;

	//Walking
	float rotateHand1 = 0;
	float rotateHand2 = 0;
	float directionObject1 = 1;
	float directionObject2 = -1;
	float y = 0;
	int direction = 0;
	Vector3 cPosition;
	Vector3 cForward;


	Camera camera;
	
	Light light[2];

	MS modelStack, viewStack, projectionStack;
};

#endif