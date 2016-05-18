#include "Rotate.h"


Rotate::Rotate() {
	time = rx = ry = rz = 0;
}

Rotate::Rotate(float t, float x, float y, float z) {
	time = t;
	rx = x;
	ry = y;
	rz = z;
}

bool Rotate::isEmpty() {
	return (time == 0 && rx == 0 && ry == 0 && rz == 0) ? true : false;
}