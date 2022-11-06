#include "Camera.h"

glm::vec3 Camera::eye{ 0.f, 0.f, 5.f };
glm::vec3 Camera::target{ 0.f, 0.f, -1.f };
glm::vec3 Camera::up{ 0.f, 1.f, 0.f };
float Camera::yaw = -90;
float Camera::pitch = 1;
int Camera::mouse_last_x = WINDOW_WIDTH / 2;
int Camera::mouse_last_y = WINDOW_HEIGHT / 2;
float Camera::FOV = 90;
glm::mat4 Camera::perspective = glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

glm::mat4 Camera::getCamera()
{
	move();
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getPerspective()
{
	return perspective;
}

glm::vec3 Camera::getPosition()
{
	return eye;
}

glm::vec3 Camera::getTarget()
{
	return target;
}

void Camera::setPerspective(float FOV, float width, float height)
{
	perspective = glm::perspective(glm::radians(FOV), width / height, 0.1f, 100.0f);
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
			eye += cameraSpeed * target;
		if (Keyboard::key_pressed == GLFW_KEY_S)
			eye -= cameraSpeed * target;
		if (Keyboard::key_pressed == GLFW_KEY_A)
			eye -= glm::normalize(glm::cross(target, up)) * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_D)
			eye += glm::normalize(glm::cross(target, up)) * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_SPACE)
			eye += up * cameraSpeed;
		if (Keyboard::key_pressed == GLFW_KEY_LEFT_CONTROL)
			eye -= up * cameraSpeed;

		float x_offset = Mouse::x - mouse_last_x;
		float y_offset = mouse_last_y - Mouse::y;

		mouse_last_x = Mouse::x;
		mouse_last_y = Mouse::y;

		const float sensitivity = 0.1f;
		x_offset *= sensitivity;
		y_offset *= sensitivity;

		if (Mouse::button_clicked == GLFW_MOUSE_BUTTON_LEFT)
		{
			Window::lockCursor();
			yaw += x_offset;
			pitch += y_offset;
		}
		else
			Window::unlockCursor();

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction{};
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		target = glm::normalize(direction);
	}
}
