#include "FlyCamera.h"


FlyCamera::FlyCamera(
	const glm::vec3 position,
	const glm::vec3 LookAtPoint,
	const float FOVY,
	const float fAspectRatio,
	const float nearDistance,
	const float FarDistance) : Camera::Camera()
{
	up = glm::vec3(0, 1, 0);
	m_fSpeed = 1.0f;
	m_fMouseSpeed = 0.1f;
	SetPerspective(FOVY, fAspectRatio, nearDistance, FarDistance);
	SetLookAt(position, LookAtPoint, up);
}

void FlyCamera::Update(float fDeltaTime)
{
	auto glfwWindow = glfwGetCurrentContext();

	bool inputFlag = false;

	glm::vec3 displacement = glm::vec3(0);

	if (glfwGetKey(glfwWindow, GLFW_KEY_W))
	{
		displacement -= glm::vec3(worldTransform[2]);
		inputFlag = true;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_S))
	{
		displacement += glm::vec3(worldTransform[2]);
		inputFlag = true;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_A))
	{
		displacement -= glm::vec3(worldTransform[0]);
		inputFlag = true;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_D))
	{
		displacement += glm::vec3(worldTransform[0]);
		inputFlag = true;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_LEFT_CONTROL))
	{
		displacement -= glm::vec3(worldTransform[1]);
		inputFlag = true;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_SPACE))
	{
		displacement += glm::vec3(worldTransform[1]);
		inputFlag = true;
	}

	if (inputFlag == true)
	{
		SetPosition(GetWorldTransform()[3] + (glm::vec4(displacement, 0.0f) * m_fSpeed * fDeltaTime));
	}

	double dCursorPositionX;
	double dCursorPositionY;

	glfwGetCursorPos(glfwWindow, &dCursorPositionX, &dCursorPositionY);

	double dDeltaX = dCursorPositionX - (1280 * 0.5);
	double dDeltaY = dCursorPositionY - (720 * 0.5);

	glfwSetCursorPos(glfwWindow, 1280 * 0.5, 720 * 0.5);

	if (dDeltaX || dDeltaY)
	{
		auto rotation = glm::mat4(1.0f);

		rotation = glm::rotate(rotation, float(m_fMouseSpeed * fDeltaTime * -dDeltaX), glm::vec3(viewTransform[1]));
		rotation = glm::rotate(rotation, float(m_fMouseSpeed * fDeltaTime * -dDeltaY), glm::vec3(1.0f, 0.0f, 0.0f));

		worldTransform = worldTransform * rotation;

		viewTransform = glm::inverse(worldTransform);

		UpdateProjectionViewTransform();
	}

}

void FlyCamera::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}