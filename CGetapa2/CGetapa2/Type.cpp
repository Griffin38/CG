#include "Type.h"


Type::Type() {
	x = 0;
	y = 0;
	z = 0;
	ang = 0;
}

Type::Type(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	ang = 0;
}

Type::Type(float a, float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	ang = a;
}

bool Type::tipoVazio() {
	bool res = false;
	if (x == 0 && y == 0 && z == 0 && ang == 0)
		res = true;

	return res;
}

Type::~Type(void)
{
}
