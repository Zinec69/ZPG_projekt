#pragma once

#include "GLincludes.h"
#include "DrawObject.h"
#include "Camera.h"
#include <vector>

class Scene
{
private:
	std::vector<DrawObject*> objects = std::vector<DrawObject*>();
	std::vector<Light*> lights = std::vector<Light*>();
public:
	Scene() {};
	void render();
	void addObject(DrawObject* object);
	void setObjects(std::vector<DrawObject*> objects);
	void addLight(Light* light);
	void setLights(std::vector<Light*> lights);
};
