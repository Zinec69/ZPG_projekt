#pragma once

#include "Model.h"
#include "ShaderManager.h"
#include "Camera.h"

class DrawObject
{
private:
	glm::mat4 object{ 1.0 };
	glm::vec3 color{ 1.0, 1.0, 0.0 };
	glm::vec3 lightPos{ -4.0, 4.0, 0.0 };
	glm::vec3 lightColor{ 1.0, 1.0, 1.0 };
	int spotLightOn = 1;
	int pointLightsOn = 1;
	float scale = 1;

	enum LightType {
		POINT = 1,
		SPOT = 2,
	};

	Model* model;
	ShaderManager* shader;
	void transform();
public:
	DrawObject(Model* model, ShaderManager* shader);
	void draw();
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle, glm::vec3 axis, glm::vec3 point);
	void resize(glm::vec3 multiplier);
	void move(glm::vec3 point);
	void changeColor(glm::vec3 color);
	void changeSize(float size);
	void setPointLights(bool on);
	void setSpotLight(bool on);
	void changeLightColor(glm::vec3 color);
	void moveLight(glm::vec3 position);
};
