#include "Model.h"
#include <GL\glew.h>
#include <IL\il.h>
Model::Model(string n) {
	nome = n;
}

void Model::adicionaPonto(Point p) {
	pontos.push_back(p);
}
void Model::adicionaNorma(Point p) {
	normas.push_back(p);
}
void Model::adicionaTextura(Point p) {
	texturas.push_back(p);
}
void Model::draw() {
	



	//triangulos
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	//normais
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	//Texturas
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nv);
}

void Model::carregaImagem(string file) {

	string path = "texts/" + file;
	
		ilGenImages(1, &imag);
	
	ilBindImage(imag);
	
	
	ilLoadImage((ILstring)path.c_str());
	
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	imageData = ilGetData();
	
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}
void Model::prep() {
	int tpontos = pontos.size(), lados = tpontos / 3, j,j2;
	nv = tpontos * 3;
	
	buffer[0] = (GLuint)malloc(sizeof(GLuint)*nv);
	buffer[1] = (GLuint)malloc(sizeof(GLuint)*nv);
	buffer[2] = (GLuint)malloc(sizeof(GLuint)*tpontos * 2);
	

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	float *vertexB = (float *)malloc(sizeof(float)* nv);
	float *normalB = (float *)malloc(sizeof(float)* nv);
	float *textureB = (float *)malloc(sizeof(float)* tpontos * 2);


	j = 0; j2 = 0;
	for (int i = 0; i<tpontos; i++) {

		Point xyz = pontos.at(i);
		Point norm = normas.at(i);
		Point text = texturas.at(i);

		vertexB[j] = xyz.getX();
		vertexB[j + 1] = xyz.getY();
		vertexB[j + 2] = xyz.getZ();
	
	//	cout << "pontos " << xyz.getX() << " " << xyz.getY() << " " << xyz.getZ() <<endl;
		normalB[j ] = norm.getX();
		normalB[j + 1] = norm.getY();
		normalB[j + 2] = norm.getZ();
		//cout << "normas " << norm.getX() << " " << norm.getY() << " " << norm.getZ() << endl;
		textureB[j2 ] = text.getX();
		textureB[j2 + 1] = text.getY();
		//cout << "texturas " << text.getX() << " " << text.getY() << " " << text.getZ() << endl;
		j += 3;
		j2 += 2;
		
	}
	nv = j;
	int dos = j2;

	
	glGenBuffers(3, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);	//triangulos
	glBufferData(GL_ARRAY_BUFFER, nv*sizeof(float), vertexB, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]); //normais
	glBufferData(GL_ARRAY_BUFFER, nv*sizeof(float), normalB, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]); //texturas
	glBufferData(GL_ARRAY_BUFFER, dos*sizeof(float), textureB, GL_STATIC_DRAW);

	free(vertexB);
	free(textureB);
	free(normalB);

	carregaImagem(imagem);

	
}
void Model::addFilho(Model m) {
	descendentes.push_back(m);
}
Model::~Model(void) {

}