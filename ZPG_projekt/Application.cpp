#include "Application.h"

Application::Application(int windowWidth, int windowHeight)
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	Window::getInstance().init(windowWidth, windowHeight, "ZPG");

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
	Window::getInstance().initImgui();
	ImGui_ImplOpenGL3_Init("#version 330");

	float x_rot = 0, y_rot = 0, tri_rot = 0, light_rot = 0;
	float spotLight_intensity = 1, pointLight_intensity = 3, directLight_intensity = 0.5;

	glm::vec3 pointLightColor{ 1, 1, 1 }, spotLightColor{ 1, 1, 1 }, directionalLightColor{ 1, 1, 1 };
	float sizes = 1;
	float spotLightCutOff = 22.0;
	bool spot = true, point = true, direct = false;

	ShaderManager* shader_light_source = new ShaderManager(ShaderType::LIGHT_SOURCE);
	ShaderManager* shader_lambert = new ShaderManager(ShaderType::LAMBERT);
	ShaderManager* shader_phong = new ShaderManager(ShaderType::PHONG);
	ShaderManager* shader_blinn = new ShaderManager(ShaderType::BLINN);
	ShaderManager* shader_multiple_lights = new ShaderManager(ShaderType::MULTIPLE_LIGHTS);
	ShaderManager* shader_multiple_lights_tex = new ShaderManager(ShaderType::MULTIPLE_LIGHTS_TEX);
	ShaderManager* shader_skybox = new ShaderManager(ShaderType::SKYBOX);

	Model* sphere_model = new Model(Models::sphere, sizeof(Models::sphere), sizeof(Models::sphere) / (sizeof(float) * 6), ModelType::COLORED);
	DrawObject* sphere1 = new DrawObject(sphere_model, shader_multiple_lights, 1.f, glm::vec3(0.f, 7.f, 2.f), glm::vec3(1.f, 0.f, 1.f));
	DrawObject* sphere2 = new DrawObject(sphere_model, shader_lambert, 1.f, glm::vec3(2.f, 5.f, 2.f), glm::vec3(0.f, 1.f, 1.f));
	DrawObject* sphere3 = new DrawObject(sphere_model, shader_phong, 1.f, glm::vec3(0.f, 3.f, 2.f), glm::vec3(1.f, 0.f, 0.f));
	DrawObject* sphere4 = new DrawObject(sphere_model, shader_blinn, 1.f, glm::vec3(-2.f, 5.f, 2.f), glm::vec3(1.f, 1.f, 0.f));

	DrawObject* sphere_light_source = new DrawObject(sphere_model, shader_light_source, 0.3f, glm::vec3(2.f, 7.f, 2.f), glm::vec3(1.f, 1.f, 1.f));
	Light point1 = Light(LightType::POINT, glm::vec3(2.f, 7.f, 2.f));
	point1.registerObserver(*sphere_light_source);
	Light spot1 = Light(LightType::SPOT, glm::vec3(0.f));
	spot1.isFlashlight = true;
	spot1.ambientStrength = 0.03f;
	Camera::getInstance().registerObserver(spot1);

	Scene* scene1 = new Scene();
	scene1->addShader(shader_light_source);
	scene1->addShader(shader_lambert);
	scene1->addShader(shader_phong);
	scene1->addShader(shader_blinn);
	scene1->addShader(shader_multiple_lights);
	scene1->addShader(shader_multiple_lights_tex);
	scene1->setObjects(std::map<int, DrawObject*>{
		{ 0, sphere1 },
		{ 1, sphere2 },
		{ 2, sphere3 },
		{ 3, sphere4 },
		{ 4, sphere_light_source }
	});
	std::vector<Light*> lights1 = { &point1, &spot1 };
	scene1->setLights(lights1);

	addScene(scene1, 1);

	Scene* scene2 = new Scene();
	scene2->addShader(shader_light_source);
	scene2->addShader(shader_multiple_lights_tex);
	scene2->addShader(shader_skybox);

	Model* _skybox = new Model(Models::skycube, sizeof(Models::skycube), sizeof(Models::skycube) / (sizeof(Models::skycube[0]) * 3), ModelType::SKYBOX);
	DrawObject* skybox = new DrawObject(_skybox, shader_skybox, Textures::skybox::tenerife, 1);

	Model* _house_obj = new Model("Models/house.obj");
	Model* _terrain_obj = new Model("Models/teren.obj");
	Model* _tree_obj = new Model("Models/tree.obj");
	Model* _zombie_obj = new Model("Models/zombie.obj");
	scene2->addModel(sphere_model, "sphere");
	scene2->addModel(_house_obj, "house");
	scene2->addModel(_terrain_obj, "terrain");
	scene2->addModel(_tree_obj, "tree");
	scene2->addModel(_zombie_obj, "zombie");
	scene1->addModel(sphere_model, "sphere");
	scene1->addModel(_house_obj, "house");
	scene1->addModel(_terrain_obj, "terrain");
	scene1->addModel(_tree_obj, "tree");
	scene1->addModel(_zombie_obj, "zombie");

	DrawObject* house = new DrawObject(_house_obj, shader_multiple_lights_tex, "Textures/house.png", sizes, glm::vec3(0, 0, -6));
	house->rotate(90, glm::vec3(0.f, 1.f, 0.f));

	DrawObject* terrain = new DrawObject(_terrain_obj, shader_multiple_lights_tex, Textures::grass, sizes, glm::vec3(0.f));
	DrawObject* tree = new DrawObject(_tree_obj, shader_multiple_lights_tex, "Textures/tree_1.png", 0.75, glm::vec3(-6, 0, 0));
	DrawObject* zombie = new DrawObject(_zombie_obj, shader_multiple_lights_tex, "Textures/zombie.png", 1, glm::vec3(-2, 0, -1));
	
	Light point_1 = Light(POINT, glm::vec3(0.0));
	point_1.attenuation = 50;
	point_1.intensity = 5;

	Light spot_1 = Light(SPOT, glm::vec3(0.0));
	spot_1.isFlashlight = true;
	spot_1.ambientStrength = 0.03;
	Camera::getInstance().registerObserver(spot_1);

	Light dir_1 = Light(DIRECTIONAL, glm::vec3(0.0), glm::vec3(0.0, -1.0, 0.0));

	DrawObject* sun = new DrawObject(sphere_model, shader_light_source, 3, glm::vec3(0.0), glm::vec3(1.0, 1.0, 0.0));
	point_1.registerObserver(*sun);

	std::vector<Light*> lights2 = { &point_1, &spot_1, &dir_1 };
	std::map<int, DrawObject*> objects = { {0, skybox}, {1, terrain}, {2, house}, {3, zombie}, {4, tree}, {5, sun} };

	scene2->setLights(lights2);
	scene2->setObjects(objects);

	addScene(scene2, 2);

	while (!Window::getInstance().shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (this->currentScene == 1)
		{
			for (int i = 0; i < lights1.size(); i++)
			{
				if (lights1[i]->type == SPOT)
				{
					lights1[i]->state = spot ? ON : OFF;
					lights1[i]->cutOff = glm::cos(glm::radians(spotLightCutOff));
					lights1[i]->color = spotLightColor;
					lights1[i]->intensity = spotLight_intensity;
				}
				else if (lights1[i]->type == POINT)
				{
					lights1[i]->state = point ? ON : OFF;
					lights1[i]->color = pointLightColor;
					lights1[i]->intensity = pointLight_intensity;
				}
			}
		}
		else if (this->currentScene == 2)
		{
			point_1.position = glm::vec3(glm::cos(glm::radians(light_rot)) * 100, glm::sin(glm::radians(light_rot)) * 100, glm::cos(glm::radians(light_rot)) * 50);
			point_1.notifyObservers(LightMoved, &point_1);
			
			for (int i = 0; i < lights2.size(); i++)
			{
				if (lights2[i]->type == SPOT)
				{
					lights2[i]->state = spot ? ON : OFF;
					lights2[i]->cutOff = glm::cos(glm::radians(spotLightCutOff));
					lights2[i]->color = spotLightColor;
					lights2[i]->intensity = spotLight_intensity;
				}
				else if (lights2[i]->type == POINT)
				{
					lights2[i]->state = point ? ON : OFF;
					lights2[i]->color = pointLightColor;
					lights2[i]->intensity = pointLight_intensity;
				}
				else if (lights2[i]->type == DIRECTIONAL)
				{
					lights2[i]->state = direct ? ON : OFF;
					lights2[i]->color = directionalLightColor;
					lights2[i]->intensity = directLight_intensity;
				}
			}
		}

		this->getScene(this->currentScene)->render();

		ImGui::Begin("Point");
		ImGui::Checkbox("On", &point);
		if (ImGui::IsItemClicked())
		{
			point1.notifyObservers(LightChangedState, &point1);
			point_1.notifyObservers(LightChangedState, &point_1);
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
		ImGui::SliderInt("Scene", &this->currentScene, 1, this->scenes.size());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		Window::getInstance().swapBuffers();
		glfwPollEvents();

		tri_rot--;
		light_rot += 0.2;
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
