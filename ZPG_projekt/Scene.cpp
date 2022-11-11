#include "Scene.h"

void Scene::render()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	for (int i = 0; i < this->objects.size(); i++)
	{
		if (!this->objects[i]->isActive())
			continue;
		this->objects[i]->draw(lights);
	}
}

void Scene::addObject(DrawObject* object)
{
	this->objects.push_back(object);
}

void Scene::setObjects(std::vector<DrawObject*> objects)
{
	this->objects = objects;
}

void Scene::addLight(Light* light)
{
	this->lights.push_back(light);
}

void Scene::setLights(std::vector<Light*> lights)
{
	this->lights = lights;
}
