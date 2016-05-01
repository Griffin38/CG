#include <GL/glew.h>
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

float xx = 0, yy = 0, zz = 0, angle = 0.0f;
float alpha = 0.0f, beta = 0.0f, radius = 40.0f;

//RATO
float rato = 0, ratoInx, ratoIny;
//CAM
float camX = 0, camY = 0, camZ = 0, posX = 0, posY = 0, posZ = 0;
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


//CAMERA
void sphericalToCartesian() {

	camX = posX + radius * cos(beta) * sin(alpha);
	camY = radius * sin(beta);
	camZ = posZ + radius * cos(beta) * cos(alpha);
}


//render Catmul 

void renderCatmullRomCurve(vector<Point> pontos) {
	int n = pontos.size();
	float p[3];

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		p[0] = pontos[i].getX(); p[1] = pontos[i].getY(); p[2] = pontos[i].getZ();
		glVertex3fv(p);
	}
	glEnd();
}
//render scnene 


void renderScene(void) {
	float pos[4] = { 1.0, 1.0, 1.0, 0.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	gluLookAt(camX, camY, camZ,
		posX, posY, posZ,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xx, yy, zz);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	int n_models = ListaM.size();
	
	
	
	for (int i = 0; i < n_models; i++) {
		
		
		Model mod = ListaM[i];
		float res[3];
		
		Transformation tr = ListaM[i].getTransformacao();
		glPushMatrix();
		if (!tr.trasnformacaoVazia()) {	

			Rotate r = tr.getRotacao();
			if (!r.isEmpty() && r.getTime()!=0) {
				float t = glutGet(GLUT_ELAPSED_TIME) % (int)(r.getTime() * 1000);
				float gr = (t * 360) / (r.getTime() * 1000);
			
				glRotatef(gr, r.getX(), r.getY(), r.getZ());
			}

			Translate t = tr.getTranslacao();
			if (!t.isEmpty() ) {
				
					int n = t.getSize();
					if (n > 0) {
						float r = glutGet(GLUT_ELAPSED_TIME) % (int)(t.getTime() * 1000);
						float gt = r / (t.getTime() * 1000);
						vector<Point> tp = t.getPontos();
						//marca das órbitas


						renderCatmullRomCurve(t.getCurvas());
						t.getGlobalCatmullRomPoint(gt, res, tp);
				
 						glTranslatef(res[0], res[1], res[2]);
					}
				}


			
			Scalate s = tr.getEscala();
			if (!s.isEmpty()) {
				
				glScalef(s.getX(), s.getY(), s.getZ());
			
			}

			Type tipo = tr.getCor();
			if (!tipo.isEmpty()) {
				glColor3f(tipo.getTX(), tipo.getTY(), tipo.getTZ());

			}
		}
			
		mod.draw();
		glPopMatrix();
		
		
	}



	glutPostRedisplay();
	glutSwapBuffers();
}





// write function to process keyboard events

void keys(int key, int xx, int yy)
{
	int mod = glutGetModifiers();
	switch (key) {

	case GLUT_KEY_RIGHT:
		if (mod == GLUT_ACTIVE_SHIFT)
			posX++;
		else
			alpha += 0.1;
		break;

	case GLUT_KEY_LEFT:
		if (mod == GLUT_ACTIVE_SHIFT)
			posX--;
		else
			alpha -= 0.1;
		break;

	case GLUT_KEY_UP:
		if (mod == GLUT_ACTIVE_SHIFT)
			posZ--;
		else {
			beta += 0.1f;
			if (beta > 1.5f)
				beta = 1.5f;
		}
		break;

	case GLUT_KEY_DOWN:
		if (mod == GLUT_ACTIVE_SHIFT)
			posZ++;
		else {
			beta -= 0.1f;
			if (beta < -1.5f)
				beta = -1.5f;
		}
		break;

	case GLUT_KEY_PAGE_UP: radius -= 1.5f;
		if (radius < 0.1f)
			radius = 0.1f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius += 1.5f; break;

	}
	sphericalToCartesian();
	glutPostRedisplay();
}

void BotRato(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			rato = 1;
			ratoInx = x;
			ratoIny = y;
		}
		else if (state == GLUT_UP)
			rato = 0;
	}
}

