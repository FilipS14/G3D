#include "Mesh.h"

Mesh::Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, const vector<Texture>& textures)
{
    std::cout << "start mesh constructor " << std::endl;

    std::cout << "reserve vertices " << std::endl;
    numVertices = vertices.size();
    this->vertices.reset(new Vertex[numVertices]);

    std::cout << "start copy vertices " << std::endl;
    for (size_t i = 0; i < vertices.size(); ++i) {
        this->vertices.get()[i] = vertices[i];
    }

    std::cout << "reserve indices " << std::endl;
    numIndexes = indices.size();
    this->indices.reset(new unsigned int[numIndexes]);

    std::cout << "start copy indices " << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        this->indices.get()[i] = indices[i];
    }

    std::cout << "start copy textures " << std::endl;
    this->textures = textures;

    setupMesh();

    std::cout << "end mesh constructor " << std::endl;
}

Mesh::Mesh(unsigned int numVertices, std::shared_ptr <Vertex> vertices, unsigned int numIndexes, std::shared_ptr <unsigned int> indices, const vector<Texture>& textures)
{
    std::cout << "start mesh constructor. num vertice = " << numVertices << " num indexes " << numIndexes << std::endl;

    this->numVertices = numVertices;
    this->vertices = vertices;

    this->numIndexes = numIndexes;
    this->indices = indices;

    this->textures = textures;

    setupMesh();

    std::cout << "end mesh constructor " << std::endl;
}

void Mesh::Draw(Shader& shader)
{

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }


    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(numIndexes), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    std::cout << "start to setup mesh " << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), &vertices.get()[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndexes * sizeof(unsigned int), &indices.get()[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);

    std::cout << "end to setup mesh " << std::endl;
}


