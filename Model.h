#pragma once

#include"Mesh.h"
#include"Texture.h"
#include"Shader.h"
#include"Material.h"
#include "Projectiles.h"

class Model
{
private:
	Material * material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	bool projectile;
	vector<glm::vec3> constMovement;

	void updateUniforms()
	{
	}

public:
	Model(
		glm::vec3 position,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec,
		std::vector<Mesh*>& meshes
	)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		this->projectile = false;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& m: this->meshes)
		{
			m->move(this->position);
			//i->setOrigin(this->position);
		}
	}

	~Model()
	{
		for (auto*& i : this->meshes)
			delete i;
	}


	void setProjectile() {
		this->projectile = true;
	}

	void setMovement(glm::vec3 direction) {
		this->constMovement.push_back(direction);
	}

	vector<Mesh*>* getMeshes() {
		return &this->meshes;
	}

	//Functions

	void rotate(const glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
			i->rotate(rotation);
	}

	void update()
	{

	}

	void render(Shader* shader)
	{
		//Update the uniforms
		this->updateUniforms();

		//Update uniforms
		this->material->sendToShader(*shader);

		//Use a program
		shader->use();

		//Activate texture
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		//Draw
		int i = 0;
		glm::vec3 meshPos;

		for (auto& m : this->meshes) {
			if (this->projectile && i < constMovement.size()) {
				meshPos = m->getPosition();

				m->move(constMovement[i++]);

				if (meshPos.x > 10.f || meshPos.x < -10.f ||
					meshPos.y > 10.f || meshPos.y < -10.f ||
					meshPos.z > 10.f || meshPos.z < -10.f) {
					constMovement[i - 1] = glm::vec3(0.f);
				}
			}

			m->render(shader);
		}
	}
};