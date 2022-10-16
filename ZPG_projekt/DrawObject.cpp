#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useProgram();

	// glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 perspective = glm::mat4( 1.f );

	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	glm::vec3 eye = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 target = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

	const float cameraSpeed = 0.05f;
	if (Keyboard::key_pressed == GLFW_KEY_W)
		eye += cameraSpeed * target;
	if (Keyboard::key_pressed == GLFW_KEY_S)
		eye -= cameraSpeed * target;
	if (Keyboard::key_pressed == GLFW_KEY_A)
		eye -= glm::normalize(glm::cross(target, up)) * cameraSpeed;
	if (Keyboard::key_pressed == GLFW_KEY_D)
		eye += glm::normalize(glm::cross(target, up)) * cameraSpeed;

	glm::mat4 view = glm::lookAt(eye, eye + target, up);

	this->shader->transform(this->object, perspective, view);
	this->model->draw();
}

glm::mat4 DrawObject::transform()
{
	glm::mat4 t = glm::mat4{ 1.f };

	return t;
}

void DrawObject::rotate(glm::vec3 multiplier)
{
	this->object = glm::rotate(this->object, multiplier[0], { 1.f, 0.f, 0.f });
	this->object = glm::rotate(this->object, multiplier[1], { 0.f, 1.f, 0.f });
	this->object = glm::rotate(this->object, multiplier[2], { 0.f, 0.f, 1.f });
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(this->object, multiplier);
}
