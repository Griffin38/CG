#pragma once
#pragma once

#include<string>

using namespace std;

class Luz {
	string tipo;
	float posX;
	float posY;
	float posZ;
public:
	Luz();
	Luz(float x, float y, float z, string t);
	float getPosX() { return posX; }
	float getPosY() { return posY; }
	float getPosZ() { return posZ; }
	string getTipo() { return tipo; }
	void setPosX(float x) { posX = x; }
	void setPosY(float y) { posY = y; }
	void setPosZ(float z) { posZ = z; }
	void setTipo(string t) { tipo = t; }
	virtual ~Luz(void);
};

