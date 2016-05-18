#pragma once

#include <vector>
#include "Point.h"

using namespace std;

class Translate
{
	float time;
	vector<Point> tPontos;
	vector<Point> cPontos;
	int size;	
public:
	Translate();
	Translate(float);
	Translate(float, vector<Point>, int);
	int getSize() { return size; }
	float getTime() { return time; }
	vector<Point> getCurvas() { return cPontos; }
	vector<Point> getPontos() { return tPontos; }
	
	void setTime(float t) { time = t; }
	void Translate::getGlobalCatmullRomPoint(float, float *, vector<Point>);
	void Translate::fazCurvas();
	bool Translate::isEmpty();
	virtual ~Translate() {};
};

