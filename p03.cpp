#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>


float fov = 10, px = 0, py = fov/2, pz = fov/2, ord = 0.5;
int menu;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(px, py, pz,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);



	// put the geometric transformations here


	// put drawing instructions here
	glBegin(GL_TRIANGLES);
	float alfa, alfa2;
	int n = 20, h=2, r=1;

	/*for (int i = 0; i < n; i++) {			//CONE!!!!
		alfa = i*(2 * M_PI) / n;
		alfa2 = (i + 1)*(2 * M_PI) / n;
		glColor3f(1, 0, 0);
		glVertex3f(0.0f, -h / 2, 0.0f);
		glVertex3f(r * (sin(alfa2)), -h / 2, r * cos(alfa2));
		glVertex3f(r*(sin(alfa)), -h / 2, r*cos(alfa));

		glColor3f(0, 1, 0);
		glVertex3f(0, h / 2, 0);
		glVertex3f(r * (sin(alfa)), -h / 2, r * cos(alfa));
		glVertex3f(r * (sin(alfa2)), -h / 2, r * cos(alfa2));
		

	}*/

	/*for (int i = 0; i < n; i++) {		//CILINDRO!!!
		alfa = i*(2 * M_PI) / n;
		alfa2 = (i + 1)*(2 * M_PI) / n;
		glColor3f(1, 0, 0);
		glVertex3f(0.0f, h/2, 0.0f);
		glVertex3f(r*(sin(alfa)), h/2, r*cos(alfa));		
		glVertex3f(r * (sin(alfa2)), h/2, r * cos(alfa2));

		glColor3f(0, 1, 0);
		glVertex3f(r*(sin(alfa2)), h / 2, r*cos(alfa2));
		glVertex3f(r * (sin(alfa)), h/2, r * cos(alfa));		
		glVertex3f(r * (sin(alfa)), -h/2, r * cos(alfa));
		
		glVertex3f(r * (sin(alfa)), -h / 2, r * cos(alfa));
		glVertex3f(r*(sin(alfa2)), -h / 2, r*cos(alfa2));
		glVertex3f(r*(sin(alfa2)), h / 2, r*cos(alfa2));

		glColor3f(0, 0, 1);
		glVertex3f(0.0f, -h / 2, 0.0f);
		glVertex3f(r * (sin(alfa2)), -h / 2, r * cos(alfa2));
		glVertex3f(r*(sin(alfa)), -h / 2, r*cos(alfa));		
	}*/
	int stack = n, slice = n;
	int flag = 0;
	float beta;
	for (int i = 0; i < stack; i++) {		//Esfera!!!
		for (int j = 0; j < slice; j++) {
			alfa = j*(2 * M_PI) / slice;
			beta = - M_PI/2 + i* M_PI / slice;
				glVertex3f(r*sin(alfa)*cos(beta), r*sin(beta), r * cos(alfa)*cos(beta));
				glVertex3f(r*sin(alfa + 2 * M_PI / slice)*cos(beta), r*sin(beta), r * cos(alfa + 2 * M_PI / slice)*cos(beta));
				glVertex3f(r*sin(alfa)*cos(beta + M_PI / slice), r*sin(beta + M_PI/ slice), r * cos(alfa)*cos(beta + M_PI / slice));

				glVertex3f(r*sin(alfa + 2 * M_PI / slice)*cos(beta + M_PI / slice), r*sin(beta + M_PI / slice), r * cos(alfa + 2 * M_PI / slice)*cos(beta + M_PI / slice));
				glVertex3f(r*sin(alfa)*cos(beta + M_PI / slice), r*sin(beta + M_PI / slice), r * cos(alfa)*cos(beta + M_PI / slice));
				glVertex3f(r*sin(alfa + 2 * M_PI / slice)*cos(beta), r*sin(beta), r * cos(alfa + 2 * M_PI / slice)*cos(beta));
		}
	}
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void keys(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:
		if (px>-fov && px <= 0 && pz >= 0 && pz <= fov) {
			px -= ord;
			pz -= ord;
		}
		else if (px >= -fov && px<0 && pz >= -fov && pz <= 0) {
			px += ord;
			pz -= ord;
		}
		else if (px >= 0 && px<fov && pz >= -fov && pz <= 0) {
			px += ord;
			pz += ord;
		}
		else if (px>0 && px <= fov && pz >= 0 && pz <= fov) {
			px -= ord;
			pz += ord;
		}

		break;
	case GLUT_KEY_RIGHT:
		if (px >= 0 && px<fov && pz >= 0 && pz <= fov) {
			px += ord;
			pz -= ord;
		}
		else if (px>0 && px <= fov && pz >= -fov && pz <= 0) {
			px -= ord;
			pz -= ord;
		}
		else if (px>-fov && px <= 0 && pz >= -fov && pz <= 0) {
			px -= ord;
			pz += ord;
		}
		else if (px >= -fov && px<0 && pz >= 0 && pz <= fov) {
			px += ord;
			pz += ord;
		}
		break;
	case GLUT_KEY_UP: py += ord; break;
	case GLUT_KEY_DOWN: py -= ord; break;

	}
	glutPostRedisplay();
}


// write function to process menu events

void menu_op(int id_op) {
	switch (id_op) {
	case 1:
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case 2:
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG@DI-UM");


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard and menu callbacks
	glutSpecialFunc(keys);


	// put here the definition of the menu 

	menu = glutCreateMenu(menu_op);
	glutAddMenuEntry("FILL", 1);
	glutAddMenuEntry("LINE", 2);
	glutAddMenuEntry("POINT", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
