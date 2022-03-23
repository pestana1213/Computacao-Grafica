#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
int seed = 100; 

int dist(float x, float y) {
	return ((x * x) + (y * y));
}


void drawArvore() {
	srand(seed);

	for (int i = 0;i <= 100;i++) {

		float randomX = (float(rand()) / float(RAND_MAX)) * 200;
		float randomZ = (float(rand()) / float(RAND_MAX)) * 200;

		
		if (randomX > 100) {
			randomX = -randomX + 100;
		}
		if (randomZ > 100) {
			randomZ = - randomZ + 100;
		}

		if (dist(randomX, randomZ) > 1000) {
			printf(" teste: X: %f \n Z: %f \n Dist: %i", randomX, randomZ, dist(randomX, randomZ));
			glPushMatrix();
			glTranslatef(randomX, 0, randomZ);
			glRotatef(-90, 1.0, 0.0, 0.0);
			glColor3f(0.15f, 0.064f, 0.031f);
			glutSolidCone(2, 20, 10, 10); //tronco 
			glPopMatrix();

			glPushMatrix();
			glTranslatef(randomX, 10, randomZ);

			glRotatef(-90, 1.0, 0.0, 0.0);

			glColor3f(0.0f, 0.6f, 0.0f);
			glutSolidCone(5, 15, 10, 10); //parte de cima  
			glPopMatrix();
		}
	}
}

void drawTeaPot() {
	glPushMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(sin(30)*10, 3.0, cos(30)*10);
	glutSolidTeapot(3);

	for (int i = 0; i <= 20;i++) {
		glPopMatrix();
		glPushMatrix();

		glTranslatef(sin(30) * 10, 3.0, cos(30) * 10);
		glRotatef(30, 0.0, 1.0, 0.0);

		glutSolidTeapot(3);
	}
	glPopMatrix();
}


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
		glEnd();
	// End of frame
	

	// put code to draw scene in here
	drawArvore();
	drawTeaPot();
	glColor3f(1.0f, 0.0f, 0.031f);
	glutSolidTorus(1, 2, 50, 50);
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
