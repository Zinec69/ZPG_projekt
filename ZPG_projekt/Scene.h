#pragma once

#include "GLincludes.h"
#include "DrawObject.h"
#include "Camera.h"
#include <vector>

class Scene
{
private:
	std::vector<DrawObject*> objects;
	std::vector<Light*> lights;
public:
	Scene() {};
	void render();
};
