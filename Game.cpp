#include "Game.h"

// Private Functions
void Game::initGLFW(){
	if (!glfwInit()) {
		cout << "ERROR::GLFW_INIT_FAILED" << endl;
		glfwTerminate();
	}
}

void Game::initWindow(const char* title, bool resizable){

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (!this->window) {
		cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << endl;
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::framebufferResizeCallback);
	// glViewport(0,0, framebufferWidth, framebufferWidth);

	// Make window
	glfwMakeContextCurrent(this->window);

}

void Game::initGLEW(){
	// Initial GLEW
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "ERROR:MAIN.CPP::GLEW_INIT_FAILED" << endl;
		glfwTerminate();
	}
}

void Game::initOpenGLOptions(){
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW); // Right-hand rule -> front face

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Inputs
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices(){
	// Init Matrix Variables
	this->ViewMatrix = glm::mat4(1.f);
	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUP = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUP);


	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(this->framebufferWidth / this->framebufferHeight), this->nearPlane, this->farPlane);
}

void Game::initShaders(){
	// Shader
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, (char*)"vertex_core.glsl", (char*)"fragment_core.glsl", (char*)""));
}

void Game::initTextures(){
	// Textures
	this->textures.push_back(new Texture("Images/pusheen.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/pusheen_specular.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/container_specular.png", GL_TEXTURE_2D));
}

void Game::initMaterials(){
	// Material
	materials.push_back(
		new Material(
			glm::vec3(0.1f), 
			glm::vec3(1.f), 
			glm::vec3(1.f), 
			0, 1));
}

//void Game::initMeshes()
//{
//	/*Mesh mesh(vertices,
//		numOfVertices,
//		indices,
//		numOfIndices,
//		glm::vec3(0.f),
//		glm::vec3(0.f),
//		glm::vec3(2.f));*/
//
//	
//}

void Game::initModels() {
	vector<Mesh*> meshes;

	// Projectiles
	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[2],
		this->textures[3],
		meshes
	)
	);

	models[0]->setProjectile();

	// Object
	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f, 0.f, .0f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	meshes.push_back(
		new Mesh(
			&Pyramid(),
			glm::vec3(1.f, -0.5f, -2.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(-2.f, 2.f, -2.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(2.f)
		)
	);

	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[2],
		this->textures[3],
		meshes
	)
	);

	for (auto*& m: meshes) {
		delete m;
	}
	meshes.clear();

	// Wall
	for (int i = 0; i < 10; i++) {
		meshes.push_back(
			new Mesh(
				&Quad(),
				glm::vec3(-9.f + float(i) * 2, 0.f, -10.f),
				glm::vec3(0.f),
				glm::vec3(0.f),
				glm::vec3(2.f)
			)
		);
	}
	


	for (int i = 0; i < 4; i++) {
		this->models.push_back(new Model(
			glm::vec3(0.f),
			this->materials[0],
			this->textures[2],
			this->textures[3],
			meshes
		)
		);

		for (auto& m : meshes) {
			m->rotate(glm::vec3(0.f, 90.f, 0.f));
		}
	}


	for (auto*& m : meshes) {
		delete m;
	}
	meshes.clear();
}

void Game::initLights(){
	// Lights
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms(){
	// Initial Uniform
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
}

void Game::updateUniforms(){
	// Update View matrix
	this->ViewMatrix = this->camera.getViewMatrix();
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "camPosition");

	// Update framebuffer size and projection 
	this->ProjectionMatrix = glm::mat4(1.f);

	glfwGetFramebufferSize(window, &this->framebufferWidth, &this->framebufferHeight);
	this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(this->framebufferWidth / this->framebufferHeight), this->nearPlane, this->farPlane);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable)
	
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 1.f),glm::vec3(0.f,0.f,1.f), glm::vec3(0.f, 1.f, 0.f))
{
	// Init Variables
	this->window = nullptr;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	// Delta Time
	this->dt = 0.0f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	// Mouse Inputs
	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;

	this->mouseClicked = false;
	this->PROJECTILE_SPEED = 0.1f;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	// this->initMeshes();
	this->initModels();
	this->initLights();
	this->initUniforms();
}


Game::~Game(){

	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++){
		delete this->shaders[i];
	}
	for (size_t i = 0; i < this->textures.size(); i++) {
		delete this->textures[i];
	}
	for (size_t i = 0; i < this->materials.size(); i++) {
		delete this->materials[i];
	}
	/*for (size_t i = 0; i < this->meshes.size(); i++) {
		delete this->meshes[i];
	}*/

	for (auto*& m : this->models) {
		delete m;
	}

	for (size_t i = 0; i < this->lights.size(); i++) {
		delete this->lights[i];
	}
}

void Game::setWindowShouldClose(){
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::updateDt() {
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseInput() {
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);


	if (this->firstMouse) {
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	// Offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	// Mouse click
	if (!this->mouseClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		vector<Mesh*> meshes;

		this->projectile.push_back(new Projectiles());

		this->models[0]->getMeshes()->push_back(
			new Mesh(
				&Cube(),
				this->camera.getPosition(),
				glm::vec3(0.f),
				this->camera.getFront(),
				glm::vec3(1.f)
			)
		);

		this->models[0]->setMovement(PROJECTILE_SPEED * this->camera.getFront());

		/*meshes.push_back(
			new Mesh(
				&Cube(),
				this->camera.getPosition(),
				glm::vec3(0.f),
				this->camera.getFront(),
				glm::vec3(1.f)
			)
		);
		
		this->models.push_back(
			new Model(
			glm::vec3(0.f),
			this->materials[0],
			this->textures[2],
			this->textures[3],
			meshes)
		);*/

		this->mouseClicked = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		this->mouseClicked = false;
	}
}
void Game::updateKeyboardInput() {
	// Exit
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	// Movement
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera.move(this->dt, RIGHT);
	}

	//if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	//	this->camPosition.y += 0.01f;
	//}
	//if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS) {
	//	this->camPosition.y -= 0.01f;
	//}


	this->lights[0]->x = this->camera.getPosition().x;
	this->lights[0]->y = this->camera.getPosition().y;
	this->lights[0]->z = this->camera.getPosition().z;

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
}

void Game::updateInput() {
	glfwPollEvents();
	this->updateMouseInput();
	this->updateKeyboardInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update(){
	// User Input ---
	this->updateDt();
	this->updateInput();
	

	//this->meshes[0]->rotate(glm::vec3(1.f, 0.f, 0.f));
}

void Game::render(){
	//Drawing ---
	// Clear
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Update Uniform
	this->updateUniforms();


	// Use Program
	this->shaders[SHADER_CORE_PROGRAM]->use();

	// Models
	for (auto& m : this->models) {
		m->render(this->shaders[SHADER_CORE_PROGRAM]);
	}

	// End Draw
	glfwSwapBuffers(this->window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Static Function
void Game::framebufferResizeCallback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}