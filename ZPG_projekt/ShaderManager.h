#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "ShaderLoader.h"
#include <vector>

enum shaderType {
	BASIC,
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
	void setMat(glm::mat4 mat, const char name[]);
	void setVec(glm::vec3 vec, const char name[]);
	void setFloat(float num, const char name[]);
	void setInt(int num, const char name[]);
	shaderType getType();
};
