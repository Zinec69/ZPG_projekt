#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader)
{
	this->model = model;
	this->shader = shader;
}

void DrawObject::draw()
{
	this->shader->useProgram();

	this->shader->setMat(this->object, "model");
	this->shader->setMat(Camera::getCamera(), "view");
	this->shader->setMat(Camera::getPerspective(), "projection");
	this->shader->setFloat(this->scale, "scale");

	if (this->shader->getType() != LIGHT_SOURCE)
	{
		this->shader->setVec3(this->color, "objectColor");
		this->shader->setVec3(Camera::getPosition(), "viewPos");
		if (this->shader->getType() != MULTIPLE_LIGHTS)
		{
			this->shader->setVec3(glm::vec3(0.0, 0.0, 0.0), "lightPos");
			this->shader->setVec3(this->lightColor, "lightColor");
		}
		else
		{
			this->shader->setInt(32, "shininess");

			this->shader->setInt(POINT, "lights[0].type");
			this->shader->setFloat(0.1, "lights[0].ambientStrength");
			this->shader->setFloat(0.5, "lights[0].specularStrength");
			this->shader->setVec3(this->lightColor, "lights[0].color");
			this->shader->setVec3(glm::vec3(4.0, 4.0, 0.0), "lights[0].position");

			this->shader->setInt(POINT, "lights[1].type");
			this->shader->setFloat(0.1, "lights[1].ambientStrength");
			this->shader->setFloat(0.5, "lights[1].specularStrength");
			this->shader->setVec3(this->lightColor, "lights[1].color");
			this->shader->setVec3(this->lightPos, "lights[1].position");

			this->shader->setInt(this->spotLightOn, "spotLightOn");
			this->shader->setInt(this->pointLightsOn, "pointLightsOn");

			this->shader->setInt(SPOT, "lights[2].type");
			this->shader->setFloat(0.05, "lights[2].ambientStrength");
			this->shader->setFloat(0.5, "lights[2].specularStrength");
			this->shader->setVec3(this->lightColor, "lights[2].color");
			this->shader->setVec3(Camera::getPosition(), "lights[2].position");
			this->shader->setVec3(Camera::getTarget(), "lights[2].direction");
			this->shader->setFloat(glm::cos(glm::radians(13.0)), "lights[2].cutOff");
			this->shader->setFloat(glm::cos(glm::radians(22.0)), "lights[2].outerCutOff");

			this->shader->setInt(3, "numOfLights");
		}
	}
	else
		this->shader->setVec3(this->lightColor, "lightColor");

	this->model->draw();
}

void DrawObject::transform()
{
	glm::mat4 t = glm::mat4{ 1.0 };
}

void DrawObject::rotate(float angle, glm::vec3 axis)
{
	this->object = glm::rotate(glm::mat4{ 1.0 }, glm::radians(angle), axis);
}

void DrawObject::rotate(float angle, glm::vec3 axis, glm::vec3 point)
{
	glm::mat4 m = glm::translate(this->object, point);
	m = glm::rotate(m, glm::radians(angle), axis);
	this->object = glm::translate(m, -point);
}

void DrawObject::resize(glm::vec3 multiplier)
{
	this->object = glm::scale(glm::mat4{ 1.0 }, multiplier);
}

void DrawObject::move(glm::vec3 point)
{
	this->object = glm::translate(glm::mat4{ 1.0 }, point);
}

void DrawObject::changeColor(glm::vec3 color)
{
	this->color = color;
}

void DrawObject::changeSize(float size)
{
	this->scale = size;
}

void DrawObject::setPointLights(bool on)
{
	this->pointLightsOn = on ? 1 : 0;
}

void DrawObject::setSpotLight(bool on)
{
	this->spotLightOn = on ? 1 : 0;
}

void DrawObject::changeLightColor(glm::vec3 color)
{
	this->lightColor = color;
}

void DrawObject::moveLight(glm::vec3 position)
{
	this->lightPos = position;
}
