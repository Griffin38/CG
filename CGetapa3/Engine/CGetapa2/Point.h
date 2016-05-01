#pragma once
class Point {
	double x;
	double y;
	double z;
public:
	Point(double, double, double);
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	virtual ~Point(void);
};

