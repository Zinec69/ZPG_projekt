#include "Model.h"

Model::Model(const float vertices[], int size, int num_of_vertices)
{
	this->vertices = vertices;
	this->size = size;
	this->num_of_vertices = num_of_vertices;
	
	createVBO();
	createVAO();
}

void Model::createVAO()
{
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(3 * sizeof(float)));
}

void Model::createVBO()
{
	this->VBO = 0;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices, GL_STATIC_DRAW);
}

void Model::draw()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->num_of_vertices);
}
