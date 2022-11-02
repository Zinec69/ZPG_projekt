#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->setMat(this->object, "model");
	this->shader->setMat(Camera::getCamera(), "view");
	this->shader->setMat(Camera::getPerspective(), "projection");
	this->shader->setFloat(this->scale, "scale");

	if (this->shader->getType() != BASIC)
	{
		this->shader->setVec(this->color, "objectColor");
		this->shader->setVec(Camera::getPosition(), "viewPos");
		if (this->shader->getType() != MULTIPLE_LIGHTS)
		{
			this->shader->setVec(glm::vec3(0.0, 0.0, 0.0), "lightPos");
			this->shader->setVec(this->lightColor, "lightColor");
		}
		else
		{
			this->shader->setInt(0, "lights[0].type");
			this->shader->setFloat(0.1, "lights[0].ambientStrength");
			this->shader->setFloat(0.5, "lights[0].specularStrength");
			this->shader->setVec(this->lightColor, "lights[0].color");
			this->shader->setVec(glm::vec3(4.0, 4.0, 0.0), "lights[0].position");
			this->shader->setInt(0, "lights[1].type");
			this->shader->setFloat(0.1, "lights[1].ambientStrength");
			this->shader->setFloat(0.5, "lights[1].specularStrength");
			this->shader->setVec(this->lightColor, "lights[1].color");
			this->shader->setVec(glm::vec3(-4.0, -4.0, 0.0), "lights[1].position");
		}
	}

	this->shader->useProgram();
	this->model->draw();
}

void DrawObject::transform()
{
	glm::mat4 t = glm::mat4{ 1.0 };
}

void DrawObject::rotate(float angle, glm::vec3 axis)
{
	this->object = glm::rotate(glm::mat4{ 1.0 }, glm::radians(angle), axis);
}

void DrawObject::rotate(float angle, glm::vec3 axis, glm::vec3 point)
{
	glm::mat4 m = glm::translate(this->object, point);
	m = glm::rotate(m, glm::radians(angle), axis);
	this->object = glm::translate(m, -point);
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(glm::mat4{ 1.0 }, multiplier);
}

void DrawObject::move(glm::vec3 point)
{
	this->object = glm::translate(glm::mat4{ 1.0 }, point);
}

void DrawObject::changeColor(glm::vec3 color)
{
	this->color = color;
}

void DrawObject::changeSize(float size)
{
	this->scale = 1 / size;
}
