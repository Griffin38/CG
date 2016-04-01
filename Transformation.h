#pragma once
#include "Type.h"

class Transformation {
	Type transl;
	Type rot;
	Type scale;
public:
	Transformation();
	Transformation(Type, Type, Type);
	Type getTranslacao() { return transl; }
	Type getRotacao() { return rot; }
	Type getEscala() { return scale; }
	void setTranslacao(Type t) { transl = t; }
	void setRotacao(Type t) { rot = t; }
	void setEscala(Type t) { scale = t; }
	bool trasnformacaoVazia();
	~Transformation(void);
}; 
