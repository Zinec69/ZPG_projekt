#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useMat(this->object, "model");
	this->shader->useMat(Camera::getCamera(), "view");
	this->shader->useMat(Camera::getPerspective(), "projection");
	this->shader->useFloat(this->scale, "scale");

	if (this->shader->getType() != BASIC)
	{
		this->shader->useVec(this->color, "objectColor");
		this->shader->useVec(this->lightColor, "lightColor");
		this->shader->useVec(glm::vec3(0.0, 0.0, 0.0), "lightPos");
		this->shader->useVec(Camera::getPosition(), "viewPos");
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
