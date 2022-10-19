#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useProgram();

	glEnable(GL_DEPTH_TEST);

	this->shader->transform(this->object);
	this->model->draw();
}

glm::mat4 DrawObject::transform()
{
	glm::mat4 t = glm::mat4{ 1.f };

	return t;
}

void DrawObject::rotate(glm::vec3 rotation)
{
	this->object = glm::rotate(this->object, rotation[0], { 1.f, 0.f, 0.f });
	this->object = glm::rotate(this->object, rotation[1], { 0.f, 1.f, 0.f });
	this->object = glm::rotate(this->object, rotation[2], { 0.f, 0.f, 1.f });
}

void DrawObject::rotate(float angle, glm::vec3 point, glm::vec3 axis)
{
	glm::mat4 m;

	this->angle += 1;

	m = glm::translate(glm::mat4{1.0}, point);
	m = glm::rotate(m, glm::radians(this->angle), axis);
	m = glm::translate(m, -point);
	this->object = m;
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(this->object, multiplier);
}
