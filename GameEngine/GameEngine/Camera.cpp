#include "Camera.h"

void Camera::SetPerspective(float fDieldOfView, float fAspectRatio, float fNear, float fFar)
{

}

void  Camera::SetLookAt(glm::vec3 from, glm::vec3 up)
{

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
