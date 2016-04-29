#pragma once
class Rotate
{
	float time;
	float rx;
	float ry;
	float rz;
public:
	Rotate();
	Rotate(float, float, float, float);
	float getX() { return rx; }
	float getY() { return ry; }
	float getZ() { return rz; }
	float getTime() { return time; }
	bool Rotate::isEmpty();
	virtual ~Rotate() {};
};