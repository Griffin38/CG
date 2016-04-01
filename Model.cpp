#include "Model.h"

Model::Model(string n) {
	nome = n;
}

void Model::adicionaPonto(Point p) {
	pontos.push_back(p);
}

Model::~Model(void)
{
}
