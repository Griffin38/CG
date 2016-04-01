#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "tinyxml2.h"
#include"Type.h"
#include"Transformation.h"
#include"Point.h"
#include"Model.h"


#include <string>

using namespace std;
using namespace tinyxml2;

float fov = 10;
float px = 0, py = fov / 2, pz = fov / 2, ord = 0.5, rato = 0, ratoIn, angle = 0.0;
int menu, wsizex = 800, wsizey = 400;

vector<Model> ListaM;

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






// write function to process keyboard events




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

bool leituraM(string nome , Model m) {
	bool aux;
	//LER FICHEIRO!!!!
	string line, saux;
	ifstream file(nome);
	int iaux;
	float x, y, z;

	if (file.is_open()) {  //se o ficheiro existir
		while (getline(file, line))
		{
			//x 
			iaux = line.find(",");
			saux = line.substr(0, iaux);
			 x = atof(saux.c_str());
			line.erase(0, iaux + 1);
			//Y
			iaux = line.find(",");
			saux = line.substr(0, iaux);
			 y = atof(saux.c_str());
			line.erase(0, iaux + 1);
			//Z
			iaux = line.find(",");
			saux = line.substr(0, iaux);
			 z = atof(saux.c_str());
			line.erase(0, iaux + 1);

			//add ponto ao modelo
			Point p = Point(x, y, z);

			m.adicionaPonto(p);
		
		}
		
		file.close();
		aux = true;
	}
	else
	{
		cout << "Nao foi possivel ler o ficheiro" << endl;
		aux = false;
	}
	//END OF LER FICHEIRO!!!!!
	return aux;
}

void Modelos(XMLElement* grupo, Transformation tdefault) {
	Transformation temp;
	Type tipoN;

	//ver se tem filhos
	if (strcmp(grupo->FirstChildElement()->Value(), "group") == 0) {
		grupo = grupo->FirstChildElement();
	}


	//percorrer os filhos ( atributos) ate aos modelos 

	for (XMLElement* filho = grupo->FirstChildElement(); strcmp(filho->Value(), "models") != 0;filho = filho->NextSiblingElement() ) {
		
		//rotate
		if (strcmp(filho->Value(), "rotate") == 0) {
			float tx, ty, tz,tang;

			if (filho->Attribute("angle") == NULL) { tang = 0; }
			else { tang = stof(filho->Attribute("Z")); }

			if (filho->Attribute("X") == NULL) { tx = 0; }
			else { tx = stof(filho->Attribute("X")); }

			if (filho->Attribute("Y") == NULL) { ty = 0; }
			else { ty = stof(filho->Attribute("Y")); }

			if (filho->Attribute("Z") == NULL) { tz = 0; }
			else { tz = stof(filho->Attribute("Z")); }
			
			Type tt = tdefault.getRotacao();
			tipoN = Type::Type(tang + tt.getTAng(),tx + tt.getTX(), ty + tt.getTY(), tz + tt.getTZ());
			temp.setRotacao(tipoN);

		}

		//scale 
		if (strcmp(filho->Value(), "scale") == 0) {

			float tx, ty, tz;

			if (filho->Attribute("X") == NULL) { tx = 0; }
			else { tx = stof(filho->Attribute("X")); }

			if (filho->Attribute("Y") == NULL) { ty = 0; }
			else { ty = stof(filho->Attribute("Y")); }

			if (filho->Attribute("Z") == NULL) { tz = 0; }
			else { tz = stof(filho->Attribute("Z")); }

			Type tt = tdefault.getEscala();
			tipoN = Type::Type(tx + tt.getTX(), ty + tt.getTY(), tz + tt.getTZ());
			temp.setEscala(tipoN);
		}

		//translate 
		if (strcmp(filho->Value(), "translate") == 0) {

			float tx, ty, tz;

			if (filho->Attribute("X") == NULL) { tx = 0; }
			else { tx = stof(filho->Attribute("X")); }

			if (filho->Attribute("Y") == NULL) { ty = 0; }
			else { ty = stof(filho->Attribute("Y")); }

			if (filho->Attribute("Z") == NULL) { tz = 0; }
			else { tz = stof(filho->Attribute("Z")); }

			Type tt = tdefault.getTranslacao();
			tipoN = Type::Type(tx + tt.getTX(), ty + tt.getTY(), tz + tt.getTZ());
			temp.setTranslacao(tipoN);
		}
	}

	//percorrer os modelos do filho 
	for (XMLElement* modelo = grupo->FirstChildElement("models")->FirstChildElement("model"); modelo; modelo = modelo->NextSiblingElement("model")) {
		Model m (modelo->Attribute("file"));
		if (leituraM(m.getNomeModelo(), m)) {
			//escrever os modelos
			m.setTransformacao(temp);
			ListaM.push_back(m);
		}
	}
	//ver se tem mais filhos

	if (grupo->FirstChildElement("group")) {
		Modelos(grupo->FirstChildElement("group"), temp);
	}
	//ver se tem irmaos
	if (grupo->NextSiblingElement("group")) {
		Modelos(grupo->NextSiblingElement("group"), tdefault);
	}

}
void lXML(string nome) {
	XMLDocument docxml;
	if (!docxml.LoadFile(nome.c_str()))
	{


		XMLElement* root = docxml.RootElement(); //guarda em root o primeiro filho (neste caso com nome especificado como "scene");
		XMLElement* elem;       //elem => elemento xml auxiliar para percorrer o documento (prзximo ciclo for)
		Transformation t = Transformation::Transformation(); // transformaçao 
		
		if (root != NULL) {
			Modelos(root->FirstChildElement("group"), t); // manda o primeiro grupo para procurar os modelos 

		}
		
	}
	else cout << "Nao foi encontrado o xml" << endl; // nao existe o ficheiro
}

int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(wsizex, wsizey);
	glutCreateWindow("CG@DI-UM");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (argc > 1) {
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