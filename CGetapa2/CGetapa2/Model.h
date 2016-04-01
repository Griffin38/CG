#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
#include "Transformation.h"

using namespace std;

class Model {
	string nome;
	Transformation transf;
public:
	Model(string);
	vector<Point> pontos;
	string getNomeModelo() { return nome; }
	vector<Point> getPontos() { return pontos; }
	Transformation getTransformacao() { return transf; }
	void setTransformacao(Transformation t) { transf = t; }
	void adicionaPonto(Point p);
	virtual ~Model(void);
};