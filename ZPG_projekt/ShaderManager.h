#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "ShaderLoader.h"
#include <vector>

enum shaderType {
	LIGHT_SOURCE,
	LAMBERT,
	PHONG,
	PHONG_1,
	BLINN,
	MULTIPLE_LIGHTS,
};

class ShaderManager : ShaderLoader
{
private:
	GLuint shaderProgram;
	shaderType type;

	void pollInfoLogs();
public:
	ShaderManager(shaderType type);
	void useProgram();
	void setMat(glm::mat4 mat, const std::string name);
	void setVec3(glm::vec3 vec, const std::string name);
	void setFloat(float num, const std::string name);
	void setInt(int num, const std::string name);
	shaderType getType();
};
