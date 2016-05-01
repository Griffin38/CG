#pragma once
#include "Type.h"
#include "Scalate.h"
#include"Rotate.h"
#include"Translate.h"

class Transformation {
	Translate transl;
	Rotate rot;
	Scalate scale;
	Type color;

	// rotate  scalate translate
public:
	Transformation();
	Transformation(Translate, Rotate, Scalate,Type);
	Translate getTranslacao() { return transl; }
	Rotate getRotacao() { return rot; }
	Scalate getEscala() { return scale; }
	Type getCor() { return color; }
	void setTranslacao(Translate t) { transl = t; }
	void setCor(Type t) { color = t; }
	void setEscala(Scalate t) { scale = t; }
	void setRotacao(Rotate t) { rot = t; }
	
	bool trasnformacaoVazia();
	~Transformation(void);
}; 
