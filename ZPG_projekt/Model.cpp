#include "Model.h"

Model::Model(const float vertices[], int size, int num_of_vertices, ModelType type)
{
	this->vertices = vertices;
	this->size = size;
	this->num_of_vertices = num_of_vertices;
	this->type = type;

	this->cols = (size / num_of_vertices) / sizeof(vertices[0]);

	createVBO();
	createVAO();
}

void Model::createVAO()
{
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)0);
	if (this->type == ModelType::COLORED)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)(sizeof(float) * 3));
	}
	else if (this->type == ModelType::TEXTURED)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)(sizeof(float) * 6));
	}
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
	if (getType() == ModelType::SKYBOX)
		glClear(GL_DEPTH_BUFFER_BIT);
}

ModelType Model::getType()
{
	return this->type;
}
