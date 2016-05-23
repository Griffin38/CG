#pragma once
#include <GL\glew.h>
#include <GL\glut.h>
#include <IL\il.h>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Transformation.h"


using namespace std;

class Model {
	string nome;
	Transformation transf;
	GLuint buffer[3];
	int nv;
	vector<Model> descendentes;
	string imagem;
	unsigned int imag;
	unsigned int textID;
	unsigned char *imageData;
	float diffR, diffG, diffB;
public:
	Model(string);
	vector<Point> pontos;
	vector<Point> normas;
	vector<Point> texturas;
	string getNomeModelo() { return nome; }
	vector<Point> getPontos() { return pontos; }
	vector<Point> getNormas() { return normas; }
	vector<Point> getTexturas() { return texturas; }
	Transformation getTransformacao() { return transf; }
	unsigned int getTextID() { return textID; }
	float getdiffR() { return diffR; }
	float getdiffG() { return diffG; }
	float getdiffB() { return diffB; }
	void setTransformacao(Transformation t) { transf = t; }
	void Model::setDiffs(float dr, float dg, float db);
	void adicionaPonto(Point p);
	void adicionaNorma(Point p);
	void adicionaTextura(Point p);
	void setImagem(string s) {imagem = s;}
	vector<Model> getFilhos() { return descendentes; }
	void Model::addFilho(Model m);
	void setFilhos(vector<Model> d) { descendentes = d; }
	void Model::prep();
	void Model::draw();
	void Model::drawTeapot();
	void Model::prepTeapot();
	void Model::carregaImagem(string file);
	virtual ~Model(void);
};