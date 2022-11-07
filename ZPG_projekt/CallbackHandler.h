#pragma once

#include "GLincludes.h"
#include "Camera.h"
#include "Observer.h"
#include <stdio.h>
#include <vector>

class Mouse : public Subject
{
private:
	Mouse() {};
public:
	int x = -1;
	int y = -1;
	int button_clicked = -1;
	int button_action = -1;
	int scroll = 0;

	static Mouse& getInstance()
	{
		static Mouse instance;
		return instance;
	}

	Mouse(Mouse const&) = delete;
	Mouse& operator=(Mouse const&) = delete;
};

class Keyboard : public Subject
{
private:
	Keyboard() {};
public:
	int key_pressed = -1;
	int key_action = -1;

	static Keyboard& getInstance()
	{
		static Keyboard instance;
		return instance;
	}

	Keyboard(Keyboard const&) = delete;
	Keyboard& operator=(Keyboard const&) = delete;
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
public:
	CallbackHandler(GLFWwindow* window);

	CallbackHandler(CallbackHandler const&) = delete;
	CallbackHandler& operator = (CallbackHandler const&) = delete;
};
