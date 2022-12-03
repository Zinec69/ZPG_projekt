#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include <string>

class Window
{
private:
	Window() {};
	~Window();
	int width;
	int height;
	const char* name;
	static GLFWwindow* window;
	void setViewport();
public:
	static Window& getInstance()
	{
		static Window instance;
		return instance;
	}

	void init(int width, int height, const char* name);
	int shouldClose();
	void swapBuffers();
	void initImgui();
	static void lockCursor();
	static void unlockCursor();

	Window(Window const&) = delete;
	void operator=(Window const&) = delete;
};
