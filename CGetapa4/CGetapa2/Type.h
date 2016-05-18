#pragma once
class Type {
	float r;
	float g;
	float b;
	
public:
	Type();
	Type(float, float, float);
	float getTX() { return r; }
	float getTY() { return g; }
	float getTZ() { return b; }

	bool isEmpty();
	~Type(void);
};


