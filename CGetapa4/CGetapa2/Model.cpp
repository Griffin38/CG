#include "Model.h"

Model::Model(string n) {
	nome = n;
}

void Model::adicionaPonto(Point p) {
	pontos.push_back(p);
}

void Model::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, nv);
}

void Model::prep() {
	int tpontos = pontos.size(), lados = tpontos / 3, j;
	buffer = (GLuint*)malloc(sizeof(GLuint)*tpontos * 3);

	nv = tpontos * 3;
	glEnableClientState(GL_VERTEX_ARRAY);

	float *vertexB = (float *)malloc(sizeof(float)* nv);

	j = 0;
	for (int i = 0; i<tpontos; i++) {
		Point xyz = pontos.at(i);

		vertexB[j + 0] = xyz.getX();
		vertexB[j + 1] = xyz.getY();
		vertexB[j + 2] = xyz.getZ();

		j += 3;
	}
	nv = j;

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, nv*sizeof(float), vertexB, GL_STATIC_DRAW);

	free(vertexB);
}
void Model::addFilho(Model m) {
	descendentes.push_back(m);
}
Model::~Model(void) {

}