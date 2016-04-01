#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "tinyxml2.h"
#include<Type.h>
#include<Transformation.h>
#include<Point.h>
#include<Model.h>


#include <string>

using namespace std;
using namespace tinyxml2;

float fov = 10;
float px = 0, py = fov/2, pz = fov/2, ord = 0.5, rato = 0, ratoIn, angle = 0.0;
int menu, wsizex = 800, wsizey = 400;

float pontos[50000][3];
int npontos = 0;

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

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	// put the geometric transformations here


	// put drawing instructions here
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	for (int jz = 0; jz < npontos; jz++) {
		glVertex3f(pontos[jz][0], pontos[jz][1], pontos[jz][2]);
	}
	glEnd();
	

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void keys(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:
		angle += 5*ord;
		break;
	case GLUT_KEY_RIGHT:
		angle -= 5*ord;
		break;
	case GLUT_KEY_UP: py += ord; break;
	case GLUT_KEY_DOWN: py -= ord; break;
	}
	glutPostRedisplay();
}

void BotRato(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			rato = 1;
			ratoIn = x;
		}
		else if (state == GLUT_UP)
			rato = 0;
	}
}

void MovRato(int x, int y) {
	if (rato == 1)
		if (x < ratoIn) {
			if (px>-fov && px <= 0 && pz >= 0 && pz <= fov) {
				px -= (ord / 10);
				pz -= (ord / 10);
			}
			else if (px >= -fov && px<0 && pz >= -fov && pz <= 0) {
				px += (ord / 10);
				pz -= (ord / 10);
			}
			else if (px >= 0 && px<fov && pz >= -fov && pz <= 0) {
				px += (ord / 10);
				pz += (ord / 10);
			}
			else if (px>0 && px <= fov && pz >= 0 && pz <= fov) {
				px -= (ord / 10);
				pz += (ord / 10);
			}
		}
		else {
			if (px >= 0 && px<fov && pz >= 0 && pz <= fov) {
				px += (ord / 10);
				pz -= (ord / 10);
			}
			else if (px>0 && px <= fov && pz >= -fov && pz <= 0) {
				px -= (ord / 10);
				pz -= (ord / 10);
			}
			else if (px>-fov && px <= 0 && pz >= -fov && pz <= 0) {
				px -= (ord / 10);
				pz += (ord / 10);
			}
			else if (px >= -fov && px<0 && pz >= 0 && pz <= fov) {
				px += (ord / 10);
				pz += (ord / 10);
			}
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

void leituraM(string nome) {

	//LER FICHEIRO!!!!
	string line, saux;
	ifstream file(nome);
	int iaux;


	if (file.is_open()) {
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

}

void lXML(string nome) {
XMLDocument docxml;
		if (!docxml.LoadFile(nome.c_str()))
	{
		
		     
	XMLElement* root = docxml.RootElement(); //guarda em root o primeiro filho (neste caso com nome especificado como "scene");
	XMLElement* elem;       //elem => elemento xml auxiliar para percorrer o documento (prзximo ciclo for)
	Transformation t = Transformation::Transformation();
		
	Modelos(root, t);
		}
		else cout << "Nao foi encontrado o xml" << endl;
}

int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(wsizex, wsizey);
	glutCreateWindow("CG@DI-UM");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
if(argc > 1){
	lXML(argv[1]);
}
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard and menu callbacks
	glutSpecialFunc(keys);
	glutMouseFunc(BotRato);
	glutMotionFunc(MovRato);

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