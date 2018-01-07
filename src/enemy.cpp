#include "enemy.h"

#include <ryd3_ResourceManager.h>
#include <ryd3_entitymanager.h>
#include <ryd3_model.h>

#include "projectile.h"

Enemy::Enemy(glm::vec3 position, glm::vec3 scale, glm::quat rotation) : Entity(position, scale, rotation) {
	Ryd3::ResourceManager *rManager;
	rManager = Ryd3::ResourceManager::getResourceManager();
	setModel(rManager->getResource<Ryd3::Model>("data/model/enemy.obj"));
	momentum = glm::vec3(0.0f, 0.0f, -1.0f);
	radius = 5.0f;
	shootTimer = 60;
}

int Enemy::update() {
	setPosition(getPosition() + momentum);
	if (shootTimer <= 0 && getPosition().z > -40.0f) {
		Ryd3::EntityManager *eManager = Ryd3::EntityManager::getEntityManager();
		eManager->addEntity(new Projectile(getPosition(), glm::vec3(1.0f), glm::quat(), glm::vec3(0.0f, 0.0f, -2.0f), this));
		shootTimer = 120;
	}
	shootTimer--;

	if (getPosition().z < -150.0f) {
		return 0;
	}
	return 1;
}
