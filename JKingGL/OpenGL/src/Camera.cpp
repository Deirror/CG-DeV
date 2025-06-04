#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_direction(glm::vec3(0.0f, 0.0f, -1.0f)), 
	m_position(glm::vec3(0.0f, 0.0f, 1.0f))
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 delta = newMousePosition - m_oldMousePosition;
	m_direction = glm::mat3(glm::rotate(glm::mat4(1), -delta.x * 0.005f, m_up)) * m_direction; 

	m_oldMousePosition = newMousePosition;
}
