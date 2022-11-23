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
}

void Model::loadObj(const std::string filename)
{
    //Assimp::Importer importer;
    //unsigned int importOptions = aiProcess_Triangulate
    //    | aiProcess_OptimizeMeshes              // slouèení malých plošek
    //    | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
    //    | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
    //    | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    ////aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    //const aiScene* scene = importer.ReadFile(filename, importOptions);

    //if (scene) //pokud bylo nacteni uspesne
    //{
    //    printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
    //    printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

    //    for (unsigned int i = 0; i < scene->mNumMaterials; i++)                 //Materials
    //    {
    //        const aiMaterial* mat = scene->mMaterials[i];

    //        aiString name;
    //        mat->Get(AI_MATKEY_NAME, name);
    //        printf("Material [%d] name %s\n", i, name.C_Str());

    //        aiColor4D d;

    //        glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    //        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
    //            diffuse = glm::vec4(d.r, d.g, d.b, d.a);

    //    }

    //    for (unsigned int i = 0; i < scene->mNumMeshes; i++)                    //Objects
    //    {
    //        aiMesh* mesh = scene->mMeshes[i];

    //        _vertices = new Vertex[mesh->mNumVertices];
    //        std::memset(_vertices, 0, sizeof(Vertex) * mesh->mNumVertices);

    //        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    //        {
    //            if (mesh->HasPositions())
    //            {
    //                _vertices[i].position[0] = mesh->mVertices[i].x;
    //                _vertices[i].position[1] = mesh->mVertices[i].y;
    //                _vertices[i].position[2] = mesh->mVertices[i].z;
    //            }
    //            if (mesh->HasNormals())
    //            {
    //                _vertices[i].normal[0] = mesh->mNormals[i].x;
    //                _vertices[i].normal[1] = mesh->mNormals[i].y;
    //                _vertices[i].normal[2] = mesh->mNormals[i].z;
    //            }
    //            if (mesh->HasTextureCoords(0))
    //            {
    //                _vertices[i].texture[0] = mesh->mTextureCoords[0][i].x;
    //                _vertices[i].texture[1] = mesh->mTextureCoords[0][i].y;
    //            }
    //            if (mesh->HasTangentsAndBitangents())
    //            {
    //                _vertices[i].tangent[0] = mesh->mTangents[i].x;
    //                _vertices[i].tangent[1] = mesh->mTangents[i].y;
    //                _vertices[i].tangent[2] = mesh->mTangents[i].z;
    //            }

    //        }

    //        unsigned int* pIndices = nullptr;

    //        if (mesh->HasFaces())
    //        {

    //            pIndices = new unsigned int[mesh->mNumFaces * 3];
    //            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    //            {
    //                pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
    //                pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
    //                pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
    //            }
    //        }
    //            
    //        glGenVertexArrays(1, &this->VAO);
    //        glGenBuffers(1, &this->VBO);
    //        glGenBuffers(1, &this->IBO);

    //        glBindVertexArray(this->VAO);
    //        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    //        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, this->_vertices, GL_STATIC_DRAW);

    //        glEnableVertexAttribArray(0);
    //        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
    //        glEnableVertexAttribArray(1);
    //        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    //        glEnableVertexAttribArray(2);
    //        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
    //        glEnableVertexAttribArray(3);
    //        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //        glBindVertexArray(this->VAO);

    //        GLuint err = glGetError();
    //        if (err != GL_NO_ERROR)
    //        {
    //            std::cout << "GL ERROR: " << err << std::endl; return;
    //        }
    //        this->num_of_vertices = mesh->mNumFaces * 3;

    //        delete[] pIndices;
    //    }
    //}
    //else
    //    printf("Error during parsing mesh from %s : %s\n", filename.c_str(), importer.GetErrorString());

    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
    
    const aiScene* scene = importer.ReadFile(filename, importOptions);
    
    std::vector<float> data;
    
    if (scene)
    {
        aiMesh* mesh = scene->mMeshes[0];
        this->num_of_vertices = mesh->mNumFaces * 3;

        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
            }
        }
    }

    //Vertex Array Object (VAO)
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
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
