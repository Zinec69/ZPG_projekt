#pragma once

#include "Model.h"
#include "ShaderManager.h"

class DrawObject
{
private:
	glm::vec3 translation{ 0.f };
	glm::vec3 rotation{ 0.f };
	glm::vec3 scales{ 1.f };
	Model* model;
	ShaderManager* shader;
	glm::mat4 transform();
public:
	DrawObject(Model* model, ShaderManager* shader);
	void draw();
	void rotate(glm::vec3 angle);
};
