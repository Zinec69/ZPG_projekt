#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//constexpr int WINDOW_WIDTH = 1280;
//constexpr int WINDOW_HEIGHT = 720;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

struct colorPoints
{
	float vertices[4];
	float color[4];
};
