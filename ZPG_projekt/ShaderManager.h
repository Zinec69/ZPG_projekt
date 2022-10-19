#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "Camera.h"
#include "ShaderLoader.h"
#include <vector>

class ShaderManager : ShaderLoader
{
private:
	GLuint shaderProgram;
	std::vector<GLuint> shaders;

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

	const char* vertex_shader_advanced_code =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 vc;"
		"out vec4 color;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"uniform mat3 normalMatrix;"
		"void main () {"
		"	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp);"
		"	ex_worldPosition = modelMatrix * vec4(vp);"
		"	ex_worldNormal = normalMatrix * in_Normal;"
		"	color = vc;"
		"}";
	const char* fragment_shader_advanced_code =
		"#version 330\n"
		"out vec4 out_Color;"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"in vec4 color;"
		"void main () {"
		"	vec3 lightPosition= vec3(0.0, 0.0, 0.0);"
		"	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);"
		"	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);"
		"	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
		"	out_Color = ambient + diffuse;"
		"	frag_colour = vec4(color);"
		"}";
public:
	ShaderManager();
	void useProgram();
	void transform(glm::mat4 modelMatrix);
};
