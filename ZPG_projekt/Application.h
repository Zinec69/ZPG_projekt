#pragma once

#include "GLincludes.h"
#include "Window.h"
#include "ShaderManager.h"
#include "DrawObject.h"

class Application
{
private:
	Window* window;
	std::vector<DrawObject*> drawObjects;
	void printInfo();
public:
	Application(int windowWidth, int windowHeight);
	~Application();
	void loop();
};
