#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_direction(glm::vec3(0.0f, 0.0f, -1.0f)), 
	m_position(glm::vec3(0.0f, 0.0f, 2.0f)), m_oldMousePosition()
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 delta = newMousePosition - m_oldMousePosition;

	const float ROTATION_SPEED = 0.003f;
	glm::vec3 toRotateAround = glm::cross(m_direction, m_up);
	glm::mat4 rotator = glm::rotate(glm::mat4(1), -delta.x * ROTATION_SPEED, m_up) *
						glm::rotate(glm::mat4(1), -delta.y * ROTATION_SPEED, toRotateAround);

	m_direction = glm::mat3(rotator) * m_direction;

	m_oldMousePosition = newMousePosition;
}
