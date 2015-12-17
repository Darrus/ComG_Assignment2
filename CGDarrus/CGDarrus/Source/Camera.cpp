#include "Camera.h"
#include "Vector3.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	Mtx44 rotation;
	float theta = 0;
	float phi = 0;
	Vector3 view = (target - position).Normalized();
	Vector3 dirVector = target - position;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalized();
	up = right.Cross(view);
	
	if (Application::IsKeyPressed('W'))
	{
		phi -= 1;
		rotation.SetToRotation(phi, right.x, right.y, right.z);
		target += (-(rotation * dirVector) + dirVector);
	}
	if (Application::IsKeyPressed('S'))
	{
		phi += 1;
		rotation.SetToRotation(phi, right.x, right.y, right.z);
		target += (-(rotation * dirVector) + dirVector);
	}
	if (Application::IsKeyPressed('A'))
	{
		theta -= 2;
		rotation.SetToRotation(theta, 0, 1, 0);
		target += (-(rotation * dirVector) + dirVector);
	}
	if (Application::IsKeyPressed('D'))
	{
		theta += 2;
		rotation.SetToRotation(theta, 0, 1, 0);
		target += (-(rotation * dirVector) + dirVector);
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		rotation.SetToRotation(theta, 0, 1, 0);
		target += (rotation * view);
		position += (rotation * view);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		rotation.SetToRotation(theta, 0, 1, 0);
		target -= (rotation * view);
		position -= (rotation * view);
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		rotation.SetToRotation(theta, 0, 1, 0);
		target -= (rotation * right);
		position -= (rotation * right);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		rotation.SetToRotation(theta, 0, 1, 0);
		target += (rotation * right);
		position += (rotation * right);
	}
}

float Camera::X(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float Camera::Y(float phi)
{
	return sin(Math::DegreeToRadian(phi));
}
float Camera::Z(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}