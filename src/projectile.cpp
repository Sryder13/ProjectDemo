#include "projectile.h"

#include <ryd3_ResourceManager.h>
#include <ryd3_entitymanager.h>
#include <ryd3_model.h>
#include <ryd3_sound.h>
#include <math.h>

#include "player.h"
#include "enemy.h"

#define PI 3.14159265

#define COLLIDE_KILL_THIS 0x01
#define COLLIDE_KILL_OTHER 0x02

Projectile::Projectile(glm::vec3 position, glm::vec3 scale, glm::quat rotation, glm::vec3 momentum, Ryd3::Entity *owner) : Entity(position, scale, rotation) {
	Ryd3::ResourceManager *rManager;
	rManager = Ryd3::ResourceManager::getResourceManager();
	setModel(rManager->getResource<Ryd3::Model>("data/model/projectile.obj"));
	this->momentum = momentum;
	this->owner = owner;
	radius = 1.0f;
	scaleTimer = 15;
	rManager->getResource<Ryd3::Sound>("data/sound/laser.wav")->playSound();
}

int Projectile::update() {
	setPosition(getPosition() + momentum);
	glm::vec3 newScale = glm::vec3(1.0f) - (0.5f * (float)sin(((float)scaleTimer/15)*180*PI/180));
	setScale(newScale);
	scaleTimer--;
	if (scaleTimer <= 0) {
		scaleTimer = 15;
	}
	if (getPosition().z > 300.0f || getPosition().z < -150.0f) {
		return 0;
	}

	Ryd3::EntityManager *eManager = Ryd3::EntityManager::getEntityManager();

	for (std::list<Ryd3::Entity *>::iterator it = eManager->getListBegin(); it != eManager->getListEnd(); ) {
		if (owner == (*it) || this == (*it)) {
			it++;
			continue;
		}
		Player *otherPlayer = dynamic_cast<Player *>((*it));
		Enemy *otherEnemy = dynamic_cast<Enemy *>((*it));
		if (otherPlayer != NULL) {
			if (glm::distance(getPosition(), (*it)->getPosition()) < radius + otherPlayer->getRadius()) {
				int collideFlags = collide((*it));
				if (collideFlags & COLLIDE_KILL_OTHER) {
					it = eManager->removeEntity((*it));
				} else {
					it++;
				}
				if (collideFlags & COLLIDE_KILL_THIS) {
					return 0;
				}
			} else {
				it++;
			}
		} else if (otherEnemy != NULL) {
			if (glm::distance(getPosition(), (*it)->getPosition()) < radius + otherEnemy->getRadius()) {
				int collideFlags = collide((*it));
				if (collideFlags & COLLIDE_KILL_OTHER) {
					it = eManager->removeEntity((*it));
				} else {
					it++;
				}
				if (collideFlags & COLLIDE_KILL_THIS) {
					return 0;
				}
			} else {
				it++;
			}
		} else {
			it++;
		}
	}
	return 1;
}

int Projectile::collide(Ryd3::Entity *other) {
	Player *otherPlayer = dynamic_cast<Player *>(other);
	Enemy *otherEnemy = dynamic_cast<Enemy *>(other);
	int returnVal = 0;
	if (otherPlayer != NULL) {
		returnVal = COLLIDE_KILL_OTHER;
	}
	if (otherEnemy != NULL) {
		returnVal = COLLIDE_KILL_THIS|COLLIDE_KILL_OTHER;
	}
	return returnVal;
}
