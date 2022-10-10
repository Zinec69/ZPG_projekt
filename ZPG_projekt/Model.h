#pragma once

#include "GLincludes.h"

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	const colorPoints* vertexColor;
	int size;
	int num_of_vertices;

	void createVBO();
	void createVAO();
public:
	Model(const colorPoints vertexColor[], int size, int num_of_vertices);
	void draw();
};
