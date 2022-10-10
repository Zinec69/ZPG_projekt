#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useProgram();
	this->shader->transform(transform());
	this->model->draw();
}

glm::mat4 DrawObject::transform()
{
	glm::mat4 t = glm::translate(glm::mat4{ 1.f }, this->translation);
	t = glm::scale(t, this->scales);
	t = glm::rotate(t, this->rotation.x, { 1.f, 0.f, 0.f });
	t = glm::rotate(t, this->rotation.y, { 0.f, 1.f, 0.f });
	t = glm::rotate(t, this->rotation.z, { 0.f, 0.f, 1.f });
	
	return t;
}

void DrawObject::rotate(glm::vec3 angle)
{
	this->rotation += angle;
}
