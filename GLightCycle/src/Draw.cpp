/*
 * Draw.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: kimsj
 */

#include <vector>
#include <math.h>
#include "Draw.h"
#include <GL.h>
#include <glu.h>
#include <glfw.h>

#define DEG_TO_RAD M_PI/180.0

int windowWidth = 500;
int windowHeight = 500;

void init() {
	int r_bits =8, g_bits = 8, b_bits = 8, a_bits=8;
	int depth_bits = 16;
	int stencil_bits = 0;

	glfwOpenWindow(windowWidth, windowHeight,
					r_bits, g_bits, b_bits, a_bits,
					depth_bits, stencil_bits, GLFW_WINDOW);

	// Move the cursor to the center of the screen and hide it
	glfwSetMousePos(windowWidth / 2, windowHeight / 2);
	glfwDisable(GLFW_MOUSE_CURSOR);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)(windowWidth)/windowHeight, 0.1, 200);

	glMatrixMode(GL_MODELVIEW);

	GLfloat light0_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 0.5, 0.5, 0.5, 1.0 };

	/* set up ambient, diffuse, and specular components for light 0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
}

void drawWorld(World *state) {
	int viewports[4][4];

	if (state->getNumPlayers() == 1) {
		viewports[0][0] = 0;
		viewports[0][1] = 0;
		viewports[0][2] = windowWidth;
		viewports[0][3] = windowHeight;
	} else if (state->getNumPlayers() == 2) {
		viewports[0][0] = 0;
		viewports[0][1] = 0;
		viewports[0][2] = windowWidth;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = 0;
		viewports[1][1] = windowHeight/2;
		viewports[1][2] = windowWidth;
		viewports[1][3] = windowHeight/2;
	} else if (state->getNumPlayers() == 3) {
		viewports[0][0] = 0;
		viewports[0][1] = windowHeight/2;
		viewports[0][2] = windowWidth/2;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = windowWidth/2;
		viewports[1][1] = windowHeight/2;
		viewports[1][2] = windowWidth/2;
		viewports[1][3] = windowHeight/2;

		viewports[2][0] = 0;
		viewports[2][1] = 0;
		viewports[2][2] = windowWidth;
		viewports[2][3] = windowHeight/2;
	} else {
		viewports[0][0] = 0;
		viewports[0][1] = windowHeight/2;
		viewports[0][2] = windowWidth/2;
		viewports[0][3] = windowHeight/2;

		viewports[1][0] = windowWidth/2;
		viewports[1][1] = windowHeight/2;
		viewports[1][2] = windowWidth/2;
		viewports[1][3] = windowHeight/2;

		viewports[2][0] = 0;
		viewports[2][1] = 0;
		viewports[2][2] = windowWidth/2;
		viewports[2][3] = windowHeight/2;

		viewports[3][0] = windowWidth/2;
		viewports[3][1] = 0;
		viewports[3][2] = windowWidth/2;
		viewports[3][3] = windowHeight/2;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int p;

	for (p=0; p<state->getNumPlayers(); p++) {
		Cycle player = state->getCycles()[p];

		// Calculate the camera position
		GLfloat camera_pos[3] = { player.getPos().x - 5 * cos(player.getDirection()
				* DEG_TO_RAD), player.getPos().y - 5
				* sin(player.getDirection() * DEG_TO_RAD), 5.0 };

		// Calculate the camera's direction
		GLfloat camera_dir[3] = {
				player.getPos().x + cos(player.getDirection() * DEG_TO_RAD), player.getPos().y
						+ sin(player.getDirection() * DEG_TO_RAD), 0.0 };


		glViewport(viewports[p][0], viewports[p][1],
				viewports[p][2], viewports[p][3]);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
				  camera_dir[0], camera_dir[1], camera_dir[2],
				  0, 0, 1);


		int i, j;
		GLfloat light0_position[4] = { state->width/2, state->height/2, 10.0, 0.0 };

		glMatrixMode(GL_MODELVIEW);

		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

//		glPushMatrix();
//
//		for (i=0; i<state->width; i++) {
//			for (j=0; j<state->height; j++) {
//				drawPlane();
//				glTranslated(1.0, 0.0, 0.0);
//			}
//			glTranslated(-state->height, 1.0, 0.0);
//		}
//		glPopMatrix();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		{
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(state->width, 0.0, 0.0);
			glVertex3f(state->width, state->height, 0.0);
			glVertex3f(0.0, state->height, 0.0);
		}
		glEnd();

//		for (i=0; i<state->getNumPlayers(); i++) {
//			drawTrail(&(state->getTrails())[i]);
//			drawCycle(&(state->getCycles())[i]);
//		}
	}

	glfwSwapBuffers();
}

void drawPlane() {
	GLfloat grid_vertex[][3] = { {0.0, 0.0, 0.0},
								 {1.0, 0.0, 0.0},
								 {1.0, 1.0, 0.0},
								 {0.0, 1.0, 0.0}
								};

	GLfloat grid_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat grid_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat grid_ambient[] = { 0.1, 0.1, 0.1, 0.0 };
	GLfloat grid_emissive[] = { 0.1, 1.0, 1.0, 0.0 };
	GLfloat grid_shininess = 0.0;

	glMaterialfv(GL_FRONT, GL_SPECULAR, grid_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grid_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, grid_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, grid_emissive);
	glMaterialf(GL_FRONT, GL_SHININESS, grid_shininess);

	glBegin(GL_LINE_LOOP);
	{
		glVertex3fv(grid_vertex[0]);
		glVertex3fv(grid_vertex[1]);
		glVertex3fv(grid_vertex[2]);
		glVertex3fv(grid_vertex[3]);
	}
	glEnd();
}

void drawTrail(Trail *t) {
	GLfloat trail_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat trail_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat trail_ambient[] = { 1.0, 0.1, 0.1, 0.0 };
	GLfloat trail_emissive[] = { 1.0, 0.1, 0.1, 0.0 };
	GLfloat trail_shininess = 0.0;

	GLfloat trail_height = 0.5;

	glMaterialfv(GL_FRONT, GL_SPECULAR, trail_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, trail_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, trail_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, trail_emissive);
	glMaterialf(GL_FRONT, GL_SHININESS, trail_shininess);

	std::vector<Coords> points = t->getPoints();
	int i;

	for(i=1; i<(int)points.size(); i++) {
		glBegin(GL_POLYGON);
		{
			glVertex3f(points[i-1].x, points[i-1].y, 0.0);
			glVertex3f(points[i].x, points[i].y, 0.0);
			glVertex3f(points[i].x, points[i].y, trail_height);
			glVertex3f(points[i-1].x, points[i-1].y, trail_height);
		}
		glEnd();
	}
}

void drawCycle(Cycle *c) {
	GLUquadricObj *sphere;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);

	GLfloat cycle_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat cycle_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat cycle_ambient[] = { 1.0, 0.1, 0.1, 0.0 };
	GLfloat cycle_shininess = 128.0;

	glMaterialfv(GL_FRONT, GL_SPECULAR, cycle_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cycle_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cycle_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, cycle_shininess);

	glPushMatrix();
	glTranslated(c->getPos().x, c->getPos().y, 0.5);
	gluSphere(sphere, 0.5, 15, 15);
	glPopMatrix();
}

void drawItem(WorldItem *) {

}
