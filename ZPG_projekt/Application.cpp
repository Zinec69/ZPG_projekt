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

	float x_rot = 0, y_rot = 0, tri_rot = 0, light_rot = 0;
	float spotLight_intensity = 1, pointLight_intensity = 1, directLight_intensity = 1;

	glm::vec3 sphere1{ 1, 0, 0 }, sphere2{ 0, 1, 0 }, sphere3{ 0, 0, 1 }, sphere4{ 1, 0, 1 };
	glm::vec3 pointLightColor{ 1, 1, 1 }, spotLightColor{ 1, 1, 1 }, directionalLightColor{ 1, 1, 1 };
	float sizes = 1;
	float spotLightCutOff = 13.0;
	bool spot = true, point = true, direct = true;

	ShaderManager* shader_light_source = new ShaderManager(LIGHT_SOURCE);
	ShaderManager* shader_multiple_lights = new ShaderManager(MULTIPLE_LIGHTS);

	Camera::getInstance().registerObserver(*shader_light_source);
	Camera::getInstance().registerObserver(*shader_multiple_lights);

	Model* model = new Model(sphere, sizeof(sphere), sizeof(sphere) / (sizeof(sphere[0]) * 6));
	DrawObject* drawObject = nullptr;

	drawObject = new DrawObject(model, shader_multiple_lights, 1, sphere1, glm::vec3(2, 0, 0));
	this->drawObjects.push_back(drawObject);

	drawObject = new DrawObject(model, shader_multiple_lights, 1, sphere2, glm::vec3(0, 2, 0));
	this->drawObjects.push_back(drawObject);

	drawObject = new DrawObject(model, shader_multiple_lights, 1, sphere3, glm::vec3(-2, 0, 0));
	this->drawObjects.push_back(drawObject);

	drawObject = new DrawObject(model, shader_multiple_lights, 1, sphere4, glm::vec3(0, -2, 0));
	this->drawObjects.push_back(drawObject);

	drawObject = new DrawObject(model, shader_light_source, 0.2, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2));
	this->drawObjects.push_back(drawObject);

	drawObject = new DrawObject(model, shader_light_source, 0.2, glm::vec3(1.0, 1.0, 1.0), glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));
	this->drawObjects.push_back(drawObject);

	Light point_1 = Light(POINT, glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2));
	Light point_2 = Light(POINT, glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));
	Light spot_1 = Light(SPOT, glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0), spotLight_intensity, 0.03, 0.5, glm::cos(glm::radians(13.0)), glm::cos(glm::radians(22.0)), true);
	Camera::getInstance().registerObserver(spot_1);
	Light spot_2 = Light(SPOT, glm::vec3(0.0, 5.0, 1.0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(1.0), spotLight_intensity, 0.03);
	Light dir_1 = Light(DIRECTIONAL, glm::vec3(0.0), glm::vec3(0.0, -1.0, 0.0));

	std::vector<Light*> lights = { &point_1, &point_2, &spot_1, &spot_2, &dir_1 };
	
	for (int i = 0; i < this->drawObjects.size(); i++)
		this->drawObjects[i]->setLights(lights);

	while (!this->window->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (Keyboard::getInstance().key_pressed == GLFW_KEY_LEFT) y_rot += 1;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_RIGHT) y_rot -= 1;

		if (Keyboard::getInstance().key_pressed == GLFW_KEY_UP) x_rot += 1;
		if (Keyboard::getInstance().key_pressed == GLFW_KEY_DOWN) x_rot -= 1;

		this->drawObjects[0]->changeColor(sphere1);
		this->drawObjects[0]->changeSize(sizes);

		this->drawObjects[1]->changeColor(sphere2);
		this->drawObjects[1]->changeSize(sizes);

		this->drawObjects[2]->changeColor(sphere3);
		this->drawObjects[2]->changeSize(sizes);
			
		this->drawObjects[3]->changeColor(sphere4);
		this->drawObjects[3]->changeSize(sizes);

		this->drawObjects[4]->move(glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2));

		this->drawObjects[5]->move(glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));

		point_1.position = glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2);
		point_2.position = glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0);
		
		for (Light* light : lights)
		{
			if (light->type == SPOT)
			{
				light->state = spot ? ON : OFF;
				light->cutOff = glm::cos(glm::radians(spotLightCutOff));
				light->outerCutOff = glm::cos(glm::radians(spotLightCutOff + 9));
				light->color = spotLightColor;
				light->intensity = spotLight_intensity;
			}
			else if (light->type == POINT)
			{
				light->state = point ? ON : OFF;
				light->color = pointLightColor;
				light->intensity = pointLight_intensity;
			}
			else if (light->type == DIRECTIONAL)
			{
				light->state = direct ? ON : OFF;
				light->color = directionalLightColor;
				light->intensity = directLight_intensity;
			}
		}
		
		Camera::getInstance().move();

		for (int i = 0; i < this->drawObjects.size(); i++)
		{
			if (this->drawObjects[i]->isLightSource() && !point)
				continue;
			this->drawObjects[i]->draw();
		}

		ImGui::Begin("Spheres");
		ImGui::ColorEdit3("1", &sphere1.x);
		ImGui::ColorEdit3("2", &sphere2.x);
		ImGui::ColorEdit3("3", &sphere3.x);
		ImGui::ColorEdit3("4", &sphere4.x);
		ImGui::SliderFloat("Sizes", &sizes, 0, 5);
		ImGui::End();

		ImGui::Begin("Point");
		ImGui::Checkbox("On", &point);
		ImGui::SliderFloat("Intensity", &pointLight_intensity, 0, 10);
		ImGui::ColorEdit3("Color", &pointLightColor.x);
		ImGui::End();

		ImGui::Begin("Spot");
		ImGui::Checkbox("On", &spot);
		ImGui::SliderFloat("Radius", &spotLightCutOff, 0, 45);
		ImGui::SliderFloat("Intensity", &spotLight_intensity, 0, 10);
		ImGui::ColorEdit3("Color", &spotLightColor.x);
		ImGui::End();

		ImGui::Begin("Directional");
		ImGui::Checkbox("On", &direct);
		ImGui::SliderFloat("Intensity", &directLight_intensity, 0, 10);
		ImGui::ColorEdit3("Color", &directionalLightColor.x);
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text(("Position: " + to_string(Camera::getInstance().getPosition().x) + ", " + to_string(Camera::getInstance().getPosition().y) + ", " + to_string(Camera::getInstance().getPosition().z)).c_str());
		ImGui::Text(("Target: " + to_string(Camera::getInstance().getTarget().x) + ", " + to_string(Camera::getInstance().getTarget().y) + ", " + to_string(Camera::getInstance().getTarget().z)).c_str());
		ImGui::Text(("FOV: " + to_string(Camera::getInstance().getFOV())).c_str());
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
