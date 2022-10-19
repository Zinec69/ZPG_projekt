#include "Application.h"
#include "Models.h"

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

	Model* model_1 = new Model(triangle1, sizeof(triangle1), sizeof(triangle1) / sizeof(colorPoints));
	Model* model_2 = new Model(triangle2, sizeof(triangle2), sizeof(triangle2) / sizeof(colorPoints));
	Model* model_3 = new Model(cube, sizeof(cube), sizeof(cube) / sizeof(colorPoints));
	Model* model_4 = new Model(sphere, sizeof(sphere), sizeof(sphere) / sizeof(colorPoints));

	ShaderManager* shaders = new ShaderManager();

	DrawObject* drawObject_1 = new DrawObject(model_1, shaders);
	DrawObject* drawObject_2 = new DrawObject(model_2, shaders);
	DrawObject* drawObject_3 = new DrawObject(model_3, shaders);
	DrawObject* drawObject_4 = new DrawObject(model_4, shaders);

	this->drawObjects.push_back(drawObject_1);
	this->drawObjects.push_back(drawObject_2);
	this->drawObjects.push_back(drawObject_3);
	//this->drawObjects.push_back(drawObject_4);

	printInfo();
}

void Application::run()
{
	float x_rot = 0, y_rot = 0, tri_rot = 0;
	while (!this->window->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Keyboard::key_pressed == GLFW_KEY_LEFT) y_rot += 1;
		if (Keyboard::key_pressed == GLFW_KEY_RIGHT) y_rot -= 1;

		if (Keyboard::key_pressed == GLFW_KEY_UP) x_rot += 1;
		if (Keyboard::key_pressed == GLFW_KEY_DOWN) x_rot -= 1;

		this->drawObjects[0]->rotate(tri_rot, glm::vec3(-0.1, 0.5, 0.5), glm::vec3(0, 0, 1));
		this->drawObjects[1]->rotate(tri_rot, glm::vec3(0, 1, 0));
		//this->drawObjects[2]->move(glm::vec3(1, 1, 0));
		this->drawObjects[2]->rotate(x_rot, glm::vec3(1, 0, 0), glm::vec3(-0.5, 0.5, 0.5));
		this->drawObjects[2]->rotate(y_rot, glm::vec3(0, 1, 0), glm::vec3(-0.5, 0.5, 0.5));

		for (int i = 0; i < this->drawObjects.size(); i++)
		{
			this->drawObjects[i]->draw();
		}

		glfwPollEvents();
		this->window->swapBuffers();

		tri_rot--;
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
