#include "Scalate.h"


Scalate::Scalate() {
	x = 0;
	y = 0;
	z = 0;
	
}

Scalate::Scalate(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;

}


bool Scalate::isEmpty() {
	bool res = false;
	if (x == 0 && y == 0 && z == 0)
		res = true;

	return res;
}

Scalate::~Scalate(void)
{
}
