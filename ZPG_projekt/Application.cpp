#include "Application.h"

int scene = 1;

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

	//Model* model_1 = new Model(triangle1, sizeof(triangle1), sizeof(triangle1) / (sizeof(triangle1[0]) * 6));
	//Model* model_2 = new Model(triangle2, sizeof(triangle2), sizeof(triangle2) / (sizeof(triangle2[0]) * 6));
	//Model* model_3 = new Model(cube, sizeof(cube), sizeof(cube) / (sizeof(cube[0]) * 6));
	//Model* model_4 = new Model(sphere, sizeof(sphere), sizeof(sphere) / (sizeof(sphere[0]) * 6));
	//Model* model_5 = new Model(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / (sizeof(suziSmooth[0]) * 6));

	//DrawObject* drawObject_1 = new DrawObject(model_1, shaders);
	//DrawObject* drawObject_2 = new DrawObject(model_2, shaders);
	//DrawObject* drawObject_3 = new DrawObject(model_3, shaders);
	//DrawObject* drawObject_4 = new DrawObject(model_4, shaders);
	//DrawObject* drawObject_5 = new DrawObject(model_5, shaders);

	//this->drawObjects.push_back(drawObject_1);
	//this->drawObjects.push_back(drawObject_2);
	//this->drawObjects.push_back(drawObject_3);
	//this->drawObjects.push_back(drawObject_4);
	//this->drawObjects.push_back(drawObject_5);

	ShaderManager* shader_light_source = new ShaderManager(LIGHT_SOURCE);
	ShaderManager* shader_lambert = new ShaderManager(LAMBERT);
	ShaderManager* shader_phong = new ShaderManager(PHONG);
	ShaderManager* shader_phong_1 = new ShaderManager(PHONG_1);
	ShaderManager* shader_blinn = new ShaderManager(BLINN);
	ShaderManager* shader_multiple_lights = new ShaderManager(MULTIPLE_LIGHTS);

	if (scene == 1)
	{
		Model* model = new Model(sphere, sizeof(sphere), sizeof(sphere) / (sizeof(sphere[0]) * 6));
		DrawObject* drawObject = nullptr;

		for (int i = 0; i < 4; i++)
		{
			drawObject = new DrawObject(model, shader_multiple_lights);
			this->drawObjects.push_back(drawObject);
		}
		for (int i = 0; i < 2; i++)
		{
			drawObject = new DrawObject(model, shader_light_source);
			this->drawObjects.push_back(drawObject);
		}
	}
	else if (scene == 2)
	{
		Model* model = new Model(sphere, sizeof(sphere), sizeof(sphere) / (sizeof(sphere[0]) * 6));
		DrawObject* drawObject = new DrawObject(model, shader_phong_1);

		this->drawObjects.push_back(drawObject);
	}
	else if (scene == 3)
	{
		Model* _tree = new Model(tree, sizeof(tree), sizeof(tree) / (sizeof(tree[0]) * 6));
		Model* _bush = new Model(bush::plain, sizeof(bush::plain), sizeof(bush::plain) / (sizeof(bush::plain[0]) * 6));
		Model* _sphere = new Model(sphere, sizeof(sphere), sizeof(sphere) / (sizeof(sphere[0]) * 6));
		Model* _suzi = new Model(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / (sizeof(suziSmooth[0]) * 6));
		DrawObject* drawObject = nullptr;
		
		for (int i = 0; i < 111; i++)
		{
			int r = rand() % 4;
			switch (r)
			{
			case 0:
				drawObject = new DrawObject(_tree, shader_phong);
				this->drawObjects.push_back(drawObject);
				break;
			case 1:
				drawObject = new DrawObject(_bush, shader_phong);
				this->drawObjects.push_back(drawObject);
				break;
			case 2:
				drawObject = new DrawObject(_sphere, shader_phong);
				this->drawObjects.push_back(drawObject);
				break;
			case 3:
				drawObject = new DrawObject(_suzi, shader_phong);
				this->drawObjects.push_back(drawObject);
				break;
			}
		}

		Model* _plain = new Model(plane::plain, sizeof(plane::plain), sizeof(plane::plain) / (sizeof(plane::plain[0]) * 6));
		drawObject = new DrawObject(_plain, shader_phong);
		this->drawObjects.push_back(drawObject);
	}

	printInfo();
}

