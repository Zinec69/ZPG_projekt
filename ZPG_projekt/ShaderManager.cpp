#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	createProgram();
}

void ShaderManager::addShader(const char* shader_code, int type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_code, NULL);
	glCompileShader(shader);
	this->shaders.push_back(shader);
}

void ShaderManager::createProgram()
{
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 vc;"
		"out vec4 color;"
		"uniform mat4 modelMatrix;"
		"void main () {"
		"	gl_Position = modelMatrix * vec4(vp);"
		"	color = vc;"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"	frag_colour = vec4(color);"
		"}";

	addShader(vertex_shader, GL_VERTEX_SHADER);
	addShader(fragment_shader, GL_FRAGMENT_SHADER);

	this->shaderProgram = glCreateProgram();
	for (int i = 0; i < this->shaders.size(); i++)
		glAttachShader(this->shaderProgram, this->shaders[i]);
	glLinkProgram(this->shaderProgram);

	pollInfoLogs();
}

void ShaderManager::useProgram()
{
	glUseProgram(this->shaderProgram);
}

void ShaderManager::pollInfoLogs()
{
	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderManager::transform(glm::mat4 position)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUniformMatrix4fv(modelId, 1, GL_FALSE, &position[0][0]);
}
