#pragma once
#include "Camera.h"

class FlyCamera : public Camera
{
public:

	void Update(float fDeltaTime);

	void SetSpped(float fSpeed);

private:

	float fSpeed;

	glm::vec3 up;
};

