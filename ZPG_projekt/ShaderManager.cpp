#include "ShaderManager.h"

ShaderManager::ShaderManager(ShaderType type)
{
	this->type = type;

	switch (this->type)
	{
	case ShaderType::LIGHT_SOURCE:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/light_source.vert", "../ZPG_projekt/Shaders/light_source.frag");
		break;
	case ShaderType::LAMBERT:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/lambert.frag");
		break;
	case ShaderType::PHONG:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/phong.frag");
		break;
	case ShaderType::PHONG_1:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/phong_1.frag");
		break;
	case ShaderType::BLINN:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/blinn.frag");
		break;
	case ShaderType::MULTIPLE_LIGHTS:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex.vert", "../ZPG_projekt/Shaders/multiple_lights.frag");
		break;
	case ShaderType::MULTIPLE_LIGHTS_TEX:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/vertex_tex.vert", "../ZPG_projekt/Shaders/multiple_lights_tex.frag");
		break;
	case ShaderType::SKYBOX:
		this->shaderProgram = loadShader("../ZPG_projekt/Shaders/cubemap.vert", "../ZPG_projekt/Shaders/cubemap.frag");
		break;
	}

	this->projectionMat = Camera::getInstance().getPerspective();
	this->cameraPosition = Camera::getInstance().getPosition();
	this->viewMat = Camera::getInstance().getCamera();

	Camera::getInstance().registerObserver(*this);

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

void ShaderManager::useProgram()
{
	glUseProgram(this->shaderProgram);
}

void ShaderManager::setMat(glm::mat4 mat, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (modelId == -1)
	{
		std::string err = "[Shader error] Matrix '";
		err += name;
		err += "' not found\n";
		fprintf(stderr, err.c_str());
		exit(EXIT_FAILURE);
	}
	else glUniformMatrix4fv(modelId, 1, GL_FALSE, &mat[0][0]);
}

void ShaderManager::setVec3(glm::vec3 vec, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (modelId == -1)
	{
		std::string err = "[Shader error] Vector '";
		err += name;
		err += "' not found\n";
		fprintf(stderr, err.c_str());
		exit(EXIT_FAILURE);
	}
	else glUniform3fv(modelId, 1, &vec[0]);
}

void ShaderManager::setFloat(float num, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (modelId == -1)
	{
		std::string err = "[Shader error] Float '";
		err += name;
		err += "' not found\n";
		fprintf(stderr, err.c_str());
		exit(EXIT_FAILURE);
	}
	else glUniform1f(modelId, num);
}

void ShaderManager::setInt(int num, const std::string name)
{
	GLint modelId = glGetUniformLocation(this->shaderProgram, name.c_str());
	if (modelId == -1)
	{
		std::string err = "[Shader error] Int '";
		err += name;
		err += "' not found\n";
		fprintf(stderr, err.c_str());
		exit(EXIT_FAILURE);
	}
	else glUniform1i(modelId, num);
}

void ShaderManager::setCameraData()
{
	setMat(this->viewMat, "view");
	setMat(this->projectionMat, "projection");
	if (this->type != ShaderType::LIGHT_SOURCE && this->type != ShaderType::SKYBOX && this->type != ShaderType::LAMBERT)
		setVec3(this->cameraPosition, "viewPos");
}

ShaderType ShaderManager::getType()
{
	return this->type;
}

void ShaderManager::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == CameraMoved)
	{
		this->cameraPosition = Camera::getInstance().getPosition();
		this->viewMat = Camera::getInstance().getCamera();
	}
	else if (eventType == WindowSizeChanged)
	{
		this->projectionMat = Camera::getInstance().getPerspective();
	}
}
