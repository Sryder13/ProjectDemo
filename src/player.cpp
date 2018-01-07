#include "player.h"

#include <ryd3_ResourceManager.h>
#include <ryd3_entitymanager.h>
#include <ryd3_model.h>

#include "projectile.h"

Player::Player(glm::vec3 position, glm::vec3 scale, glm::quat rotation) : Entity(position, scale, rotation) {
	Ryd3::ResourceManager *rManager;
	rManager = Ryd3::ResourceManager::getResourceManager();
	setModel(rManager->getResource<Ryd3::Model>("data/model/ship.obj"));
	momentum = glm::vec3(0);
	radius = 5.0f;
	shootTimer = 0;
}

void Player::controlInput(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, bool shoot) {
	momentum = glm::vec3(0);
	setRotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	if (moveUp) {
		momentum.y = 1.0f;
		setRotation(glm::rotate(getRotation(), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	}
	if (moveDown) {
		momentum.y = -1.0f;
		setRotation(glm::rotate(getRotation(), glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	}
	if (moveLeft) {
		momentum.x = 1.0f;
		setRotation(glm::rotate(getRotation(), glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	}
	if (moveRight) {
		momentum.x = -1.0f;
		setRotation(glm::rotate(getRotation(), glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	}
	if (shoot && shootTimer <= 0) {
		Ryd3::EntityManager *eManager = Ryd3::EntityManager::getEntityManager();
		eManager->addEntity(new Projectile(getPosition(), glm::vec3(1.0f), glm::quat(), glm::vec3(0.0f, 0.0f, 2.0f), this));
		shootTimer = 10;
	}
}

int Player::update() {
	glm::vec3 playerPosition = getPosition();
	playerPosition += momentum;
	if (playerPosition.x < -30.0f) {
		playerPosition.x = -30.0f;
	}
	else if (playerPosition.x > 30.0f) {
		playerPosition.x = 30.0f;
	}
	if (playerPosition.y < -30.0f) {
		playerPosition.y = -30.0f;
	}
	else if (playerPosition.y > 30.0f) {
		playerPosition.y = 30.0f;
	}
	setPosition(playerPosition);
	shootTimer--;
	return 1;
}
