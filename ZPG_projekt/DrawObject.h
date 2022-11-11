#pragma once

#include "GLincludes.h"
#include "Model.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Light.h"
#include "Observer.h"

namespace Textures {
	constexpr auto grass = "../ZPG_projekt/Textures/grass.png";
	constexpr auto wooden_fence = "../ZPG_projekt/Textures/wooden_fence.png";
	constexpr auto wooden_floor = "../ZPG_projekt/Textures/wooden_floor.png";
	constexpr auto ground = "../ZPG_projekt/Textures/ground.jpg";
	namespace skybox {
		static const char* meadow[6] = {"../ZPG_projekt/Textures/cubemap/skybox_meadow/posx.jpg", "../ZPG_projekt/Textures/cubemap/skybox_meadow/negx.jpg",
													"../ZPG_projekt/Textures/cubemap/skybox_meadow/posy.jpg", "../ZPG_projekt/Textures/cubemap/skybox_meadow/negy.jpg",
													"../ZPG_projekt/Textures/cubemap/skybox_meadow/posz.jpg", "../ZPG_projekt/Textures/cubemap/skybox_meadow/negz.jpg" };
		static const char* tenerife[6] = { "../ZPG_projekt/Textures/cubemap/Tenerife/posx.jpg", "../ZPG_projekt/Textures/cubemap/Tenerife/negx.jpg",
													"../ZPG_projekt/Textures/cubemap/Tenerife/posy.jpg", "../ZPG_projekt/Textures/cubemap/Tenerife/negy.jpg",
													"../ZPG_projekt/Textures/cubemap/Tenerife/posz.jpg", "../ZPG_projekt/Textures/cubemap/Tenerife/negz.jpg" };
		static const char* sea[6] = { "../ZPG_projekt/Textures/cubemap/sea/posx.jpg", "../ZPG_projekt/Textures/cubemap/sea/negx.jpg",
													"../ZPG_projekt/Textures/cubemap/sea/posy.jpg", "../ZPG_projekt/Textures/cubemap/sea/negy.jpg",
													"../ZPG_projekt/Textures/cubemap/sea/posz.jpg", "../ZPG_projekt/Textures/cubemap/sea/negz.jpg" };
		static const char* lake[6] = { "../ZPG_projekt/Textures/cubemap/lake/posx.jpg", "../ZPG_projekt/Textures/cubemap/lake/negx.jpg",
													"../ZPG_projekt/Textures/cubemap/lake/posy.jpg", "../ZPG_projekt/Textures/cubemap/lake/negy.jpg",
													"../ZPG_projekt/Textures/cubemap/lake/posz.jpg", "../ZPG_projekt/Textures/cubemap/lake/negz.jpg" };
		//constexpr auto canyon = "../ZPG_projekt/Textures/cubemap/canyon.jpg";
		//constexpr auto night_sky = "../ZPG_projekt/Textures/cubemap/night_sky.png";
	}
}

struct Material
{
	float shininess = 32;
};

class DrawObject : public Observer
{
private:
	glm::mat4 object{ 1.0 };
	glm::vec3 color{ 0.0, 1.0, 0.1 };
	float scale = 1;

	bool active = true;

	GLuint texture;

	Material material;
	Model* model;
	ShaderManager* shader;
public:
	DrawObject(Model* model, ShaderManager* shader, float scale = 1, glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(0.0, 1.0, 0.1));
	DrawObject(Model* model, ShaderManager* shader, const char* texture_filename, float scale = 1, glm::vec3 position = glm::vec3(0.0));
	DrawObject(Model* model, ShaderManager* shader, const char* texture_filenames[6], float scale = 1);
	void draw(std::vector<Light*> lights);
	void rotate(float angle, glm::vec3 axis);
	void rotate(float angle, glm::vec3 axis, glm::vec3 point);
	void resize(glm::vec3 multiplier);
	void move(glm::vec3 point);
	void changeColor(glm::vec3 color);
	void changeSize(float size);
	void changeShininess(int shininess);
	GLuint loadTexture(const char* filename);
	GLuint loadCubemap(const char* filenames[6]);
	GLuint loadCubemap(const char* filename);
	void applyTextures();
	bool isLightSource() const;
	bool isCubeMap() const;
	bool isActive() const;

	void onSubjectNotification(EventType eventType, void* object);
};
