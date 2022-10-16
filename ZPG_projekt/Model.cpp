#include "Model.h"

Model::Model(const colorPoints vertexColor[], int size, int num_of_vertices)
{
	this->vertexColor = vertexColor;
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertexColor[0]), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertexColor[0]), (GLvoid*)(4 * sizeof(float)));
}

void Model::createVBO()
{
	this->VBO = 0;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->vertexColor, GL_STATIC_DRAW);
}

void Model::draw()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->num_of_vertices);
}
