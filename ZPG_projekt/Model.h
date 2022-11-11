#pragma once

#include "GLincludes.h"

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

enum ModelType {
	COLORED,
	TEXTURED,
	CUBEMAP,
};

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	const float* vertices;
	int size;
	int num_of_vertices;

	int cols;
	
	ModelType type;

	void createVBO();
	void createVAO();
public:
	Model(const float vertices[], int size, int num_of_vertices, ModelType type);
	void draw();
	ModelType getType();
};
