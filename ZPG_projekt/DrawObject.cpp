#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useProgram();

	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
	// glm::mat4 perspective = glm::mat4( 1.f );

	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	const float cameraSpeed = 0.05f;
	if (Keyboard::key_pressed == GLFW_KEY_W)
		this->eye += cameraSpeed * this->target;
	if (Keyboard::key_pressed == GLFW_KEY_S)
		this->eye -= cameraSpeed * this->target;
	if (Keyboard::key_pressed == GLFW_KEY_A)
		this->eye -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
	if (Keyboard::key_pressed == GLFW_KEY_D)
		this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;

	glm::mat4 view = glm::lookAt(this->eye, this->eye + this->target, this->up);

	glEnable(GL_DEPTH_TEST);

	this->shader->transform(this->object, perspective, view);
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
