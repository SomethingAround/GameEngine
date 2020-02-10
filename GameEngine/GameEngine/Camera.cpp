#include "Camera.h"

Camera::Camera()
{
	worldTransform = glm::mat4(1);

	viewTransform = glm::mat4(1);

	projectionTransform = glm::mat4(1);

	projectionViewTransform = glm::mat4(1);
}

void Camera::SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar)
{
	projectionTransform = glm::perspective(fFieldOfView, fAspectRatio, fNear, fFar);

	UpdateProjectionViewTransform();
}

void  Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);
	UpdateProjectionViewTransform();
}

void Camera::SetPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position, 1);
	viewTransform = glm::inverse(worldTransform);
	UpdateProjectionViewTransform();
}

glm::mat4  Camera::GetWorldTransform()
{
	return worldTransform;
}


glm::mat4  Camera::GetView()
{
	return viewTransform;
}


glm::mat4  Camera::GetProjection()
{
	return projectionTransform;
}


glm::mat4  Camera::GetProjectionView()
{
	return projectionViewTransform;
}

void Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}