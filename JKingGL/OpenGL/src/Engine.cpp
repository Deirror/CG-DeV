#include "Engine.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "WinInit.h"

#include "Vertex33.h"

#define NUM_ARRAY_ELEMENTS(A) sizeof(A) / sizeof(*A)

static glm::vec3 normalizeScreenToNDC(float x, float y, float width, float height, float z)
{
	float normX = (x / width) * 2.0f - 1.0f;
	float normY = (y / height) * 2.0f - 1.0f;
	return glm::vec3(normX, normY, z);
}

void Engine::run(GLFWwindow* window)
{
	// Enable GL Effects
	glfwSwapInterval(1);

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Main Code
	Vertex33 baseV[] =
	{
		{glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)},

		{glm::vec3(0.0f, 540.0f, 1.0),
		glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(960.0f, 540.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)},

		{glm::vec3(960.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)},
	};

	Vertex33 verts[] =
	{
		baseV[0],
		baseV[1],
		baseV[2],
		baseV[3],

		{glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)},
		
		{glm::vec3(0.0f, 540.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(960.0f, 0.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(960.0f, 540.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)},

	};

	unsigned int indices[] =
	{
		0, 1, 2, 0, 2, 3,
		0, 1, 4, 1, 4, 5,
		4, 5, 6, 5, 6, 7,
		2, 3, 7, 3, 6, 7,
		1, 2, 7, 1, 5, 7,
		0, 3, 6, 0, 4, 6,
	};

	for (int i = 0; i < NUM_ARRAY_ELEMENTS(verts); ++i)
	{
		verts[i].position = normalizeScreenToNDC(
			verts[i].position.x,
			verts[i].position.y,
			WIDTH,
			HEIGHT,
			verts[i].position.z
		);
	}

	VertexBuffer vb(verts, sizeof(verts));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	VertexArray va;
	va.AddVertexBuffer(vb, layout);

	IndexBuffer ib(indices, NUM_ARRAY_ELEMENTS(indices));

	Shader shader("res/shaders/Basic.shader");
	shader.SetUniform3f("u_Color", 1.0f, 1.0f, 1.0f);

	Renderer renderer;

	glm::vec3 cameraPos = glm::vec3(0.0f, 3.5f, 1.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, -1.5f, -1.0f);  // where the camera looks
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);    // up direction
	float cameraSpeed = 0.05f;  // adjust for faster/slower movement
	
	float rotationAngle1 = 54.0f;
	float rotationAngle2 = 126.0f;
	float rotationSpeed = glm::radians(1.0f);  // 1 degree per frame (adjust as needed)

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float aspectRatio = (float)width / (float)height;

		if (height == 0) height = 1;
		
		// Flatten the front vector to the XZ plane
		glm::vec3 cameraFrontXZ = glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z));
		glm::vec3 right = glm::normalize(glm::cross(cameraFrontXZ, cameraUp));

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			rotationAngle1 += rotationSpeed;
			rotationAngle2 += rotationSpeed;
		}

		// Forward/backward (W/S)
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFrontXZ;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFrontXZ;

		// Strafe left/right (A/D)
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= right * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += right * cameraSpeed;

		// Cube 1
		glm::mat4 projPersp = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 10.0f);
		glm::mat4 view = glm::lookAt(
			cameraPos,
			cameraPos + cameraFront,  // look slightly ahead
			cameraUp
		);
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -3.0f));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationAngle1, glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 mvp = projPersp * view * translation * rotation;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);

		// Cube 2
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.75f));
		rotation = glm::rotate(glm::mat4(1.0f), rotationAngle2, glm::vec3(0.0f, 1.0f, 0.0f));

		mvp = projPersp * view * translation * rotation;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

