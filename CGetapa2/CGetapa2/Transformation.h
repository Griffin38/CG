#pragma once
#include "Type.h"

class Transformation {
	Type transl;
	Type rot;
	Type scale;
	Type color;
public:
	Transformation();
	Transformation(Type, Type, Type,Type);
	Type getTranslacao() { return transl; }
	Type getRotacao() { return rot; }
	Type getEscala() { return scale; }
	Type getCor() { return color; }
	void setTranslacao(Type t) { transl = t; }
	void setCor(Type t) { color = t; }
	void setEscala(Type t) { scale = t; }
	void setRotacao(Type t) { rot = t; }
	
	bool trasnformacaoVazia();
	~Transformation(void);
}; 
