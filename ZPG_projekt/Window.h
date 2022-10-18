#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include <string>

class Window
{
private:
	int width;
	int height;
	const char* name;
	GLFWwindow* window;
	void setViewport();
public:
	Window(int width, int height, const char* name);
	~Window();
	int shouldClose();
	void swapBuffers();
	void lockCursor();
	void unlockCursor();
};
