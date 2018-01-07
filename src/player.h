#ifndef DEMO_PLAYER_H
#define DEMO_PLAYER_H

#include "ryd3_entity.h"

class Player : public Ryd3::Entity {
	public:
		Player(glm::vec3 position, glm::vec3 scale, glm::quat rotation);
		void controlInput(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, bool shoot);
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
