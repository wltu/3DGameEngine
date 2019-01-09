#pragma once
#include "Mesh.h"

class Projectiles {
	private:
		glm::vec3 direction;


	public:
		Projectiles(glm::vec3 direction) {
			this->direction = direction;
		}

		Projectiles() {
		}

		glm::vec3 getDir() {
			return this->direction;
		}
};