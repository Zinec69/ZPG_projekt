#pragma once

#include "GLincludes.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

namespace Models {
	namespace plane {
		#include "Models/plain.h"
	}
	namespace plane_tex {
		#include "Models/plain_tex.h"
	}
	namespace bush {
		#include "Models/bushes.h"
	}
	#include "Models/sphere.h"
	#include "Models/suzi_flat.h"
	#include "Models/suzi_smooth.h"
	#include "Models/tree.h"
	#include "Models/gift.h"
	#include "Models/triangle.h"
	#include "Models/rectangle.h"
	#include "Models/skycube.h"
	namespace cube {
		#include "Models/cube.h"
	}
	namespace cube_tex {
		#include "Models/cube_tex.h"
	}
}

enum class ModelType
{
	COLORED,
	TEXTURED,
	CUBEMAP,
	SKYBOX,
};

struct Vertex
{
	float position[3];
	float normal[3];
	float texture[2];
	// float tangent[3];
};

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	const float* vertices = nullptr;
	Vertex* vertices_obj = nullptr;
	int size;
	int num_of_vertices;

	int cols;
	
	ModelType type;

	void createVBO();
	void createVAO();
	void loadObj(const std::string filename);
public:
	Model(const float vertices[], int size, int num_of_vertices, ModelType type);
	Model(const std::string obj_filename);
	void draw();
	ModelType getType();
};
