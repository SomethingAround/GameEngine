#pragma once

#include "Camera.h"
#include "glfw3.h"

class FlyCamera : public Camera
{
public:

	FlyCamera(
		const glm::vec3 position,
		const glm::vec3 LookAtPoint, 
		const float FOVY = 3.14159f * 0.5f,
		const float fAspectRatio = 16.0f / 9.0f,
		const float nearDistance = 0.01f,
		const float FarDistance = 100.0f);

	//Updates the fly cameras position
	void Update(float fDeltaTime) override;

	//Sets the speed of the camera
	void SetSpeed(float fSpeed);

private:

	float m_fSpeed;

	float m_fMouseSpeed;

	glm::vec3 m_v3Up;
};

