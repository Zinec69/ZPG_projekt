#include "DrawObject.h"

DrawObject::DrawObject(Model* model, ShaderManager* shader, float scale, glm::vec3 position, glm::vec3 color)
{
	this->model = model;
	this->shader = shader;
	this->scale = scale;
	this->object = glm::translate(glm::mat4{ 1.0 }, position);
	this->color = color;
}

DrawObject::DrawObject(Model* model, ShaderManager* shader, const char* texture_filename, float scale, glm::vec3 position)
{
	this->model = model;
	this->shader = shader;
	this->scale = scale;
	this->object = glm::translate(glm::mat4{ 1.0 }, position);
	if (model->getType() == ModelType::CUBEMAP)
		this->texture = loadCubemap(texture_filename);
	else
		this->texture = loadTexture(texture_filename);
}

DrawObject::DrawObject(Model* model, ShaderManager* shader, const char* texture_filenames[6], float scale)
{
	this->model = model;
	this->shader = shader;
	this->scale = scale;
	this->object = glm::translate(glm::mat4{ 1.0 }, glm::vec3(0.0));
	this->texture = loadCubemap(texture_filenames);
}

void DrawObject::draw(std::vector<Light*> lights)
{
	//if (this->model->getType() == CUBEMAP)
	//	glDepthMask(GL_FALSE);

	this->shader->useProgram();

	this->shader->setCameraData();
	
	this->applyTextures();

	if (this->shader->getType() != shaderType::SKYBOX)
		this->shader->setMat(this->object, "model");
	
	this->shader->setFloat(this->scale, "scale");

	if (this->shader->getType() == shaderType::SKYBOX)
	{
		this->shader->setInt(0, "SkyBox");
	}
	else if (this->shader->getType() != shaderType::LIGHT_SOURCE)
	{
		if (this->model->getType() == ModelType::COLORED)
			this->shader->setVec3(this->color, "objectColor");

		if (this->shader->getType() != shaderType::MULTIPLE_LIGHTS && this->shader->getType() != shaderType::MULTIPLE_LIGHTS_TEX)
		{
			this->shader->setVec3(lights[0]->position, "lightPos");
			this->shader->setVec3(lights[0]->color, "lightColor");
		}
		else
		{
			this->shader->setFloat(this->material.shininess, "material.shininess");
			if (this->model->getType() == ModelType::TEXTURED)
			{
				this->shader->setInt(0, "material.diffuse");
				this->shader->setInt(1, "material.specular");
			}

			for (int i = 0; i < lights.size(); i++)
			{
				this->shader->setInt(lights[i]->state, "lights[" + to_string(i) + "].state");
				this->shader->setInt(lights[i]->type, "lights[" + to_string(i) + "].type");
				this->shader->setFloat(lights[i]->ambientStrength, "lights[" + to_string(i) + "].ambientStrength");
				this->shader->setFloat(lights[i]->specularStrength, "lights[" + to_string(i) + "].specularStrength");
				this->shader->setFloat(lights[i]->intensity, "lights[" + to_string(i) + "].intensity");
				this->shader->setVec3(lights[i]->color, "lights[" + to_string(i) + "].color");
				this->shader->setVec3(lights[i]->position, "lights[" + to_string(i) + "].position");
				this->shader->setVec3(lights[i]->direction, "lights[" + to_string(i) + "].direction");
				this->shader->setFloat(lights[i]->cutOff, "lights[" + to_string(i) + "].cutOff");
			}

			this->shader->setInt(lights.size() <= 100 ? lights.size() : 100, "numOfLights");
		}
	}
	else
		this->shader->setVec3(lights[0]->color, "lightColor");

	this->model->draw();

	//if (this->model->getType() == CUBEMAP)
	//	glDepthMask(GL_TRUE);
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
	return this->shader->getType() == shaderType::LIGHT_SOURCE;
}

bool DrawObject::isSkyBox() const
{
	return this->model->getType() == ModelType::SKYBOX;
}

bool DrawObject::isActive() const
{
	return this->active;
}

GLuint DrawObject::loadTexture(const char* filename)
{
	GLuint image = SOIL_load_OGL_texture(filename, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (image == 0)
	{
		std::cout << "An error occurred while loading texture image\n";
		exit(EXIT_FAILURE);
	}
	return image;
}

GLuint DrawObject::loadCubemap(const char* filenames[6])
{
	GLuint image = SOIL_load_OGL_cubemap(filenames[0], filenames[1], filenames[2], filenames[3], filenames[4], filenames[5], SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (image == 0)
	{
		std::cout << "An error occurred while loading multi-file cubemap texture\n";
		exit(EXIT_FAILURE);
	}
	return image;
}

GLuint DrawObject::loadCubemap(const char* filename)
{
	GLuint image = SOIL_load_OGL_single_cubemap(filename, SOIL_DDS_CUBEMAP_FACE_ORDER, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (image == 0)
	{
		std::cout << "An error occurred while loading single-file cubemap texture\n";
		exit(EXIT_FAILURE);
	}
	return image;
}

void DrawObject::applyTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	if (isSkyBox())
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void DrawObject::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == LightMoved)
	{
		move(((Light*)object)->position);
	}
	else if (eventType == LightChangedState)
	{
		this->active = !this->active;
	}
}