void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	this->window->initImgui();
	ImGui_ImplOpenGL3_Init("#version 330");

	glm::vec3 sphere1{ 1, 0, 0 }, sphere2{ 0, 1, 0 }, sphere3{ 0, 0, 1 }, sphere4{ 1, 0, 1 };
	glm::vec3 lightColor{ 1, 1, 1 };
	float sizes = 1;
	bool spot = true, point = true;

	if (scene == 1)
	{
	}
	else if (scene == 2)
	{
		this->drawObjects[0]->move(glm::vec3(2, 0, 0));
		this->drawObjects[0]->changeColor(glm::vec3(1, 0, 0));
	}
	else if (scene == 3)
	{
		this->drawObjects[this->drawObjects.size() - 1]->changeSize(50);
		for (int i = 0; i < this->drawObjects.size() - 1; i++)
		{
			this->drawObjects[i]->move(glm::vec3(rand() % 50, 1, rand() % 50));
			float r = (float)(rand() % 100) / 100, g = (float)(rand() % 100) / 100, b = (float)(rand() % 100) / 100;
			this->drawObjects[i]->changeColor(glm::vec3(r, g, b));
		}
	}

	float x_rot = 0, y_rot = 0, tri_rot = 0, light_rot = 0;
	while (!this->window->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (Keyboard::key_pressed == GLFW_KEY_LEFT) y_rot += 1;
		if (Keyboard::key_pressed == GLFW_KEY_RIGHT) y_rot -= 1;

		if (Keyboard::key_pressed == GLFW_KEY_UP) x_rot += 1;
		if (Keyboard::key_pressed == GLFW_KEY_DOWN) x_rot -= 1;

		//this->drawObjects[0]->move(glm::vec3(0, 0, 0));
		//this->drawObjects[0]->rotate(tri_rot, glm::vec3(0, 0, 1), glm::vec3(-0.1, 0.5, 0.5));
		//this->drawObjects[0]->changeColor(glm::vec3(1.0, 0.0, 1.0));

		//this->drawObjects[1]->rotate(tri_rot, glm::vec3(0, 1, 0));

		//this->drawObjects[2]->move(glm::vec3(-1, 1, -1));
		//this->drawObjects[2]->rotate(x_rot, glm::vec3(1, 0, 0), glm::vec3(-0.5, 0.5, 0.5));
		//this->drawObjects[2]->rotate(y_rot, glm::vec3(0, 1, 0), glm::vec3(-0.5, 0.5, 0.5));
		//this->drawObjects[2]->changeColor(glm::vec3(0.0, 0.0, 1.0));

		//this->drawObjects[3]->move(glm::vec3(1, 1.5, -1));
		//this->drawObjects[3]->changeColor(glm::vec3(1.0, 0.0, 0.0));

		//this->drawObjects[4]->move(glm::vec3(0, 0, -3));
		//this->drawObjects[4]->rotate(x_rot, glm::vec3(1, 0, 0), glm::vec3(0, 0, 0));
		//this->drawObjects[4]->rotate(y_rot, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
		//this->drawObjects[4]->changeColor(glm::vec3(0.0, 1.0, 0.0));
		//this->drawObjects[4]->changeSize(1.5);

		this->drawObjects[0]->move(glm::vec3(2, 0, 0));
		this->drawObjects[0]->changeColor(sphere1);
		this->drawObjects[0]->changeSize(sizes);

		this->drawObjects[1]->move(glm::vec3(0, 2, 0));
		this->drawObjects[1]->changeColor(sphere2);
		this->drawObjects[1]->changeSize(sizes);

		this->drawObjects[2]->move(glm::vec3(-2, 0, 0));
		this->drawObjects[2]->changeColor(sphere3);
		this->drawObjects[2]->changeSize(sizes);
			
		this->drawObjects[3]->move(glm::vec3(0, -2, 0));
		this->drawObjects[3]->changeColor(sphere4);
		this->drawObjects[3]->changeSize(sizes);

		this->drawObjects[4]->move(glm::vec3(4, 4, 0));
		this->drawObjects[4]->changeColor(glm::vec3(1, 1, 1));
		this->drawObjects[4]->changeSize(0.2);

		this->drawObjects[5]->move(glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));
		this->drawObjects[5]->changeColor(glm::vec3(1, 1, 1));
		this->drawObjects[5]->changeSize(0.2);

		for (int i = 0; i < this->drawObjects.size(); i++)
		{
			this->drawObjects[i]->moveLight(glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));
			this->drawObjects[i]->setPointLights(point);
			this->drawObjects[i]->setSpotLight(spot);
			this->drawObjects[i]->changeLightColor(lightColor);
			this->drawObjects[i]->draw();
		}

		ImGui::Begin("Spheres");
		ImGui::ColorEdit3("1", &sphere1.x);
		ImGui::ColorEdit3("2", &sphere2.x);
		ImGui::ColorEdit3("3", &sphere3.x);
		ImGui::ColorEdit3("4", &sphere4.x);
		ImGui::SliderFloat("Sizes", &sizes, 0, 5);
		ImGui::End();

		ImGui::Begin("Lights");
		ImGui::Checkbox("Point", &point);
		ImGui::Checkbox("Spot", &spot);
		ImGui::ColorEdit3("Color", &lightColor.x);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		this->window->swapBuffers();
		glfwPollEvents();

		tri_rot--;
		light_rot++;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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
