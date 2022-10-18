#include "Window.h"

Window::Window(int width, int height, const char* name)
{
	this->width = width;
	this->height = height;
	this->name = name;
	this->window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);
	this->setViewport();

	CallbackHandler(this->window);
}

void Window::setViewport()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	glViewport(0, 0, width, height);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(this->window);
}

void Window::lockCursor()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::unlockCursor()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int Window::shouldClose()
{
	return glfwWindowShouldClose(this->window);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}
