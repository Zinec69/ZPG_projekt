#include "Application.h"

Application::Application(int windowWidth, int windowHeight)
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = new Window(windowWidth, windowHeight, "ZPG");

	glewExperimental = GL_TRUE;
	glewInit();

	const colorPoints triangle1[] = {
		{{ -0.75, -0.5, 0.5, 1 }, { 1, 1, 0, 1 }},
		{{ -0.1, -0.5, 0.5, 1 }, { 1, 0, 0, 1 }},
		{{ -0.1, 0.5, 0.5, 1 }, { 0, 0, 1, 1 }}
	};

	const colorPoints triangle2[] = {
		{{ 0.75, -0.5, 0.5, 1 }, { 1, 1, 0, 1 }},
		{{ 0.1, -0.5, 0.5, 1 }, { 0, 1, 0, 1 }},
		{{ 0.1, 0.5, 0.5, 1 }, { 0, 1, 1, 1 }}
	};

	const colorPoints rectangle[] = {
		{{ -0.5, -0.5, 0.5, 1.5 }, { 0, 0.5, 0.5, 1 }},
		{{ 0.5, -0.5, 0.5, 1.5 }, { 1, 0, 0.5, 1 }},
		{{ 0.5, 0.5, 0.5, 1.5 }, { 0.25, 0, 0, 1 }},
		{{ -0.5, 0.5, 0.5, 1.5 }, { 1, 1, 0, 1 }}
	};

	Model* model_1 = new Model(triangle1, sizeof(triangle1), sizeof(triangle1) / sizeof(triangle1[0]));
	Model* model_2 = new Model(triangle2, sizeof(triangle2), sizeof(triangle2) / sizeof(triangle2[0]));
	Model* model_3 = new Model(rectangle, sizeof(rectangle), sizeof(rectangle) / sizeof(rectangle[0]));
	ShaderManager* shaders = new ShaderManager();

	DrawObject* drawObject_1 = new DrawObject(model_1, shaders);
	DrawObject* drawObject_2 = new DrawObject(model_2, shaders);
	DrawObject* drawObject_3 = new DrawObject(model_3, shaders);

	this->drawObjects.push_back(drawObject_1);
	this->drawObjects.push_back(drawObject_2);
	this->drawObjects.push_back(drawObject_3);

	printInfo();
}

void Application::loop()
{
	while (!this->window->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->drawObjects[2]->rotate(glm::vec3(0, 0, -0.01));

		for (int i = 0; i < this->drawObjects.size(); i++)
		{
			this->drawObjects[i]->draw();
		}

		glfwPollEvents();
		this->window->swapBuffers();
	}
}

void Application::printInfo()
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("OpenGL Version:\t%s\n", glGetString(GL_VERSION));
	printf("GLEW Version:\t%s\n", glewGetString(GLEW_VERSION));
	printf("GLFW Version:\t%i.%i.%i\n", major, minor, revision);
	printf("GLSL Version:\t%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor:\t\t%s\n", glGetString(GL_VENDOR));
	printf("Renderer:\t%s\n", glGetString(GL_RENDERER));
}

Application::~Application()
{
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
