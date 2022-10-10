#include "CallbackHandler.h"

void CallbackHandler::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void CallbackHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d, %d, %d, %d] \n", key, scancode, action, mods);
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
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void CallbackHandler::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback [%.f, %.f]\n", x, y);
}

void CallbackHandler::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		printf("button_callback [%d, %d, %d]\n", button, action, mode);
}

CallbackHandler::CallbackHandler(GLFWwindow* window)
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
}
