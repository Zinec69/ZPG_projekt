#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader, float scale, glm::vec3 color, glm::vec3 position)
{
	this->model = model;
	this->shader = shader;
	this->color = color;
	this->scale = scale;
	this->object = glm::translate(glm::mat4{ 1.0 }, position);
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
			this->shader->setVec3(this->lights[0]->color, "lightColor");
		}
		else
		{
			this->shader->setInt(this->material.shininess, "material.shininess");

			for (int i = 0; i < this->lights.size(); i++)
			{
				this->shader->setInt(this->lights[i]->state, "lights[" + to_string(i) + "].state");
				this->shader->setInt(this->lights[i]->type, "lights[" + to_string(i) + "].type");
				this->shader->setFloat(this->lights[i]->ambientStrength, "lights[" + to_string(i) + "].ambientStrength");
				this->shader->setFloat(this->lights[i]->specularStrength, "lights[" + to_string(i) + "].specularStrength");
				this->shader->setFloat(this->lights[i]->intensity, "lights[" + to_string(i) + "].intensity");
				this->shader->setVec3(this->lights[i]->color, "lights[" + to_string(i) + "].color");
				this->shader->setVec3(this->lights[i]->position, "lights[" + to_string(i) + "].position");
				this->shader->setVec3(this->lights[i]->direction, "lights[" + to_string(i) + "].direction");
				this->shader->setFloat(this->lights[i]->cutOff, "lights[" + to_string(i) + "].cutOff");
				this->shader->setFloat(this->lights[i]->outerCutOff, "lights[" + to_string(i) + "].outerCutOff");
			}

			this->shader->setInt(this->lights.size() <= 100 ? this->lights.size() : 100, "numOfLights");
		}
	}
	else
		this->shader->setVec3(this->lights[0]->color, "lightColor");

	this->model->draw();
}

void DrawObject::addLight(Light* light)
{
	this->lights.push_back(light);
}

void DrawObject::setLights(std::vector<Light*> lights)
{
	this->lights = lights;
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

void DrawObject::changeShininess(int shininess)
{
	this->material.shininess = shininess;
}

bool DrawObject::isLightSource() const
{
	return this->shader->getType() == LIGHT_SOURCE;
}
