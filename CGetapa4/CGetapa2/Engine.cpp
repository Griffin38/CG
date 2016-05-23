﻿#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include"Type.h"
#include"Transformation.h"
#include"Point.h"
#include"Model.h"
#include"Luz.h"

#pragma comment(lib, "DevIL.lib")

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
Luz luz;
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

	
	gluLookAt(camX, camY, camZ,
		posX, posY, posZ,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xx, yy, zz);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	int n_models = ListaM.size();
	GLfloat lx, ly, lz,dr, dg, db;
	lx = luz.getPosX(); ly = luz.getPosY(); lz = luz.getPosZ();


	for (int i = 0; i < n_models; i++) {

		Model mod = ListaM[i];
		float res[3];
		dr = mod.getdiffR(); dg = mod.getdiffG(); db = mod.getdiffB();
		if (i == 0) {

			GLfloat pos[4] = { lx, ly, lz, 7 };
			GLfloat amb[3] = { 1.0, 1.0, 1.0 };
			GLfloat diff[3] = { dr, dg, db };
			GLfloat matt[3] = { 1, 1, 1 };

			glLightfv(GL_LIGHT0, GL_POSITION, pos); // posição da luz
			glLightfv(GL_LIGHT0, GL_AMBIENT, amb); // cores da luz
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); // cores da luz

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matt);
		}
		else {
			GLfloat diff[3] = { dr, dg, db };
			GLfloat matt[3] = { 0, 0, 0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matt);
		}

		
		

		Transformation tr = ListaM[i].getTransformacao();
		glPushMatrix();
		if (!tr.trasnformacaoVazia()) {
		
			Rotate r = tr.getRotacao();
			if (!r.isEmpty() && r.getTime() != 0) {
				float t = glutGet(GLUT_ELAPSED_TIME) % (int)(r.getTime() * 1000);
				float gr = (t * 360) / (r.getTime() * 1000);

				glRotatef(gr, r.getX(), r.getY(), r.getZ());
			}


			Translate t = tr.getTranslacao();
			if (!t.isEmpty()) {

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

		/*****/

		if (ListaM[i].getFilhos().size() != 0) {
			vector<Model> filhos = ListaM[i].getFilhos();
			for (int k = 0; k < filhos.size(); k++) {
				Transformation tfilho = filhos[k].getTransformacao();
				glPushMatrix();
				if (!tfilho.trasnformacaoVazia()) {
					
					Translate trans = tfilho.getTranslacao();
					if (!trans.isEmpty()) {
						int tam = trans.getSize();
						if (tam > 0) {
							float te = glutGet(GLUT_ELAPSED_TIME) % (int)(trans.getTime() * 1000);
							float gt = te / (trans.getTime() * 1000);
							vector<Point> vpt = trans.getPontos();
							renderCatmullRomCurve(trans.getCurvas());
							trans.getGlobalCatmullRomPoint(gt, res, vpt);
							glTranslatef(res[0], res[1], res[2]);

						}
					}

					Rotate rot = tfilho.getRotacao();
					if (!rot.isEmpty()) {
						float r = glutGet(GLUT_ELAPSED_TIME) % (int)(rot.getTime() * 1000);
						float gr = (r * 360) / (rot.getTime() * 1000);
						glRotatef(gr, rot.getX(), rot.getY(), rot.getZ());
					}

					Scalate esc = tfilho.getEscala();
					if (!esc.isEmpty()) {
						glScalef(esc.getX(), esc.getY(), esc.getZ());
					}
				}


				glBindTexture(GL_TEXTURE_2D, filhos[k].getTextID());
				glEnable(GL_LIGHTING);
				filhos[k].draw();
				glDisable(GL_LIGHTING);
				glBindTexture(GL_TEXTURE_2D, 0);

				/**********/

				glPopMatrix();
			}
		}
		if (mod.getNomeModelo().compare("Cometa") == 0) {
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			mod.drawTeapot();
		}else{
		glBindTexture(GL_TEXTURE_2D, mod.getTextID());
		glEnable(GL_LIGHTING);
		mod.draw();
		glDisable(GL_LIGHTING);
			
		glBindTexture(GL_TEXTURE_2D, 0);
		}
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
	string line, saux, delimiter  = ",",separator = "@";
	ifstream file(nome);
	int iaux,sep,niv = 0;
	float x, y, z;

	if (file.is_open()) {
		while (getline(file, line)) {

			sep = line.find(separator);
			if (!sep) {
				niv++;
			}
			else {
				iaux = line.find(delimiter);
				saux = line.substr(0, iaux);
				x = atof(saux.c_str());
				line.erase(0, iaux + delimiter.length());


				iaux = line.find(delimiter);
				saux = line.substr(0, iaux);
				y = atof(saux.c_str());
				line.erase(0, iaux + delimiter.length());

if(niv < 2 ){
				iaux = line.find(delimiter);
				saux = line.substr(0, iaux);
				z = atof(saux.c_str());
				line.erase(0, iaux + delimiter.length());


				Point po(x, y, z);
				if (!niv) {
					m.adicionaPonto(po);
				}
				else m.adicionaNorma(po);
}
else { Point po(x, y, 0);  m.adicionaTextura(po); }


				
			}
		
			
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

Model Modelos(XMLElement* grupo, Transformation tdefault) {
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

			
			rN = Rotate::Rotate(tt2, tx, ty , tz );
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
			/*	Translate tt = tdefault.getTranslacao();
				if (!tt.isEmpty()) {
					tx = tx + tt.getPontos().at(i).getX();
					ty = ty + tt.getPontos().at(i).getY();
					tz = tz + tt.getPontos().at(i).getZ();



					i++;
				}*/
				
				
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
	Model m(grupo->Attribute("name"));
	
	for (XMLElement* modelo = grupo->FirstChildElement("models")->FirstChildElement("model"); modelo; modelo = modelo->NextSiblingElement("model")) {
		
		if (leituraM(modelo->Attribute("file"), m)) {
			m.setImagem(modelo->Attribute("texture"));
			float dr = 1, dg = 1, db = 1;
			if (modelo->Attribute("diffR")) {
				dr = stof(modelo->Attribute("diffR"));
			}
			if (modelo->Attribute("diffG")) {
				dg = stof(modelo->Attribute("diffG"));
			}
			if (modelo->Attribute("diffB")) {
				db = stof(modelo->Attribute("diffB"));
			}
			m.setDiffs(dr, dg, db);
			//escrever os modelos
			m.setTransformacao(temp);
			
	
			
		}
	}
	

	return m;




}

void addFilhos(XMLElement* grupo, Model& m) {
	if (grupo) {
	Transformation t = m.getTransformacao();
	if (t.trasnformacaoVazia()) cout << "sl fodido" << endl; 
	Model p = Modelos(grupo, t);

	if (grupo->FirstChildElement("group")) {

		XMLElement *son = grupo->FirstChildElement("group");
		cout << "processar filho df " << son->Attribute("name") << endl;

		addFilhos(son, p);

	}
	m.addFilho(p);

	if (grupo->NextSiblingElement("group")) {
		XMLElement *brotha = grupo->NextSiblingElement("group");
		cout << "processar irmao df " << brotha->Attribute("name") << endl;
		addFilhos(brotha, m);
	}
}
}
void ModelosAll(XMLElement* grupo,Transformation t) {

	
/************************************************************************/
	if (grupo) {
		Model m = Modelos(grupo, t);



		//ver se tem mais filhos
		if (grupo->FirstChildElement("group")) {

			XMLElement *son = grupo->FirstChildElement("group");
			cout << "processar filho " << son->Attribute("name") << endl;

			addFilhos(son, m);

		}
		ListaM.push_back(m);
		//ver se tem irmaos
		if (grupo->NextSiblingElement("group")) {
			XMLElement *brotha = grupo->NextSiblingElement("group");
			cout << "processar irmao " << brotha->Attribute("name") << endl;
			ModelosAll(brotha, t);
		}
	}
	/************************************************************************/
}

void lXML(string nome) {
	
	XMLDocument docxml;
	cout << "A tentar ler  o ficheiro " << nome.c_str() << endl;
	
	int loadOkay = docxml.LoadFile(nome.c_str());
	if (!loadOkay)
	{
		cout << " A Ler o ficheiro " << nome.c_str() << endl;

		XMLElement* root = docxml.RootElement(); //guarda em root o primeiro filho (neste caso com nome especificado como "scene");
		Transformation t = Transformation::Transformation(); // transformaçao 
		
		
		if (root != NULL) {

			XMLElement* luzes =root->FirstChildElement("luz");
			if (luzes != NULL) {
				XMLElement* l = luzes->FirstChildElement("light");
				string tipo = "POINT";
				float x = 0, y = 0, z = 0;
				if (l->Attribute("tipo")) { tipo = l->Attribute("tipo"); }
				if (l->Attribute("posX")) { x = stof(l->Attribute("posX")); }
				if (l->Attribute("posY")) { y = stof(l->Attribute("posY")); }
				if (l->Attribute("posZ")) { z = stof(l->Attribute("posZ")); }

				luz = Luz::Luz(x, y, z, tipo);
			}
			else {
				luz = Luz::Luz(0, 0, 0, "POINT");
			}
			cout << "A começar a desenhar ->  " << root->Attribute("name") << endl;
			ModelosAll(root->FirstChildElement("group"),t);  // manda o primeiro grupo para procurar os modelos 

		}
		
	}
	else cout << "Nao foi encontrado o xml "<< loadOkay << endl; // nao existe o ficheiro
}

	


void goVBO() {
	int n = ListaM.size();

	

	for (int i = 0; i < n; i++) {

			if (ListaM[i].getFilhos().size() != 0) {
			cout << "whhhat" << endl;
			vector<Model> filhos = ListaM[i].getFilhos();

			for (int j = 0; j < filhos.size(); j++) {

				filhos[j].prep();
			}
			ListaM[i].setFilhos(filhos);
		}
		cout << "A iniciar VBO de: " << ListaM[i].getNomeModelo() << endl;
		if (ListaM[i].getNomeModelo().compare("Cometa") == 0) {
			ListaM[i].prepTeapot();
		}
		else {
			ListaM[i].prep();
		}
		
		
	}
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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glew, Il e VBO
	ilInit();
	glewInit();
	goVBO();
	
	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}