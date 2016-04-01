#include "Transformation.h"

Transformation::Transformation() {
	transl = Type::Type();
	rot = Type::Type();
	scale = Type::Type();
}

Transformation::Transformation(Type t, Type r, Type e) {
	transl = t;
	rot = r;
	scale = e;
}

bool Transformation::trasnformacaoVazia() {
	bool res = false;
	if (transl.tipoVazio() && rot.tipoVazio() && scale.tipoVazio())
		res = true;

	return res;
}

Transformation::~Transformation(void)
{
}