void MovRato(int x, int y) {
	int flag = 0;
	int merro = 30;
	if (rato == 1) {
		if (x < (ratoInx - merro)) {
			//cout << "x " << x << " | Ratox " << ratoInx << endl;
			//cout << "y " << y << " | Ratoy " << ratoIny << endl;
			alpha += 0.05;
		}
		else if (x >(ratoInx + merro)) {
			alpha -= 0.05;
		}
		if (y > (ratoIny + (merro * 3))) {
			beta += 0.01f;
			if (beta > 1.5f)
				beta = 1.5f;
		}
		else if (y < (ratoIny - (merro * 3))) {
			beta -= 0.01f;
			if (beta < -1.5f)
				beta = -1.5f;
		}

	}
	sphericalToCartesian();
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

int leituraM(string nome , Model& m) {


	bool aux;
	//LER FICHEIRO!!!!
	string line, saux, delimiter  = ",";
	ifstream file(nome);
	int iaux;
	float x, y, z;

	if (file.is_open()) {
		while (getline(file, line)) {
			iaux = line.find(delimiter);
			saux = line.substr(0, iaux);
			x= atof(saux.c_str());
			line.erase(0, iaux + delimiter.length());
		

			iaux = line.find(delimiter);
			saux = line.substr(0, iaux);
			y = atof(saux.c_str());
			line.erase(0, iaux + delimiter.length());
		

			iaux = line.find(delimiter);
			saux = line.substr(0, iaux);
			z = atof(saux.c_str());
			line.erase(0, iaux + delimiter.length());
			

			Point po(x,y,z);
			m.adicionaPonto(po);

			
		}
		file.close();
		return 1;
	}
	else {
		cout << "Nao foi possivel ler o arquivo" << endl;
		return 0;
	}
	//END OF LER FICHEIRO!!!!!
	
}

void Modelos(XMLElement* grupo, Transformation tdefault) {
	Transformation temp;
	Type tipoN;
	Rotate rN;
	Scalate sN;
	Translate tN;
	int c;
	//ver se tem filhos
	if (strcmp(grupo->FirstChildElement()->Value(), "group") == 0) {
		grupo = grupo->FirstChildElement();
	}


	//percorrer os  atributos ate aos modelos 
	temp = Transformation::Transformation();
	for (XMLElement* filho = grupo->FirstChildElement(); strcmp(filho->Value(), "models") != 0;filho = filho->NextSiblingElement() ) {
		
		//rotate+e*************************************************************************************************************************
		if (strcmp(filho->Value(), "rotate") == 0) {
			float tx, ty, tz, tt2;



			if (filho->Attribute("X") == NULL) { tx = 0; }
			else { tx = stof(filho->Attribute("X")); }

			if (filho->Attribute("Y") == NULL) { ty = 0; }
			else { ty = stof(filho->Attribute("Y")); }

			if (filho->Attribute("Z") == NULL) { tz = 0; }
			else { tz = stof(filho->Attribute("Z")); }

			if (filho->Attribute("T") == NULL) { tt2 = 0; }
			else { tz = stof(filho->Attribute("T")); }

			Rotate tt = tdefault.getRotacao();
			rN = Rotate::Rotate(tt2, tx + tt.getX(), ty + tt.getY(), tz + tt.getZ());
			temp.setRotacao(rN);

		}

		//scale *********************************************************************************************************************************
		if (strcmp(filho->Value(), "scale") == 0) {
			
			float tx, ty, tz;

			if (filho->Attribute("X") == NULL) { tx = 1; }
			else { tx = stof(filho->Attribute("X")); }

			if (filho->Attribute("Y") == NULL) { ty = 1; }
			else { ty = stof(filho->Attribute("Y")); }

			if (filho->Attribute("Z") == NULL) { tz = 1; }
			else { tz = stof(filho->Attribute("Z")); }

			Scalate tt = tdefault.getEscala();
			sN = Scalate::Scalate(tx * tt.getX(), ty * tt.getY(), tz * tt.getZ());
			temp.setEscala(sN);
			
		}
		
		

		//translate  ***************************************************************************************************************
	

		
		

		if (strcmp(filho->Value(), "translate") == 0) {
			float tx, ty, tz, tt2;
			vector<Point> pontosAux;
			int i = 0;

			tx = ty = tz = tt2 = 0;
			if (filho->Attribute("T")) {
				tt2 = stof(filho->Attribute("T"));
			}

			for (XMLElement* ponto = filho->FirstChildElement("Point"); ponto; ponto = ponto->NextSiblingElement("Point")) {

				if (ponto->Attribute("X")) {
					tx = stof(ponto->Attribute("X"));
				}
				if (ponto->Attribute("Y")) {
					ty = stof(ponto->Attribute("Y"));
				}
				if (ponto->Attribute("Z")) {
					tz = stof(ponto->Attribute("Z"));
				}
				Translate tt = tdefault.getTranslacao();
				if (!tt.isEmpty()) {
					tx = tx + tt.getPontos().at(i).getX();
					ty = ty + tt.getPontos().at(i).getY();
					tz = tz + tt.getPontos().at(i).getZ();
				
					i++;
				
				}
				
				Point p = Point::Point(tx, ty, tz);
				pontosAux.push_back(p);
			}
			
			tN = Translate::Translate(tt2, pontosAux, pontosAux.size());
			tN.fazCurvas();
			temp.setTranslacao(tN);
		}

	
		//Cor  ***************************************************************************************************************************
	
		if (strcmp(filho->Value(), "color") == 0) {
			
			float tx, ty, tz;

			if (filho->Attribute("R") == NULL) { tx = 0; }
			else { tx = stof(filho->Attribute("R")); }

			if (filho->Attribute("G") == NULL) { ty = 0; }
			else { ty = stof(filho->Attribute("G")); }

			if (filho->Attribute("B") == NULL) { tz = 0; }
			else { tz = stof(filho->Attribute("B")); }
			
			Type tt = tdefault.getCor();
			tipoN = Type::Type(tx ,ty , tz );
			temp.setCor(tipoN);
			
		}
		else temp.setCor(tdefault.getCor());
	}

	//percorrer os modelos do filho 
	for (XMLElement* modelo = grupo->FirstChildElement("models")->FirstChildElement("model"); modelo; modelo = modelo->NextSiblingElement("model")) {
		Model m (grupo->Attribute("name"));
		if (leituraM(modelo->Attribute("file"), m)) {
			//escrever os modelos
			m.setTransformacao(temp);
			ListaM.push_back(m);
		//	cout << "escala m" << temp.getEscala().getTX() << " " << temp.getEscala().getTY() << " " << temp.getEscala().getTZ() << endl;
			cout << "adicionado " << grupo->Attribute("name") << endl;
			
		}
	}
	//ver se tem mais filhos

	if (grupo->FirstChildElement("group")) {
		XMLElement *son = grupo->FirstChildElement("group");
		cout << "processar filho " << son->Attribute("name") << endl;
		Modelos(son, temp);
	}
	//ver se tem irmaos
	if (grupo->NextSiblingElement("group")) {
		XMLElement *brotha = grupo->NextSiblingElement("group");
		cout << "processar irmao " << brotha->Attribute("name") << endl;
		Modelos(brotha, tdefault);
	}

}
void lXML(string nome) {
	
	XMLDocument docxml;
	cout << "A tentar ler  o ficheiro " << nome.c_str() << endl;
	
	int loadOkay = docxml.LoadFile(nome.c_str());
	if (!loadOkay)
	{
		cout << " A Ler o ficheiro " << nome.c_str() << endl;

		XMLElement* root = docxml.RootElement(); //guarda em root o primeiro filho (neste caso com nome especificado como "scene");
		XMLElement* elem;       //elem => elemento xml auxiliar para percorrer o documento (prзximo ciclo for)
		Transformation t = Transformation::Transformation(); // transformaçao 
		
		if (root != NULL) {
			cout << "A começar a desenhar ->  " << root->Attribute("name") << endl;
			Modelos(root->FirstChildElement("group"), t);  // manda o primeiro grupo para procurar os modelos 

		}
		
	}
	else cout << "Nao foi encontrado o xml "<< loadOkay << endl; // nao existe o ficheiro
}

void goVBO() {
	int n = ListaM.size();

	for (int i = 0; i < n; i++)
		ListaM[i].prep();


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
	sphericalToCartesian();
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

	//
	glewInit();
	goVBO();
	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}