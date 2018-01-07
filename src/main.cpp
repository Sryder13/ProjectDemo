#include <iostream>

#include "ryd3_core.h"
#include "ryd3_shader.h"
#include "ryd3_ResourceManager.h"
#include "ryd3_texture.h"
#include "GL/glew.h"

#include "player.h"
#include "enemy.h"

int main(int argc, char* argv[]) {
	Ryd3::Core core(640, 480);
	if (!core.initialise(2)) {
		std::cout << "Failed to start" << std::endl;
		return 1;
	}

	SDL_Event event;
	Uint32 start = SDL_GetTicks();

	bool running = true;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool shoot = false;

	Ryd3::Shader mainShader;

	Ryd3::Camera &camera = core.getCamera();
	camera.setPosition(glm::vec3(0.0f, 0.0f, -100.0f));
	camera.setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.setFieldOfView(60.0f);
	camera.setFZPlane(300.0f);

	mainShader.loadShaderFile("data/shader/vertexShader.vshd", GL_VERTEX_SHADER);
	mainShader.loadShaderFile("data/shader/fragmentShader.fshd", GL_FRAGMENT_SHADER);
	mainShader.createAndLink();

	Ryd3::Shader backgroundShader;
	backgroundShader.loadShaderFile("data/shader/background.vshd", GL_VERTEX_SHADER);
	backgroundShader.loadShaderFile("data/shader/background.fshd", GL_FRAGMENT_SHADER);
	backgroundShader.createAndLink();

	Ryd3::Texture *backgroundTexture;

	backgroundTexture = Ryd3::ResourceManager::getResourceManager()->getResource<Ryd3::Texture>("data/texture/1.png");

	// vertex and UV coords interleaved in the array
	// setup of stuff for drawing the background image
	GLfloat backQuad[] = {	-1.0f, -1.0f, 0.0f,
							0.0f,  0.0f,
							1.0f, -1.0f, 0.0f,
							1.0f,  0.0f,
							-1.0f,  1.0f, 0.0f,
							1.0f,  0.75f,
							1.0f,  1.0f, 0.0f,
							0.0f,  0.75f};

	GLubyte backIndices[] = {0, 1, 2, 2, 1, 3};

	GLuint backVao;
	GLuint backVbo;
	GLuint backVio;

	glGenVertexArrays(1, &backVao);
	glBindVertexArray(backVao);

	glGenBuffers(1, &backVbo);
	glBindBuffer(GL_ARRAY_BUFFER, backVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backQuad), backQuad, GL_STATIC_DRAW);

	glGenBuffers(1, &backVio);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backVio);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backIndices), backIndices, GL_STATIC_DRAW);

	Player *player = new Player(glm::vec3(0), glm::vec3(1), glm::quat());
	player->setPosition(glm::vec3(0.0f, 0.0f, -40.0f));

	Ryd3::EntityManager *entityManager = Ryd3::EntityManager::getEntityManager();
	entityManager->addEntity(player);

	int enemyDelay = 0;

	core.playMusic("data/music/Blown Away.ogg", -1);

	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
					}
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							moveUp = true;
							break;
						case SDLK_DOWN:
							moveDown = true;
							break;
						case SDLK_LEFT:
							moveLeft = true;
							break;
						case SDLK_RIGHT:
							moveRight = true;
							break;
						case SDLK_SPACE:
							shoot = true;
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							moveUp = false;
							break;
						case SDLK_DOWN:
							moveDown = false;
							break;
						case SDLK_LEFT:
							moveLeft = false;
							break;
						case SDLK_RIGHT:
							moveRight = false;
							break;
						case SDLK_SPACE:
							shoot = false;
							break;
					}
					break;
				default:
					break;
			}
		}

		if (player) {
			player->controlInput(moveUp, moveDown, moveLeft, moveRight, shoot);
		}

		if (enemyDelay <= 0) {
			float randXPos = -30.0f + ((float)rand() / (RAND_MAX/60.0f));
			float randYPos = -30.0f + ((float)rand() / (RAND_MAX/60.0f));
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			rotation = glm::rotate(rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			entityManager->addEntity(new Enemy(glm::vec3(randXPos, randYPos, 120.0f), glm::vec3(1.0f), rotation));
			enemyDelay = 30 + (rand() % 60);
		}
		enemyDelay--;

		entityManager->updateEntities();

		core.clearColourBuffer();
		core.clearDepthBuffer();

		backgroundShader.bind();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		GLuint vertexLoc = glGetAttribLocation(backgroundShader.getProgramID(), "game_vertexPosition");
		GLuint uvLoc = glGetAttribLocation(backgroundShader.getProgramID(), "game_vertexUv");

		backgroundTexture->bindTexture();

		glEnableVertexAttribArray(vertexLoc);
		glBindBuffer(GL_ARRAY_BUFFER, backVbo);
		glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(uvLoc);
		glBindBuffer(GL_ARRAY_BUFFER, backVbo);
		glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backVio);

		glDrawElements(GL_TRIANGLES, sizeof(backIndices), GL_UNSIGNED_BYTE, 0);

		glDisableVertexAttribArray(vertexLoc);
		glDisableVertexAttribArray(uvLoc);

		mainShader.bind();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);

		entityManager->drawEntities(camera, mainShader.getProgramID());

		core.swapWindow();

		// delay until we need to draw the next frame (60fps)
		int delay = start + 1000/60 - SDL_GetTicks();
		while (delay > 0) {
			delay = start + 1000/60 - SDL_GetTicks();
		}
	}

	entityManager->clearEntities();

	glDeleteBuffers(1, &backVbo);
	glDeleteBuffers(1, &backVao);
	glDeleteVertexArrays(1, &backVao);

	return 0;
}