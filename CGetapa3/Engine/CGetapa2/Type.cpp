#include "Type.h"


Type::Type() {
	r = 0;
	g = 0;
	b = 0;
	
	
}

Type::Type(float xx, float yy, float zz) {
	r = xx;
	g = yy;
	b = zz;
	
	
}


bool Type::isEmpty() {
	bool res = false;
	if (r == 0 && g == 0 && b == 0 )
		res = true;

	return res;
}

Type::~Type(void)
{
}
