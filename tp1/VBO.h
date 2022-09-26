#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<../glm/glm.hpp>
#include<glad/glad.h>
#include<vector>
#include <detail/type_vec.hpp>
//using namespace glm;


// Structure to standardize the vertices used in the meshes
//struct Vertex
//{
//	std::vector<glm::vec3> position;
//	std::vector<glm::vec3> normal;
//	std::vector<glm::vec3> color;
//	std::vector<glm::vec3> texUV;
//};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};


class VBO
{
public:

	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif