#pragma once
#include "glm.hpp"
#include "ext.hpp"


class Camera
{
public:

	Camera();

	virtual void Update(float fDeltaTime) = 0;

	void SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar);

	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);

	void SetPosition(glm::vec3 position);

	glm::mat4 GetWorldTransform();
	
	glm::mat4 GetView();

	glm::mat4 GetProjection();

	glm::mat4 GetProjectionView();
	

	void UpdateProjectionViewTransform();

protected:

	glm::mat4 worldTransform;

	glm::mat4 viewTransform;

	glm::mat4 projectionTransform;

	glm::mat4 projectionViewTransform;

};

