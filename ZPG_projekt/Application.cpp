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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	this->window->initImgui();
	ImGui_ImplOpenGL3_Init("#version 330");

	float x_rot = 0, y_rot = 0, tri_rot = 0, light_rot = 0;
	float spotLight_intensity = 1, pointLight_intensity = 1, directLight_intensity = 1;

	glm::vec3 pointLightColor{ 1, 1, 1 }, spotLightColor{ 1, 1, 1 }, directionalLightColor{ 1, 1, 1 };
	float sizes = 1;
	float spotLightCutOff = 13.0;
	bool spot = true, point = true, direct = false;

	ShaderManager* shader_light_source = new ShaderManager(LIGHT_SOURCE);
	ShaderManager* shader_multiple_lights = new ShaderManager(MULTIPLE_LIGHTS);
	ShaderManager* shader_multiple_lights_tex = new ShaderManager(MULTIPLE_LIGHTS_TEX);
	ShaderManager* shader_skybox = new ShaderManager(SKYBOX);
	Camera::getInstance().registerObserver(*shader_light_source);
	Camera::getInstance().registerObserver(*shader_multiple_lights);
	Camera::getInstance().registerObserver(*shader_multiple_lights_tex);
	Camera::getInstance().registerObserver(*shader_skybox);

	Model* _skybox = new Model(Models::skycube, sizeof(Models::skycube), sizeof(Models::skycube) / (sizeof(Models::skycube[0]) * 3), CUBEMAP);
	DrawObject* skybox = new DrawObject(_skybox, shader_skybox, Textures::skybox::tenerife, 20);

	Model* _sphere = new Model(Models::sphere, sizeof(Models::sphere), sizeof(Models::sphere) / (sizeof(Models::sphere[0]) * 6), COLORED);
	Model* _plane = new Model(Models::plane_tex::plain, sizeof(Models::plane_tex::plain), sizeof(Models::plane_tex::plain) / (sizeof(Models::plane_tex::plain[0]) * 8), TEXTURED);

	DrawObject* plane1 = new DrawObject(_plane, shader_multiple_lights_tex, Textures::wooden_fence, sizes, glm::vec3(0, 2, -2));
	DrawObject* plane2 = new DrawObject(_plane, shader_multiple_lights_tex, Textures::wooden_floor, sizes, glm::vec3(2, 2, 0));
	DrawObject* plane3 = new DrawObject(_plane, shader_multiple_lights_tex, Textures::grass, sizes, glm::vec3(0, 2, 2));
	DrawObject* plane4 = new DrawObject(_plane, shader_multiple_lights_tex, Textures::ground, sizes, glm::vec3(-2, 2, 0));
	
	Light point_1 = Light(POINT, glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2));
	Light point_2 = Light(POINT, glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0));
	Light spot_1 = Light(SPOT, glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0), spotLight_intensity, 0.03, 0.5, glm::cos(glm::radians(13.0)), glm::cos(glm::radians(22.0)), true);
	Light dir_1 = Light(DIRECTIONAL, glm::vec3(0.0), glm::vec3(0.0, -1.0, 0.0));
	Camera::getInstance().registerObserver(spot_1);

	DrawObject* sphere5_ls = new DrawObject(_sphere, shader_light_source, 0.2, glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2), glm::vec3(1.0, 1.0, 1.0));
	DrawObject* sphere6_ls = new DrawObject(_sphere, shader_light_source, 0.2, glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0), glm::vec3(1.0, 1.0, 1.0));
	point_1.registerObserver(*sphere5_ls);
	point_2.registerObserver(*sphere6_ls);

	std::vector<Light*> lights = { &point_1, &point_2, &spot_1, &dir_1 };
	std::vector<DrawObject*> objects = { skybox, plane1, plane2, plane3, plane4, sphere5_ls, sphere6_ls };

	Scene* scene1 = new Scene();
	scene1->setLights(lights);
	scene1->setObjects(objects);

	addScene(scene1, 1);

	while (!this->window->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		point_1.position = glm::vec3(-glm::cos(glm::radians(light_rot)) * 4, 4, glm::sin(glm::radians(light_rot)) * 2);
		point_1.notifyObservers(LightMoved, &point_1);
		point_2.position = glm::vec3(glm::cos(glm::radians(light_rot)) * 4, glm::sin(glm::radians(light_rot)) * 4, 0);
		point_2.notifyObservers(LightMoved, &point_2);
		
		for (int i = 0; i < lights.size(); i++)
		{
			if (lights[i]->type == SPOT)
			{
				lights[i]->state = spot ? ON : OFF;
				lights[i]->cutOff = glm::cos(glm::radians(spotLightCutOff));
				lights[i]->outerCutOff = glm::cos(glm::radians(spotLightCutOff + 9));
				lights[i]->color = spotLightColor;
				lights[i]->intensity = spotLight_intensity;
			}
			else if (lights[i]->type == POINT)
			{
				lights[i]->state = point ? ON : OFF;
				lights[i]->color = pointLightColor;
				lights[i]->intensity = pointLight_intensity;
			}
			else if (lights[i]->type == DIRECTIONAL)
			{
				lights[i]->state = direct ? ON : OFF;
				lights[i]->color = directionalLightColor;
				lights[i]->intensity = directLight_intensity;
			}
		}

		this->getScene(this->currentScene)->render();

		ImGui::Begin("Point");
		ImGui::Checkbox("On", &point);
		if (ImGui::IsItemClicked())
		{
			point_1.notifyObservers(LightChangedState, &point_1);
			point_2.notifyObservers(LightChangedState, &point_2);
		}
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
		ImGui::Text(("Position: " + glm::to_string(Camera::getInstance().getPosition())).c_str());
		ImGui::Text(("Target: " + glm::to_string(Camera::getInstance().getTarget())).c_str());
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

void Application::changeCurrentScene(int ID)
{
	this->currentScene = ID;
}

void Application::addScene(Scene* scene, int ID)
{
	if (this->scenes.size() == 0)
		this->currentScene = ID;
	this->scenes.insert(std::pair<int, Scene*>(ID, scene));
}

Scene* Application::getScene(int ID)
{
	return this->scenes.at(ID);
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
