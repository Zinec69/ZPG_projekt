#include "Camera.h"

glm::mat4 Camera::getCamera()
{
	return this->lookAt;
}

glm::mat4 Camera::getPerspective()
{
	return this->perspective;
}

glm::vec3 Camera::getPosition()
{
	return this->eye;
}

glm::vec3 Camera::getTarget()
{
	return this->target;
}

void Camera::setPerspective(float FOV, float width, float height)
{
	this->perspective = glm::perspective(glm::radians(FOV), width / height, 0.1f, 100.0f);
	notifyObservers(CameraMoved, this);
}

void Camera::move()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (!io.WantCaptureMouse)
	{
		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		const float cameraSpeed = 0.02f;
		if (Keyboard::key_pressed == GLFW_KEY_W)
			this->eye += cameraSpeed * this->target;
		if (Keyboard::key_pressed == GLFW_KEY_S)
			this->eye -= cameraSpeed * this->target;
		if (Keyboard::key_pressed == GLFW_KEY_A)
			this->eye -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_D)
			this->eye += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_SPACE)
			this->eye += this->up * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_LEFT_CONTROL)
			this->eye -= this->up * cameraSpeed;

		float x_offset = Mouse::x - this->mouse_last_x;
		float y_offset = this->mouse_last_y - Mouse::y;

		this->mouse_last_x = Mouse::x;
		this->mouse_last_y = Mouse::y;

		const float sensitivity = 0.1f;
		x_offset *= sensitivity;
		y_offset *= sensitivity;

		if (Mouse::button_clicked == GLFW_MOUSE_BUTTON_LEFT)
		{
			Window::lockCursor();
			this->yaw += x_offset;
			this->pitch += y_offset;
		}
		else
			Window::unlockCursor();

		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		glm::vec3 direction{};
		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->target = glm::normalize(direction);

		this->lookAt = glm::lookAt(this->eye, this->eye + this->target, this->up);

		notifyObservers(CameraMoved, this);
	}
}
