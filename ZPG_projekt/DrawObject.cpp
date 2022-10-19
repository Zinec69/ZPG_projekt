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

void DrawObject::rotate(float angle, glm::vec3 axis)
{
	this->object = glm::rotate(this->object, angle, axis);
}

void DrawObject::rotate(float angle, glm::vec3 axis, glm::vec3 point)
{
	glm::mat4 m;

	m = glm::translate(glm::mat4{1.0}, point);
	m = glm::rotate(m, glm::radians(angle), axis);
	m = glm::translate(m, -point);
	
	this->object = m;
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(this->object, multiplier);
}

void DrawObject::move(glm::vec3 point)
{
	this->object = glm::translate(this->object, point);
}
