#include "Texture.h"

void Texture::loadTexture(std::string filepath)
{
	GLuint id = SOIL_load_OGL_texture(filepath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (id == 0)
	{
		std::cout << "An error occurred while loading texture image\n";
		exit(EXIT_FAILURE);
	}
	textures.insert(std::pair<std::string, GLuint>(filepath, id));
}

void Texture::loadCubemap(std::vector<std::string> filepaths)
{
	GLuint id = SOIL_load_OGL_cubemap(filepaths.at(0).c_str(), filepaths.at(1).c_str(), filepaths.at(2).c_str(), filepaths.at(3).c_str(), filepaths.at(4).c_str(), filepaths.at(5).c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (id == 0)
	{
		std::cout << "An error occurred while loading multi-file cubemap texture\n";
		exit(EXIT_FAILURE);
	}
	textures.insert(std::pair<std::string, GLuint>(filepaths.at(0), id));
}

GLuint Texture::getTexture(std::string filepath)
{
	GLuint id = 0;

	if (textures.find(filepath) == textures.end())
		loadTexture(filepath);
	
	id = textures.at(filepath);

	return id;
}

GLuint Texture::getTexture(std::vector<std::string> filepaths)
{
	GLuint id = 0;

	if (textures.find(filepaths.at(0)) == textures.end())
		loadCubemap(filepaths);
	
	id = textures.at(filepaths.at(0));

	return id;
}
