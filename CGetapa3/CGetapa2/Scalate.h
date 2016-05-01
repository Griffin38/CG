#pragma once
class Scalate {
	float x;
	float y;
	float z;
	
public:
	Scalate();
	Scalate(float, float, float);

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	
	bool isEmpty();
	~Scalate(void);
};
