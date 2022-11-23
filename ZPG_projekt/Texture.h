#pragma once

#include "GLincludes.h"
#include <vector>
#include <map>

class Texture
{
private:
	Texture() {};
	void loadTexture(std::string filepath);
	void loadCubemap(std::vector<std::string> filepaths);
	std::map<std::string, GLuint> textures = std::map<std::string, GLuint>();

public:
	static Texture& getInstance()
	{
		static Texture instance;
		return instance;
	}

	GLuint getTexture(std::string filepath);
	GLuint getTexture(std::vector<std::string> filepaths);

	Texture(Texture const&) = delete;
	void operator=(Texture const&) = delete;
};
