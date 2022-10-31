#pragma once

#include "GLincludes.h"
#include "Camera.h"
#include <stdio.h>
#include <vector>

class Mouse
{
private:
	Mouse() {};
public:
	static int x;
	static int y;
	static int button_clicked;
	static int scroll;

	Mouse(Mouse const&) = delete;
	Mouse& operator = (Mouse const&) = delete;
};

class Keyboard
{
private:
	Keyboard() {};
public:
	static int key_pressed;
	static int key_action;

	Keyboard(Keyboard const&) = delete;
	Keyboard& operator = (Keyboard const&) = delete;
};

class CallbackHandler
{
private:
	CallbackHandler() {};
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static Mouse* mouse;
	static Keyboard* keyboard;
public:
	CallbackHandler(GLFWwindow* window);

	CallbackHandler(CallbackHandler const&) = delete;
	CallbackHandler& operator = (CallbackHandler const&) = delete;
};
