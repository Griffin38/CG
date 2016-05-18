#include "Translate.h"

Translate::Translate() {
	time = 0;
}

Translate::Translate(float t) {
	time = t;
}

Translate::Translate(float f, vector<Point> p, int n) {
	time = f;
	tPontos = p;
	size = n;
}

bool Translate::isEmpty() {
	return (time == 0 && tPontos.size() == 0) ? true : false;
}

void getCatmullRomPoint(float t, int *indices, float *res, vector<Point> pontos) {
	float resAux[4];

	float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
	{ 1.0f, -2.5f,  2.0f, -0.5f },
	{ -0.5f,  0.0f,  0.5f,  0.0f },
	{ 0.0f,  1.0f,  0.0f,  0.0f }
	};

	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
	float t3 = t*t*t, t2 = t*t;

	//T*M
	resAux[0] = t3*m[0][0] + t2*m[1][0] + t*m[2][0] + m[3][0];
	resAux[1] = t3*m[0][1] + t2*m[1][1] + t*m[2][1] + m[3][1];
	resAux[2] = t3*m[0][2] + t2*m[1][2] + t*m[2][2] + m[3][2];
	resAux[3] = t3*m[0][3] + t2*m[1][3] + t*m[2][3] + m[3][3];

	int i0 = indices[0]; Point p0 = pontos[i0];
	int i1 = indices[1]; Point p1 = pontos[i1];
	int i2 = indices[2]; Point p2 = pontos[i2];
	int i3 = indices[3]; Point p3 = pontos[i3];

	//T*M*P = res
	res[0] = resAux[0] * p0.getX() + resAux[1] * p1.getX() + resAux[2] * p2.getX() + resAux[3] * p3.getX();
	res[1] = resAux[0] * p0.getY() + resAux[1] * p1.getY() + resAux[2] * p2.getY() + resAux[3] * p3.getY();
	res[2] = resAux[0] * p0.getZ() + resAux[1] * p1.getZ() + resAux[2] * p2.getZ() + resAux[3] * p3.getZ();
}

void Translate::getGlobalCatmullRomPoint(float gt, float *res, vector<Point> pontos) {
	int tamanho = pontos.size();
	float t = gt * tamanho; 
	int index = (int)t;  
	t = t - index; 

				  
	int indices[4];
	indices[0] = (index + tamanho - 1) % tamanho;
	indices[1] = (indices[0] + 1) % tamanho;
	indices[2] = (indices[1] + 1) % tamanho;
	indices[3] = (indices[2] + 1) % tamanho;

	getCatmullRomPoint(t, indices, res, pontos);
}

void Translate::fazCurvas() {
	float res[3];

	for (float gt = 0; gt<1; gt += (float)0.01) {
		getGlobalCatmullRomPoint(gt, res, tPontos);

		Point p = Point::Point(res[0], res[1], res[2]);
		cPontos.push_back(p);
	}
}