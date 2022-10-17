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
	addShader(this->vertex_shader_code, GL_VERTEX_SHADER);
	addShader(this->fragment_shader_code, GL_FRAGMENT_SHADER);

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

void ShaderManager::transform(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	if (modelId == -1) fprintf(stderr, "Failed getting model matrix\n");
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &modelMatrix[0][0]);

	modelId = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
	if (modelId == -1) fprintf(stderr, "Failed getting projection matrix\n");
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &projectionMatrix[0][0]);

	modelId = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	if (modelId == -1) fprintf(stderr, "Failed getting view matrix\n");
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &viewMatrix[0][0]);
}
