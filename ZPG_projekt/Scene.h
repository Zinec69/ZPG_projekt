#pragma once

#include "GLincludes.h"
#include "DrawObject.h"
#include "Camera.h"
#include "Observer.h"
#include <vector>
#include <map>

class Scene : Observer
{
private:
	std::map<int, DrawObject*> objects = std::map<int, DrawObject*>();
	std::vector<Light*> lights = std::vector<Light*>();
	std::map<ShaderType, ShaderManager*> shaders = std::map<ShaderType, ShaderManager*>();
	std::map<std::string, Model*> models = std::map<std::string, Model*>();
public:
	Scene();
	void render();
	void addObject(DrawObject* object);
	void setObjects(std::map<int, DrawObject*> objects);
	void removeObject(int id);
	void addLight(Light* light);
	void setLights(std::vector<Light*> lights);
	void addShader(ShaderManager* shader);
	void setShaders(std::map<ShaderType, ShaderManager*> shaders);
	ShaderManager* getShader(ShaderType shaderType);
	void addModel(Model* model, std::string name);
	void setModels(std::map<std::string, Model*> models);
	Model* getModel(std::string model_name);

	void onSubjectNotification(EventType eventType, void* object) override;
};
