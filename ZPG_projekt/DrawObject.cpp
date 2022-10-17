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

	this->shader->transform(this->object, Camera::getPerspective(), Camera::getCamera());
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

void DrawObject::rotate(glm::vec3 rotation, glm::vec3 point)
{
	this->object = glm::translate(this->object, point);
	this->object = glm::rotate(this->object, rotation[0], { 1.f, 0.f, 0.f });
	this->object = glm::rotate(this->object, rotation[1], { 0.f, 1.f, 0.f });
	this->object = glm::rotate(this->object, rotation[2], { 0.f, 0.f, 1.f });
	this->object = glm::translate(this->object, -point);
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(this->object, multiplier);
}
