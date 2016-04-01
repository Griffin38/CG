#pragma once
class Type {
	float x;
	float y;
	float z;
	float ang;
public:
	Type();
	Type(float, float, float);
	Type(float, float, float, float);
	float getTX() { return x; }
	float getTY() { return y; }
	float getTZ() { return z; }
	float getTAng() { return ang; }
	bool tipoVazio();
	~Type(void);
};


