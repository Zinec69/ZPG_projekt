#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include <vector>

class ShaderManager
{
private:
	std::vector<GLuint> shaders;
	GLuint shaderProgram;
	void addShader(const char* shader_code, int type);
	void createProgram();
	void pollInfoLogs();
	const char* vertex_shader_code =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 vc;"
		"out vec4 color;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"void main () {"
		"	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp);"
		"	color = vc;"
		"}";
	const char* fragment_shader_code =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"	frag_colour = vec4(color);"
		"}";
public:
	ShaderManager();
	void useProgram();
	void transform(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
};
