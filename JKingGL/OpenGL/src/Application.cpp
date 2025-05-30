#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Engine.h"
#include "WinInit.h"

int main()
{
	GLFWwindow* window = glfwWinInit();
	if (window == nullptr)
	{
		std::cout << "[Init Error] Could not init glfw window\n";
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		std::cout << "[Init Error] Could not init glew\n";
	}

	Engine::run(window);

	glfwTerminate();
	return 0;
}