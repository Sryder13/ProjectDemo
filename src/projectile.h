#ifndef DEMO_PROJECTILE_H
#define DEMO_PROJECTILE_H

#include "ryd3_entity.h"

class Projectile : public Ryd3::Entity {
	public:
		Projectile(glm::vec3 position, glm::vec3 scale, glm::quat rotation, glm::vec3 momentum, Ryd3::Entity *owner);
		int update();
		int collide(Ryd3::Entity *other);
		glm::vec3 getMomentum() {return this->momentum;};
		float getRadius() {return this->radius;};
		Ryd3::Entity *getOwner() {return this->owner;};
	private:
		glm::vec3 momentum;
		float radius;
		Ryd3::Entity *owner;
		int scaleTimer;
};

#endif
