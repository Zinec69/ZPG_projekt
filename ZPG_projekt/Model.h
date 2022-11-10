#pragma once

#include "GLincludes.h"
namespace plane {
	#include "Models/plain.h"
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
#include "Models/cube.h"
#include "Models/rectangle.h"
#include "Models/plain_tex.h"
#include "Models/skycube.h"

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	const float* vertices;
	int size;
	int num_of_vertices;

	void createVBO();
	void createVAO();
public:
	Model(const float vertices[], int size, int num_of_vertices);
	void draw();
};
