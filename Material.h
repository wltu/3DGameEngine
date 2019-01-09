#pragma once
#include "Shader.h"

class Material {
	public:
		Material(
				glm::vec3 ambient,
				glm::vec3 diffuse,
				glm::vec3 specular,
				GLint diffuseTexture,
				GLint specularTexture) {
			
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
			this->diffuseTexture = diffuseTexture;
			this->specularTexture = specularTexture;
		}

		~Material() {
		}

		void sendToShader(Shader& program) {
			program.setVec3f(this->ambient, "material.ambient");
			program.setVec3f(this->diffuse, "material.diffuse");
			program.setVec3f(this->specular, "material.specular");
			program.set1i(this->diffuseTexture, "material.diffuseTexture");
			program.set1i(this->specularTexture, "material.specularTexture");
		}
		
	private:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		GLint diffuseTexture;
		GLint specularTexture;
};