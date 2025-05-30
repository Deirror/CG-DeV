#pragma once

#define WIDTH 960
#define HEIGHT 540

struct GLFWwindow;

GLFWwindow* glfwWinInit();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
