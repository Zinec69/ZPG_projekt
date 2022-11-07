#include "ShaderManager.h"

ShaderManager::ShaderManager(shaderType type)
{
	this->type = type;

	switch (this->type)
	{
	case LIGHT_SOURCE:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/light_source.vert", "../ZPG_projekt/Shaders/light_source.frag");
		break;
	case LAMBERT:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/lambert.frag");
		break;
	case PHONG:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/phong.frag");
		break;
	case PHONG_1:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/phong_1.frag");
		break;
	case BLINN:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/blinn.frag");
		break;
	case MULTIPLE_LIGHTS:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/multiple_lights.frag");
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

void ShaderManager::setMat(glm::mat4 mat, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
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

void ShaderManager::setVec3(glm::vec3 vec, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
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

void ShaderManager::setFloat(float num, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
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

void ShaderManager::setInt(int num, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
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

void ShaderManager::setCameraData()
{
	setMat(this->viewMat, "view");
	setMat(this->projectionMat, "projection");
	if (this->type != LIGHT_SOURCE)
		setVec3(this->cameraPosition, "viewPos");
}

shaderType ShaderManager::getType()
{
	return this->type;
}

void ShaderManager::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == CameraMoved)
	{
		this->cameraPosition = Camera::getInstance().getPosition();
		this->viewMat = Camera::getInstance().getCamera();

		printMat(Camera::getInstance().getCamera());
	}
	else if (eventType == WindowSizeChanged)
	{
		this->projectionMat = Camera::getInstance().getPerspective();
	}
}
