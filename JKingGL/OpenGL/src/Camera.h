#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	const float MOVE_SPEED = 0.01f;

public: 
	Camera();

	glm::mat4 getViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);
	
	void moveForward() { m_position += m_direction * MOVE_SPEED; }
	void moveBackward() { m_position -= m_direction * MOVE_SPEED; }
	void moveLeft() { m_position -= glm::normalize(glm::cross(m_direction, m_up)) * MOVE_SPEED; }
	void moveRight() { m_position += glm::normalize(glm::cross(m_direction, m_up)) * MOVE_SPEED; }
	void moveUp() { m_position += m_up * MOVE_SPEED; }
	void moveDown() { m_position -= m_up * MOVE_SPEED; }

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	const glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec2 m_oldMousePosition;

};

