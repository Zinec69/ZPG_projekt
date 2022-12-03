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

Model::Model(const std::string obj_filename)
{
    this->type = ModelType::TEXTURED;
    loadObj(obj_filename);
    createVBO();
    createVAO();
}

void Model::loadObj(const std::string filename)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
    
    const aiScene* scene = importer.ReadFile(filename, importOptions);
    
    if (scene)
    {
        aiMesh* mesh = scene->mMeshes[0];
        this->num_of_vertices = mesh->mNumFaces * 3;
        float* _vertices = new float[this->num_of_vertices * 8];
        int index = 0;

        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                _vertices[index++] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].x;
                _vertices[index++] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].y;
                _vertices[index++] = mesh->mVertices[mesh->mFaces[i].mIndices[j]].z;
                _vertices[index++] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].x;
                _vertices[index++] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].y;
                _vertices[index++] = mesh->mNormals[mesh->mFaces[i].mIndices[j]].z;
                _vertices[index++] = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x;
                _vertices[index++] = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y;
            }
        }

        this->vertices = _vertices;
        this->cols = 8;
        this->size = this->num_of_vertices * this->cols * sizeof(float);
    }
}

void Model::createVAO()
{
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)0);
	if (this->cols > 3)
	{
	    glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)(sizeof(float) * 3));
	}
	if (this->cols > 6)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * this->cols, (GLvoid*)(sizeof(float) * 6));
	}
}

void Model::createVBO()
{
	this->VBO = 0;
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices, GL_STATIC_DRAW);
}

void Model::draw()
{
    //if (this->_vertices == nullptr)
    //{
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, this->num_of_vertices);
        if (getType() == ModelType::SKYBOX)
            glClear(GL_DEPTH_BUFFER_BIT);
    //}
    //else
    //{
    //    glBindVertexArray(this->IBO);
    //    glDrawElements(GL_TRIANGLES, this->num_of_vertices, GL_FLOAT, NULL);
    //}
}

ModelType Model::getType()
{
	return this->type;
}
