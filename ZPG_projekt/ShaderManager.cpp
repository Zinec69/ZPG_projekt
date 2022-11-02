#include "ShaderManager.h"

ShaderManager::ShaderManager(shaderType type)
{
	this->type = type;

	switch (this->type)
	{
	case BASIC:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_basic.txt", "../ZPG_projekt/Shaders/fragment_basic.txt");
		break;
	case LAMBERT:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_light.txt", "../ZPG_projekt/Shaders/fragment_lambert.txt");
		break;
	case PHONG:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_light.txt", "../ZPG_projekt/Shaders/fragment_phong.txt");
		break;
	case PHONG_1:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_light.txt", "../ZPG_projekt/Shaders/fragment_phong_1.txt");
		break;
	case BLINN:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_light.txt", "../ZPG_projekt/Shaders/fragment_blinn.txt");
		break;
	case MULTIPLE_LIGHTS:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_light.txt", "../ZPG_projekt/Shaders/fragment_multiple_lights.txt");
		break;
	}

	pollInfoLogs();
}

//void ShaderManager::addShader(const char* shader_code, int type)
//{
//	GLuint shader = glCreateShader(type);
//	glShaderSource(shader, 1, &shader_code, NULL);
//	glCompileShader(shader);
//	this->shaders.push_back(shader);
//}

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

void ShaderManager::useProgram()
{
	glUseProgram(this->shaderProgram);
}

void ShaderManager::setMat(glm::mat4 mat, const char name[])
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name);
	if (modelId == -1)
	{
		std::string err = "[Shader error] ";
		err += name;
		err += " matrix not found\n";
		fprintf(stderr, err.c_str());
		exit(1);
	}
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::setVec(glm::vec3 vec, const char name[])
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name);
	if (modelId == -1)
	{
		std::string err = "[Shader error] ";
		err += name;
		err += " vector not found\n";
		fprintf(stderr, err.c_str());
		exit(1);
	}
	else glUniform3fv(modelId, 1, &vec[0]);
}

void ShaderManager::setFloat(float num, const char name[])
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name);
	if (modelId == -1)
	{
		std::string err = "[Shader error] ";
		err += name;
		err += " float not found\n";
		fprintf(stderr, err.c_str());
		exit(1);
	}
	else glUniform1f(modelId, num);
}

void ShaderManager::setInt(int num, const char name[])
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name);
	if (modelId == -1)
	{
		std::string err = "[Shader error] ";
		err += name;
		err += " int not found\n";
		fprintf(stderr, err.c_str());
		exit(1);
	}
	else glUniform1i(modelId, num);
}

shaderType ShaderManager::getType()
{
	return this->type;
}
