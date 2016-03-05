
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include<string>
#include <iostream>
#include <fstream>

using namespace std;




void plano(int lado,string nome) {

	ofstream file(nome);
	double x, y, z;
	y = 0;

	if (!(lado % 2))
		x = z = lado / 2;
	else x = z  =lado / 2 + 0.5;

	//1 triangulo
	printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z<< endl ;
	printf("%f %f %f\n", x, y, -z); file << x << "," << y << "," << -z << endl;
	printf("%f %f %f\n", -x, y, -z); file << -x << "," << y << "," << -z<<endl;
	//2 triangulo
	printf("%f %f %f\n", -x, y, z); file << -x << "," << y << "," << z<<endl;
	printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z<<endl;
	printf("%f %f %f\n", -x, y, -z); file << -x << "," << y << "," << -z<<endl;
	
	
	file.close();
}

void caixa(int x,int y , int z , string nome) {
	ofstream file(nome);
	double xx, yy, zz; 
	if (!(x % 2)) xx = x / 2; else xx = x / 2 + 0.5;
	if (!(y % 2)) yy = y / 2; else yy = y / 2 + 0.5;
	if (!(z % 2)) zz = z / 2; else zz = z / 2 + 0.5;
	
	//frente
	//1 triangulo
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, yy, zz); file << -xx << "," << yy << "," << zz << endl;

	
	//2 triangulo
	printf("%f %f %f\n", -xx, yy, -zz); file << -xx << "," << yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, -yy, zz); file << -xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << zz << endl;
	
	//tras
	//1 triangulo
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", xx, yy, zz); file << -xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, yy, zz); file << -xx << "," << yy << "," << -zz << endl;


	//2 triangulo
	printf("%f %f %f\n", -xx, yy, -zz); file << -xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, -yy, zz); file << xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << -zz << endl;
	
	
	//esquerda 
	//1 triangulo
	printf("%f %f %f\n", xx, -yy,-zz); file <<xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", xx, yy, -zz); file << xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", xx, yy, zz); file << xx << "," <<yy << "," << zz << endl;
	
	
	//2 triangulo
	printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << endl;
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n",xx, -yy,- zz); file << xx << "," << -yy << "," << -zz << endl;
	
	
	
	//direita
	//1 triangulo
	printf("%f %f %f\n", -xx, -yy, -zz); file << -xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, -yy, zz); file << -xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, yy, -zz); file << -xx << "," << yy << "," << -zz << endl;
	//2 triangulo
	printf("%f %f %f\n", -xx, -yy, zz); file << -xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, yy, zz); file << -xx << "," << yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, yy, -zz); file << -xx << "," << yy << "," << -zz << endl;

	
	

	
	
	//cima 
	//1 triangulo
	printf("%f %f %f\n", xx, yy, -zz); file << xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, yy, zz); file << -xx << "," << yy << "," << zz << endl;
	printf("%f %f %f\n", xx, yy, zz); file << xx << "," << yy << "," << zz << endl;
	//2 triangulo
	printf("%f %f %f\n", xx, yy, -zz); file << xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, yy, -zz); file << -xx << "," << yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, yy, zz); file << -xx << "," << yy << "," << zz << endl;

	
	//baixxo
	//1 triangulo
	printf("%f %f %f\n", xx, -yy, -zz); file << xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", xx, -yy, zz); file << xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, -yy, zz); file << -xx << "," << -yy << "," << zz << endl;

	//2 triangulo
	printf("%f %f %f\n", xx, -yy, -zz); file << xx << "," << -yy << "," << -zz << endl;
	printf("%f %f %f\n", -xx, -yy, zz); file << -xx << "," << -yy << "," << zz << endl;
	printf("%f %f %f\n", -xx, -yy, -zz); file << -xx << "," << -yy << "," << -zz << endl;
	
	

	file.close();
}


void cone(int r, int h, int slices, string nome) {
	ofstream file(nome);
	double alfa, alfa2;
	double xx, yy, zz;
	for (int i = 0; i < slices; i++) {			//CONE!!!!
		alfa = i*(2 * M_PI) / slices;
		alfa2 = (i + 1)*(2 * M_PI) / slices;
		yy = h / 2;
		file << 0.0f << "," << -yy << "," << 0.0f << endl;
		xx = r * (sin(alfa2));
		zz = r * cos(alfa2);
		file << xx << "," << -yy << "," << zz << endl;
		xx = r * (sin(alfa));
		zz = r * cos(alfa);

		file << xx << "," << -yy << "," << zz << endl;

		file << 0.0f << "," << yy << "," << 0.0f << endl;
		file << xx << "," << -yy << "," << zz << endl;
		xx = r * (sin(alfa2));
		zz = r * cos(alfa2);
		file << xx << "," << -yy << "," << zz << endl;
	
	}
	file.close();
}
void esfera(int r,int slice,int stack, string nome) {
	ofstream file(nome);

	double alfa, x, y, z;
	int flag = 0;
	double beta;
	for (int i = 0; i < stack; i++) {		//Esfera!!!
		for (int j = 0; j < slice; j++) {

			alfa = j*(2 * M_PI) / slice;
			beta = -M_PI / 2 + i* M_PI / slice;

			x = r*sin(alfa)*cos(beta);
			y = r*sin(beta);
			z = r * cos(alfa)*cos(beta);
	
			file << x << "," << y << "," << z << endl;
			x = r*sin(alfa + 2 * M_PI / slice)*cos(beta);
			
			z = r * cos(alfa + 2 * M_PI / slice)*cos(beta);
		
			file << x << "," << y << "," << z << endl;
			x = r*sin(alfa)*cos(beta + M_PI / slice);
			y = r*sin(beta + M_PI / slice);
			z = r * cos(alfa)*cos(beta + M_PI / slice);
			

			file << x << "," << y << "," << z << endl;
			x = r*sin(alfa + 2 * M_PI / slice)*cos(beta + M_PI / slice);
			z = r * cos(alfa + 2 * M_PI / slice)*cos(beta + M_PI / slice);
	

			file << x << "," << y << "," << z << endl;
			x = r*sin(alfa)*cos(beta + M_PI / slice);
			z = r * cos(alfa)*cos(beta + M_PI / slice);
			

			file << x << "," << y << "," << z << endl;
			x = r*sin(alfa + 2 * M_PI / slice)*cos(beta);
			y = r*sin(beta);
			z = r * cos(alfa + 2 * M_PI / slice)*cos(beta);
			

			file << x << "," << y << "," << z << endl;
		}
	}
	
	
	file.close();
}

int main(int argc, char **argv) {
	
	string str1("Sphere");
	string str2("Plane");
	string str3("Box");
	string str4("Cone");
	

	if (argc > 1) {
		
		if (!str1.compare(argv[1])) {
			printf(" faz uma %s  com %d raio  e %d fatias  e %d stacks chamada %s", argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
			esfera(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

		}
		else if (!str2.compare(argv[1])) {
			printf(" faz um %s  ", argv[1]);
			plano(atoi(argv[2]),argv[3]);
		}
		else if (!str3.compare(argv[1])) {
			printf(" faz uma %s  ", argv[1]);
			caixa(atoi(argv[2]), atoi(argv[3]),atoi( argv[4]), argv[5]);
		}
		else if (!str4.compare(argv[1])) {
			printf(" faz uma %s  com %d raio %d altura e %d fatias chamada %s", argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
			cone(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
		}
		else printf("Essa figura nao  possivel");
	}
	else printf("Nao ha argumentos suficientes");
	return 1;
}
