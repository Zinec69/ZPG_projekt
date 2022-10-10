#pragma once

#include "GLincludes.h"
#include <vector>

class ShaderManager
{
private:
	std::vector<GLuint> shaders;
	GLuint shaderProgram;
public:
	ShaderManager();
	void addShader(const char* shader_code, int type);
	void createProgram();
	void useProgram();
	void pollInfoLogs();
	void transform(glm::mat4 position);
};
