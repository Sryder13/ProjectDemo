#include <iostream>

#include "ryd3_core.h"

#include "GL/glew.h"

int main(int argc, char* argv[]) {
	Ryd3Core core;
	if (!core.setupWindowandContext()) {
		return 1;
	}

	bool running = true;
	float angle = 0;

	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}

		angle += 1;
		while (angle > 360) {
			angle -= 360;
		}
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glRotatef(angle, 0, 0, 1);
		glColor3ub(255, 255, 255);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
		glPopMatrix();

		core.swapWindow();

		SDL_Delay(10);
	}

	return 0;
}