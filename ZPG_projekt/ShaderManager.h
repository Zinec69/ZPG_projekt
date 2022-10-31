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
	void useMat(glm::mat4 mat, const char name[]);
	void useVec(glm::vec3 vec, const char name[]);
	void useFloat(float num, const char name[]);
	shaderType getType();
};
