#pragma once
#include "libs.h"
#include "Camera.h"
#include "Projectiles.h"

// Enumerations
enum shader_enum {SHADER_CORE_PROGRAM = 0};
enum texture_enum { TEX0 = 0, TEX1 = 1, TEX2 = 2, TEX3 = 3};
enum material_enum { MAT_0 = 0 };
enum mesh_enum { MESH_QUAD = 0 };


class Game
{
	private:
		// Window
		GLFWwindow* window;


		// Delta Time
		float dt;
		float curTime;
		float lastTime;

		// Mouse Inputs
		double lastMouseX;
		double lastMouseY;
		double mouseX;
		double mouseY;
		double mouseOffsetX;
		double mouseOffsetY;
		bool firstMouse;

		Camera camera;

		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;
		int framebufferWidth;
		int framebufferHeight;

		// OpenGL Context
		const int GL_VERSION_MAJOR;
		const int GL_VERSION_MINOR;

		// Matrices
		glm::mat4 ViewMatrix;
		glm::vec3 camPosition;
		glm::vec3 worldUP;
		glm::vec3 camFront;

		float fov;
		float nearPlane;
		float farPlane;
		glm::mat4 ProjectionMatrix;

		// Shaders
		vector<Shader*> shaders;

		// Textures
		vector<Texture*> textures;

		// Materials
		vector<Material*> materials;

		// Model
		vector<Model*> models;

		// Lights
		vector<glm::vec3*> lights;

		// Game Stuff

		// Projectile
		vector<Projectiles*> projectile;
		float PROJECTILE_SPEED;

		// Mouse click
		bool mouseClicked;


		// Private Functions
		void initGLFW();
		void initWindow(const char* title, bool resizable);
		void initGLEW();
		void initOpenGLOptions();
		void initMatrices();
		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initLights();
		void initUniforms();


		void updateUniforms();
	public:
		Game(
			const char* title,
			const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
			const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
			bool resizable
		);
		virtual ~Game();

		// Accessors
		int getWindowShouldClose() {
			return glfwWindowShouldClose(this->window);
		}

		// Modifiers
		void setWindowShouldClose();

		// Functions

		// Static Variables


		// Functions
		void updateDt();
		void updateMouseInput();
		void updateKeyboardInput();
		void updateInput();
		void update();
		void render();

		// Static functions
		static void framebufferResizeCallback(GLFWwindow* window, int fbW, int fbH);
		//static void updateInput(GLFWwindow *window);
		// void updateInput(GLFWwindow *window, Mesh &mesh);
};

