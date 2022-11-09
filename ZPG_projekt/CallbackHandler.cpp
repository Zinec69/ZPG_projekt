#include "CallbackHandler.h"

void CallbackHandler::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void CallbackHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		Keyboard::getInstance().key_pressed = key;
	else
		Keyboard::getInstance().key_pressed = -1;
	Keyboard::getInstance().key_action = action;
	Keyboard::getInstance().notifyObservers(KeyboardPressed, &Keyboard::getInstance());
}

void CallbackHandler::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback [%d]\n", focused);
}

void CallbackHandler::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback [%d]\n", iconified);
}

void CallbackHandler::window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Camera::getInstance().setPerspective(90, (float)width, (float)height);
}

void CallbackHandler::cursor_callback(GLFWwindow* window, double x, double y)
{
	Mouse::getInstance().x = (int)x;
	Mouse::getInstance().y = (int)y;
	Mouse::getInstance().notifyObservers(MouseMoved, &Mouse::getInstance());
}

void CallbackHandler::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		Mouse::getInstance().button_clicked = button;
	else
		Mouse::getInstance().button_clicked = -1;
	Mouse::getInstance().notifyObservers(MouseClicked, &Mouse::getInstance());
}

void CallbackHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse::getInstance().scroll = (int)yoffset;
	Mouse::getInstance().notifyObservers(MouseScrolled, &Mouse::getInstance);
}

CallbackHandler::CallbackHandler(GLFWwindow* window)
{
	if (window == nullptr)
		fprintf(stderr, "Callback window not specified\n");
	else
	{
		glfwSetErrorCallback(error_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowFocusCallback(window, window_focus_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetWindowIconifyCallback(window, window_iconify_callback);
		glfwSetCursorPosCallback(window, cursor_callback);
		glfwSetMouseButtonCallback(window, button_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}
}
