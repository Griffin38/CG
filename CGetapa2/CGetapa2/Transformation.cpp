#include "Transformation.h"

Transformation::Transformation() {
	transl = Type::Type();
	rot = Type::Type();
	scale = Type::Type(1,1,1,1);
	color = Type::Type();
}

Transformation::Transformation(Type t, Type r, Type e,Type f) {
	transl = t;
	rot = r;
	scale = e;
	color = f;
}

bool Transformation::trasnformacaoVazia() {
	bool res = false;
	if (transl.tipoVazio() && rot.tipoVazio() && scale.tipoVazio() & color.tipoVazio())
		res = true;

	return res;
}

Transformation::~Transformation(void)
{
}
