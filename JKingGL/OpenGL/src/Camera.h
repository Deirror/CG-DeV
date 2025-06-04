#pragma once

#include <glm/glm.hpp>

class Camera
{
public: 
	Camera();

	glm::mat4 getViewMatrix() const;
	void mouseUpdate(const glm::vec2& newMousePosition);
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	const glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec2 m_oldMousePosition;
};

