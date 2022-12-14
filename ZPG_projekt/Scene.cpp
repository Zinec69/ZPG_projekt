#include "Scene.h"

Scene::Scene()
{
	Mouse::getInstance().registerObserver(*this);
}

void Scene::render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (int i = 0; i < this->objects.size(); i++)
	{
		auto object = this->objects.begin();
		std::advance(object, i);
		glStencilFunc(GL_ALWAYS, object->first, 0xFF);

		if (object->second->isSkyBox() && i > 0)
		{
			fprintf(stderr, "SkyBox must be the first object to render\n");
			exit(EXIT_FAILURE);
		}
		if (!object->second->isActive())
			continue;

		if (i == this->objects.size() - 1 && !this->objects[i]->isLightSource())
		{
			this->objects[i]->move(glm::vec3(1, 0, 0));
			this->objects[i]->rotate(2, glm::vec3(0, 1, 1), glm::vec3(1, 0, 0));
		}
		
		object->second->draw(this->lights);
	}
}

void Scene::addObject(DrawObject* object)
{
	auto _object = this->objects.begin();
	std::advance(_object, this->objects.size() - 1);
	this->objects.insert(std::pair<int, DrawObject*>(_object->first + 1, object));
}

void Scene::setObjects(std::map<int, DrawObject*> objects)
{
	this->objects = objects;
}

void Scene::removeObject(int id)
{
	this->objects.erase(id);
}

void Scene::addLight(Light* light)
{
	this->lights.push_back(light);
}

void Scene::setLights(std::vector<Light*> lights)
{
	this->lights = lights;
}

void Scene::addShader(ShaderManager* shader)
{
	this->shaders.insert(std::pair<ShaderType, ShaderManager*>(shader->getType(), shader));
}

void Scene::setShaders(std::map<ShaderType, ShaderManager*> shaders)
{
	this->shaders = shaders;
}

ShaderManager* Scene::getShader(ShaderType shaderType)
{
	return this->shaders.at(shaderType);
}

void Scene::addModel(Model* model, std::string name)
{
	this->models.insert(std::pair<std::string, Model*>(name, model));
}

void Scene::setModels(std::map<std::string, Model*> models)
{
	this->models = models;
}

Model* Scene::getModel(std::string model_name)
{
	return this->models.at(model_name);
}

void Scene::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == MouseClicked)
	{
		if (Mouse::getInstance().button_clicked == GLFW_MOUSE_BUTTON_RIGHT)
		{
			GLbyte color[4];
			GLfloat depth;
			GLuint object_id;

			int width, height;
			glfwGetFramebufferSize(static_cast<GLFWwindow*>(object), &width, &height);

			GLint x = (GLint)Mouse::getInstance().x;
			GLint y = (GLint)Mouse::getInstance().y;

			int newy = height - y;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &object_id);

			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, object_id);

			//M????eme nastavit vybran?? t??leso scena->setSelect(index-1);

			//M????eme vypo????st pozici v glob??ln??m sou??adn??m syst??mu.
			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::vec4 viewPort = glm::vec4(0, 0, width, height);
			glm::vec3 pos = glm::unProject(screenX, Camera::getInstance().getCamera(), Camera::getInstance().getPerspective(), viewPort);

			printf("unProject [%f, %f, %f]\n", pos.x, pos.y, pos.z);

			if (object_id > 0)
			{
				DrawObject* tree = new DrawObject(this->getModel("tree"), this->getShader(ShaderType::MULTIPLE_LIGHTS_TEX), "Textures/tree_1.png", 0.75, glm::vec3(pos.x, pos.y, pos.z));
				this->addObject(tree);
			}
		}
		else if (Mouse::getInstance().button_clicked == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			GLbyte color[4];
			GLfloat depth;
			GLuint object_id;

			int width, height;
			glfwGetFramebufferSize(static_cast<GLFWwindow*>(object), &width, &height);

			GLint x = (GLint)Mouse::getInstance().x;
			GLint y = (GLint)Mouse::getInstance().y;

			int newy = height - y;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &object_id);

			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, object_id);

			//M????eme nastavit vybran?? t??leso scena->setSelect(index-1);

			//M????eme vypo????st pozici v glob??ln??m sou??adn??m syst??mu.
			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::vec4 viewPort = glm::vec4(0, 0, width, height);
			glm::vec3 pos = glm::unProject(screenX, Camera::getInstance().getCamera(), Camera::getInstance().getPerspective(), viewPort);

			printf("unProject [%f, %f, %f]\n", pos.x, pos.y, pos.z);

			if (object_id > 0)
			{
				removeObject(object_id);
			}
		}
	}
}
