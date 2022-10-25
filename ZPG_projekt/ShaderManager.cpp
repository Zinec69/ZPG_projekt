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

//void ShaderManager::createProgram()
//{
//	addShader(this->vertex_shader_code, GL_VERTEX_SHADER);
//	addShader(this->fragment_shader_code, GL_FRAGMENT_SHADER);
//
//	this->shaderProgram = glCreateProgram();
//	for (int i = 0; i < this->shaders.size(); i++)
//		glAttachShader(this->shaderProgram, this->shaders[i]);
//	glLinkProgram(this->shaderProgram);
//	
//	pollInfoLogs();
//}

void ShaderManager::createProgram()
{
	this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.txt", "../ZPG_projekt/Shaders/fragment.txt");

	pollInfoLogs();
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

void ShaderManager::useProgram(glm::mat4 modelMatrix)
{
	glUseProgram(this->shaderProgram);

	GLint modelId = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	if (modelId == -1)
	{
		fprintf(stderr, "Failed getting model matrix\n");
		exit(1);
	}
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &modelMatrix[0][0]);

	modelId = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
	if (modelId == -1)
	{
		fprintf(stderr, "Failed getting projection matrix\n");
		exit(1);
	}
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &Camera::getPerspective()[0][0]);

	modelId = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	if (modelId == -1)
	{
		fprintf(stderr, "Failed getting view matrix\n");
		exit(1);
	}
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &Camera::getCamera()[0][0]);
}
