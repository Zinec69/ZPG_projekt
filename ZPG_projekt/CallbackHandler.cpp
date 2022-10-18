#include "CallbackHandler.h"

int Mouse::x = -1;
int Mouse::y = -1;
int Mouse::button_clicked = -1;
int Mouse::scroll = 0;
int Keyboard::key_pressed = -1;
int Keyboard::key_action = -1;

void CallbackHandler::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void CallbackHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		keyboard->key_pressed = key;
	else
		keyboard->key_pressed = -1;
	keyboard->key_action = action;
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
}

void CallbackHandler::cursor_callback(GLFWwindow* window, double x, double y)
{
	mouse->x = (int)x;
	mouse->y = (int)y;
}

void CallbackHandler::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		mouse->button_clicked = button;
	else
		mouse->button_clicked = -1;
}

void CallbackHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouse->scroll = (int)yoffset;
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
