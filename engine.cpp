#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

float fov = 10;
float px = 0, py = 0, pz = 10, ord = 0.5;
int menu;
float pontos[100][3];
int npontos;

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
	glColor3f(0, 0, 1);
	for (int jz = 0; jz < npontos; jz++) {
		glVertex3f(pontos[jz][0], pontos[jz][1], pontos[jz][2]);
	}
	glEnd();
	/*
	glColor3f(0, 0, 1);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3f(0, 1, 1);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3f(1, 0, 1);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);*/	

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
	case GLUT_KEY_F1: 
		fov += ord; 		
		if (px > 0 && pz > 0 && py > 0) {
			px += (ord / 3);
			pz += (ord / 3);
			py += (ord / 3);
		}
		break;
	case GLUT_KEY_F2:
		fov -= ord;
		if (px > 0 && pz > 0 && py > 0) {
			px -= (ord / 3);
			pz -= (ord / 3);
			py -= (ord / 3);
		}
		break;

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


	//LER FICHEIRO!!!!
	string line, saux, ficheiro = "box.3d";
	ifstream file(ficheiro);	
	int iaux;


	if (file.is_open()){
		npontos = 0;
		while (getline(file, line))
		{			
			
			iaux = line.find(",");
			saux = line.substr(0, iaux);
			pontos[npontos][0] = atof(saux.c_str());
			line.erase(0, iaux + 1);			

			iaux = line.find(",");
			saux = line.substr(0, iaux);
			pontos[npontos][1] = atof(saux.c_str());
			line.erase(0, iaux + 1);

			iaux = line.find(",");
			saux = line.substr(0, iaux);
			pontos[npontos][2] = atof(saux.c_str());
			line.erase(0, iaux + 1);
			
			//cout << pontos[npontos][0] << "," << pontos[npontos][1] << "," << pontos[npontos][2] << endl;
			npontos++;
		}
		cout << npontos << endl;
	}
	else
	{
		cout << "Nao foi possivel ler o ficheiro" << endl;
	}
	//END OF LER FICHEIRO!!!!!

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
