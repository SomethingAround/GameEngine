#pragma once
#include "glm.hpp"
#include "ext.hpp"


class Camera
{
public:

	Camera();

	virtual void Update(float fDeltaTime) = 0;

	//Sets the camera to perspective and passes in the needed variables
	void SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar);

	//Sets where the camera is looking from and to
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);

	//Sets the camera's position in world space
	void SetPosition(glm::vec3 position);

	//Returns the world matrix
	glm::mat4 GetWorldTransform();
	
	//Returns the view matrix
	glm::mat4 GetView();

	//Returns the projection matrix
	glm::mat4 GetProjection();

	//Returns the projection view matrix
	glm::mat4 GetProjectionView();
	
	//Updates the projection view matrix
	void UpdateProjectionViewTransform();

protected:

	glm::mat4 worldTransform;

	glm::mat4 viewTransform;

	glm::mat4 projectionTransform;

	glm::mat4 projectionViewTransform;

};

