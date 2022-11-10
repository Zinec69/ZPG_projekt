#pragma once

#include <map>
#include "GLincludes.h"
#include "Window.h"
#include "ShaderManager.h"
#include "DrawObject.h"
#include "Observer.h"
#include "Scene.h"

class Application
{
private:
	Window* window;
	std::vector<DrawObject*> drawObjects;
	std::map<int, Scene*> scenes;
	int currentScene;
	void printInfo();
public:
	Application(int windowWidth, int windowHeight);
	~Application();
	void run();
	void changeCurrentScene(int ID);
	void addScene(Scene* scene, int ID);
	Scene* getScene(int ID);
};
