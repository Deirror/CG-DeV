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
//	/*
	Vertex33 verts[] =
	{
		{ glm::vec3(0.0f, 540.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // 0
		{ glm::vec3(960.0f, 540.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // 1
		{ glm::vec3(960.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // 2
		{ glm::vec3(0.0f, 540.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // 3
		{ glm::vec3(0.0f, 540.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f) }, // 4
		{ glm::vec3(960.0f, 540.0f, +1.0f), glm::vec3(0.0f, 0.5f, 0.2f) }, // 5

		{ glm::vec3(960.0f, 0.0f, -1.0f), glm::vec3(0.739f, 0.555f, 0.370f) }, // 6
		{ glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.288f, 0.961f, 0.480f) }, // 7
		{ glm::vec3(960.0f, 540.0f, -1.0f), glm::vec3(0.316f, 0.5f, 0.316f) }, // 8

		{ glm::vec3(960.0f, 540.0f, +1.0f), glm::vec3(0.780f, 0.260f, 0.606f) }, // 9
		{ glm::vec3(960.0f, 0.0f, +1.0f), glm::vec3(0.341f, 0.796f, 0.568f) }, // 10
		{ glm::vec3(960.0f, 0.0f, -1.0f), glm::vec3(0.500f, 0.700f, 0.500f) }, // 11

		{ glm::vec3(0.0f, 540.0f, +1.0f), glm::vec3(0.621f, 0.709f, 0.177f) }, // 12
		{ glm::vec3(0.0f, 540.0f, -1.0f), glm::vec3(0.540f, 0.756f, 0.324f) }, // 13
		{ glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.408f, 0.714f, 0.571f) }, // 14

		{ glm::vec3(0.0f, 0.0f, +1.0f), glm::vec3(0.188f, 0.471f, 0.943f) }, // 15
		{ glm::vec3(960.0f, 540.0f, +1.0f), glm::vec3(0.520f, 1.0f, 0.606f) }, // 16
		{ glm::vec3(0.0f, 540.0f, +1.0f), glm::vec3(0.6f, 0.4f, 0.8f) }, // 17

		{ glm::vec3(0.0f, 0.0f, +1.0f), glm::vec3(0.178f, 0.8f, 0.7f) }, // 18
		{ glm::vec3(960.0f, 0.0f, +1.0f), glm::vec3(0.21f, 0.71f, 1.0f) }, // 19
		{ glm::vec3(960.0f, 0.0f, -1.0f), glm::vec3(0.8f, 0.3f, 0.7f) }, // 20

		{ glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.800f, 0.907f, 0.500f) }, // 21
		{ glm::vec3(0.0f, 0.0f, +1.0f), glm::vec3(0.594f, 0.787f, 0.5f) }, // 22
		{ glm::vec3(960.0f, 0.0f, +1.0f), glm::vec3(0.9f, 1.0f, 0.2f) } // 23
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


	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 23, 22
	};
//	*/
	/*
	Vertex33 verts[] =
	{
		{glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(960.0f, 0.0f, 1.0),
		glm::vec3(0.0f, 1.0f, 0.0f)},

		{glm::vec3(480.0f, 540.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)},
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};

	*/
	
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

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float aspectRatio = (float)width / (float)height;

		// glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 5.0f);
		glm::mat4 projPersp = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 10.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 5.0f),   // camera position
			glm::vec3(0.0f, 0.0f, 0.0f),      // look at center
			glm::vec3(0.0f, 1.0f, 0.0f));     // up direction
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		glm::mat4 mvp = projPersp * view * model;

		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

