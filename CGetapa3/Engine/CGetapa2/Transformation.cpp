#include "Transformation.h"

Transformation::Transformation() {
	float x = 1;
	transl = Translate::Translate();
	rot = Rotate::Rotate();
	scale = Scalate::Scalate(x,x,x);
	color = Type::Type();
}

Transformation::Transformation(Translate t, Rotate r, Scalate e,Type f) {
	transl = t;
	rot = r;
	scale = e;
	color = f;
}

bool Transformation::trasnformacaoVazia() {
	bool res = false;
	if (transl.isEmpty() && rot.isEmpty() && scale.isEmpty() & color.isEmpty())
		res = true;

	return res;
}

Transformation::~Transformation(void)
{
}
