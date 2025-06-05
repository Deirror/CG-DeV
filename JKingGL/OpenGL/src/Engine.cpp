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
#include "Camera.h"

#define NUM_ARRAY_ELEMENTS(A) sizeof(A) / sizeof(*A)

static glm::vec3 normalizeScreenToNDC(float x, float y, float width, float height, float z)
{
	float normX = (x / width) * 2.0f - 1.0f;
	float normY = (y / height) * 2.0f - 1.0f;
	return glm::vec3(normX, normY, z);
}

static void normalizeVertices(Vertex33* verts, int count, float width, float height)
{
	for (int i = 0; i < count; ++i)
	{
		verts[i].position = normalizeScreenToNDC(
			verts[i].position.x,
			verts[i].position.y,
			width,
			height,
			verts[i].position.z
		);
	}
}

static float getAspectRatio()
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	if (height == 0) height = 1; 
	return static_cast<float>(width) / static_cast<float>(height);
}

static void moveCamera(GLFWwindow* window, Camera& camera)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera.mouseUpdate(glm::vec2(x, y));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.moveForward();
	}	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.moveBackward();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.moveLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.moveRight();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.moveUp();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.moveDown();
	}
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

		{glm::vec3(0.0f, 540.0f, 1.0f),
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

	Vertex33 test[] =
	{
		{glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(960.0f, 540.0f, -2.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(960.0f, 0.0f, -2.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	};

	unsigned int testIndices[] =
	{
		0, 1, 2
	};

	normalizeVertices(verts, NUM_ARRAY_ELEMENTS(verts), WIDTH, HEIGHT);
	normalizeVertices(test, NUM_ARRAY_ELEMENTS(test), WIDTH, HEIGHT);

	VertexBuffer vb1(verts, sizeof(verts));
	VertexBuffer vb2(test, sizeof(test));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	VertexArray va1;
	va1.AddVertexBuffer(vb1, layout);

	VertexArray va2;
	va2.AddVertexBuffer(vb2, layout);

	IndexBuffer ib1(indices, NUM_ARRAY_ELEMENTS(indices));
	IndexBuffer ib2(testIndices, NUM_ARRAY_ELEMENTS(testIndices));

	Shader shader("res/shaders/Basic.shader");
	shader.SetUniform3f("u_Color", 1.0f, 1.0f, 1.0f);

	Renderer renderer;

	Camera camera;

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		moveCamera(window, camera);

		glm::mat4 projPersp = glm::perspective(glm::radians(60.0f), getAspectRatio(), 0.1f, 10.0f);

		//Cube 1
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -3.0f));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), 54.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 mvp = projPersp * camera.getViewMatrix() * translation * rotation;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va1, ib1, shader);

		//Cube 2
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.75f));
		rotation = glm::rotate(glm::mat4(1.0f), 126.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		mvp = projPersp * camera.getViewMatrix() * translation * rotation;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va1, ib1, shader);

		// Test Triangle
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.75f));

		mvp = projPersp * camera.getViewMatrix() * translation;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va2, ib2, shader);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

