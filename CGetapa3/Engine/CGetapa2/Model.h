#pragma once
#include <gl/glew.h>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Transformation.h"


using namespace std;

class Model {
	string nome;
	Transformation transf;
	GLuint *buffer;
	int nv;
	vector<Model> descendentes;
public:
	Model(string);
	vector<Point> pontos;
	string getNomeModelo() { return nome; }
	vector<Point> getPontos() { return pontos; }
	Transformation getTransformacao() { return transf; }
	void setTransformacao(Transformation t) { transf = t; }
	void adicionaPonto(Point p);
	vector<Model> getFilhos() { return descendentes; }
	void Model::addFilho(Model m);
	void setFilhos(vector<Model> d) { descendentes = d; }
	void Model::prep();
	void Model::draw();
	
	virtual ~Model(void);
};