#pragma once

#include<glew.h>
#include<glfw3.h>

#include<vector>
#include "Vertex.h"


using namespace std;

class Primitive {
	private:
		vector<Vertex> verticies;
		vector<GLuint> indices;
	public:
		Primitive() {

		}

		virtual ~Primitive() {}

		// Function

		void set(const Vertex* vertices, 
			const unsigned numOfVertices, 
			const GLuint* indices, 
			const unsigned numOfIndices) {

			for (size_t i = 0; i < numOfVertices; i++) {
				this->verticies.push_back(vertices[i]);
			}

			for (size_t i = 0; i < numOfIndices; i++) {
				this->indices.push_back(indices[i]);
			}
		}

		inline Vertex* getVertices() { return this->verticies.data();}
		inline GLuint* getIndices() { return this->indices.data(); }
		inline const unsigned getNumOfVertices() { return this->verticies.size(); }
		inline const unsigned getNumOfIndices() { return this->indices.size(); }
};


class Cube : public Primitive {
public:
	Cube() : Primitive() {
		Vertex vertices[] =
		{
			// Position						// Color					// Textcoord				// Normal
			
			// Front
			glm::vec3(-0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			
			glm::vec3(-0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,0.5f,0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,0.f,1.f),

			// Left
			glm::vec3(-0.5f,0.5f,-0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(-1.f,0.f,0.f),

			glm::vec3(-0.5f,0.5f,-0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,0.5f,0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(-1.f,0.f,0.f),

			// Right
			glm::vec3(0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(1.f,0.f,0.f),

			glm::vec3(0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,0.5f,-0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(1.f,0.f,0.f),

			// Back
			glm::vec3(0.5f,0.5f,-0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,-1.f),

			glm::vec3(0.5f,0.5f,-0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(-0.5f,0.5f,-0.5f),	glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,0.f,-1.f),


			//// Top
			glm::vec3(0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(0.5f,0.5f,-0.5f),		glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(-0.5f,0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,1.f,0.f),

			glm::vec3(0.5f,0.5f,0.5f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(-0.5f,0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(-0.5f,0.5f,0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,1.f,0.f),

			// Bottom
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,-1.f,0.f),

			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,-1.f,0.f)

		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, numOfVertices, nullptr, 0);
	}
};

class Pyramid : public Primitive {
public:
	Pyramid() : Primitive() {
		Vertex vertices[] =
		{
			// Position						// Color					// Textcoord				// Normal
			
			// Front
			glm::vec3(0.f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,1.f),

			// Left
			glm::vec3(0.f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(-0.5f,-0.5f,0.5f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(-1.f,0.f,0.f),

			// Back
			glm::vec3(0.f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,-1.f),
		
			// Right
			glm::vec3(0.f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,-0.5f, 0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(1.f,0.f,0.f),

			// Bottom
			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(-0.5f,-0.5f,-0.5f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,-1.f,0.f),

			glm::vec3(-0.5f,-0.5f,0.5f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,-0.5f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.5f,-0.5f,0.5f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,-1.f,0.f)
		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, numOfVertices, nullptr, 0);
	}
};

class Quad : public Primitive {
public:
	Quad() : Primitive() {
		Vertex vertices[] =
		{
			// Position						// Color					// Textcoord				// Normal
			glm::vec3(-0.5f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.5f,0.f),		glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,0.5f,0.f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,0.f,1.f)
		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, numOfVertices, indices, numOfIndices);
	}
};

class Triangle : public Primitive {
public:
	Triangle() : Primitive() {
		Vertex vertices[] =
		{
			// Position						// Color					// Textcoord				// Normal
			glm::vec3(-0.5f,0.6f,0.f),		glm::vec3(1.f,0.f,0.f),		glm::vec2(0.0f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.6f,0.f),		glm::vec3(0.f,1.f,0.f),		glm::vec2(0.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.6f,0.f),		glm::vec3(0.f,0.f,1.f),		glm::vec2(1.0f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,0.6f,0.f),		glm::vec3(1.f,1.f,0.f),		glm::vec2(1.f,1.f),			glm::vec3(0.f,0.f,1.f)
		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2
		};
		unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, numOfVertices, indices, numOfIndices);
	}
};