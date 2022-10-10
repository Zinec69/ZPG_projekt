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

int Window::shouldClose()
{
	return glfwWindowShouldClose(this->window);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}
