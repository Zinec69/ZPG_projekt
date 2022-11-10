#pragma once

#include "Model.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Light.h"
#include "Observer.h"

struct Material
{
	int shininess = 32;
};

class DrawObject : public Observer
{
private:
	glm::mat4 object{ 1.0 };
	glm::vec3 color{ 1.0, 1.0, 0.0 };
	float scale = 1;

	Material material;
	Model* model;
	ShaderManager* shader;
public:
	DrawObject(Model* model, ShaderManager* shader, float scale = 1, glm::vec3 color = glm::vec3(1.0, 1.0, 0.0), glm::vec3 position = glm::vec3(0.0));
	void draw(std::vector<Light*> lights);
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle, glm::vec3 axis, glm::vec3 point);
	void resize(glm::vec3 multiplier);
	void move(glm::vec3 point);
	void changeColor(glm::vec3 color);
	void changeSize(float size);
	void changeShininess(int shininess);
	bool isLightSource() const;

	void onSubjectNotification(EventType eventType, void* object);
};
