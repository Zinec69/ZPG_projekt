#include "Camera.h"

Camera::Camera()
{
	Mouse::getInstance().registerObserver(*this);
	Keyboard::getInstance().registerObserver(*this);
}

glm::mat4 Camera::getCamera() const
{
	return this->lookAt;
}

glm::mat4 Camera::getPerspective() const
{
	return this->perspective;
}

glm::vec3 Camera::getPosition() const
{
	return this->eye;
}

glm::vec3 Camera::getTarget() const
{
	return this->target;
}

int Camera::getFOV() const
{
	return static_cast<int>(this->FOV);
}

void Camera::setPerspective(float FOV, float width, float height)
{
	this->FOV = FOV;
	this->perspective = glm::perspective(glm::radians(FOV), width / height, 0.1f, 100.0f);
	notifyObservers(WindowSizeChanged, this);
}

void Camera::changePosition()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (!io.WantCaptureMouse)
	{
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_W)
			this->eye += this->movementSpeed * this->target;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_S)
			this->eye -= this->movementSpeed * this->target;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_A)
			this->eye -= glm::normalize(glm::cross(this->target, this->up)) * this->movementSpeed;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_D)
			this->eye += glm::normalize(glm::cross(this->target, this->up)) * this->movementSpeed;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_SPACE)
			this->eye += this->up * this->movementSpeed;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_LEFT_CONTROL)
			this->eye -= this->up * this->movementSpeed;

		this->lookAt = glm::lookAt(this->eye, this->eye + this->target, this->up);

		notifyObservers(CameraMoved, this);
	}
}

void Camera::changeTarget()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (!io.WantCaptureMouse)
	{
		float x_offset = (Mouse::getInstance().x - this->mouse_last_x) * this->mouseSensitivity;
		float y_offset = (this->mouse_last_y - Mouse::getInstance().y) * this->mouseSensitivity;

		this->mouse_last_x = Mouse::getInstance().x;
		this->mouse_last_y = Mouse::getInstance().y;

		if (Mouse::getInstance().button_clicked == GLFW_MOUSE_BUTTON_LEFT)
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

void Camera::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == MouseMoved)
	{
		changeTarget();
	}
	else if (eventType == MouseClicked)
	{
	}
	else if (eventType == MouseScrolled)
	{
		this->FOV -= Mouse::getInstance().scroll;
		setPerspective(this->FOV, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
	}
	else if (eventType == KeyboardPressed)
	{
		changePosition();
	}
}
