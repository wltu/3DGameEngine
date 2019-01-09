#pragma once

#include<iostream>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc\matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD = 1, RIGHT = 2, LEFT = 3 };

class Camera {
	private:
		glm::mat4 ViewMatrix;

		GLfloat movementSpeed;
		GLfloat sensitivity;


		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 up;


		glm::vec3 worldUP;

		GLfloat pitch;
		GLfloat yaw;
		GLfloat roll;

		void updateCameraVectors() {
			this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
			this->front.y = sin(glm::radians(this->pitch));
			this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));


			this->front = glm::normalize(this->front);
			this->right = glm::normalize(glm::cross(this->front, this->worldUP));
			this->up = glm::normalize(glm::cross(this->right, this->front));
		}

	public:

		Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp){
			this->ViewMatrix = glm::mat4(1.f);

			this->movementSpeed = 3.f;
			this->sensitivity = 6.f;

			this->worldUP = worldUp;
			this->position = position;
			this->right = glm::vec3(0.f);
			this->up = worldUp;

			this->pitch = 0.f;
			this->yaw = -90.f;
			this->roll = 0.f;

			this->updateCameraVectors();
		}

		~Camera(){}

		// Accessors

		const glm::mat4 getViewMatrix() {
			this->updateCameraVectors();
			
			this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

			return this->ViewMatrix;
		}

		const glm::vec3 getPosition() const {
			return this->position;
		}

		const glm::vec3 getFront() const {
			return this->front;
		}

		// Functions
		void move(const float& dt, const int direction) {
			switch (direction) {
			case FORWARD:
				this->position += glm::vec3(glm::vec3(this->front.x, 0.f, this->front.z)) * this->movementSpeed * dt;
				break;
			case BACKWARD:
				this->position -= glm::vec3(glm::vec3(this->front.x, 0.f, this->front.z))  * this->movementSpeed * dt;
				break;
			case RIGHT:
				this->position += this->right * this->movementSpeed * dt;
				break;
			case LEFT:
				this->position -= this->right * this->movementSpeed * dt;
				break;
			default:
				break;
			}
		}

		void updateMouseInput(const float& dt, const double& offsetX, const double offsetY) {
			// Update pitch yaw and roll
			this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
			this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

			if (this->pitch > 80.f)
				this->pitch = 80.f;
			else if (this->pitch < -80.f)
				this->pitch = -80.f;

			if (this->yaw > 360.f || this->yaw < -360.f)
				this->yaw = 0.f;
		}

		void updateInput(const float& dt, const int direction, const double& offsetX, const double offsetY) {
			this->updateMouseInput(dt, offsetX, offsetY);
		}
};