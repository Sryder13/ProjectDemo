#ifndef DEMO_ENEMY_H
#define DEMO_ENEMY_H

#include "ryd3_entity.h"

class Enemy : public Ryd3::Entity {
	public:
		Enemy(glm::vec3 position, glm::vec3 scale, glm::quat rotation);
		int update();
		glm::vec3 getMomentum() {return this->momentum;};
		float getRadius() {return this->radius;};
		int getShootTimer() {return this->shootTimer;};
	private:
		glm::vec3 momentum;
		float radius;
		int shootTimer;
};

#endif
