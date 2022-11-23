#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "ShaderLoader.h"
#include "Observer.h"
#include <vector>

enum class ShaderType
{
	LIGHT_SOURCE,
	LAMBERT,
	PHONG,
	PHONG_1,
	BLINN,
	MULTIPLE_LIGHTS,
	MULTIPLE_LIGHTS_TEX,
	SKYBOX,
};

class ShaderManager : ShaderLoader, public Observer
{
private:
	GLuint shaderProgram;
	ShaderType type;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
	glm::vec3 cameraPosition;

	void pollInfoLogs();
public:
	ShaderManager(ShaderType type);
	void useProgram();
	void setMat(glm::mat4 mat, const std::string name);
	void setVec3(glm::vec3 vec, const std::string name);
	void setFloat(float num, const std::string name);
	void setInt(int num, const std::string name);
	void setCameraData();
	ShaderType getType();

	void onSubjectNotification(EventType eventType, void* object) override;
};
