#pragma once

#include "GLincludes.h"
#include <vector>

class ShaderManager
{
private:
	std::vector<GLuint> shaders;
	GLuint shaderProgram;
	void addShader(const char* shader_code, int type);
	void createProgram();
	void pollInfoLogs();
public:
	ShaderManager();
	void useProgram();
	void transform(glm::mat4 position);
};
