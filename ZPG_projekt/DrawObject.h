#pragma once

#include "Model.h"
#include "ShaderManager.h"
#include "Camera.h"

class DrawObject
{
private:
	glm::mat4 object{ 1.0 };
	glm::vec3 color{ 1.0, 1.0, 0.0 };
	glm::vec3 lightColor{ 1.0, 1.0, 1.0 };
	float scale = 1;

	Model* model;
	ShaderManager* shader;
	void transform();
public:
	DrawObject(Model* model, ShaderManager* shader);
	void draw();
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle, glm::vec3 axis, glm::vec3 point);
	void resize(glm::vec3 multiplier);
	void move(glm::vec3 point);
	void changeColor(glm::vec3 color);
	void changeSize(float size);
};
