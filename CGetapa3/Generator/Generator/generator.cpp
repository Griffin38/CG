
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string>
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


void cone(int rr, int hr, int slice, int stack, string nome) {
	ofstream file(nome);
	float alfa;
	float r = rr, h = hr;
	float l = sqrt(pow(h, 2) + pow(r, 2)) / stack, t = r / stack;

	for (int i = 0; i < stack; i++) {		//CONE!!!
		for (int j = 0; j < slice; j++) {
			alfa = j*(2 * M_PI) / slice;
			if (i == 0) {
				file << 0.0f << "," << i*l << "," << 0.0f << endl;
				file << r * (sin(alfa + 2 * M_PI / slice)) << "," << i*l << "," << r * cos(alfa + 2 * M_PI / slice) << endl;
				file << r*(sin(alfa)) << "," << i*l << "," << r*cos(alfa) << endl;
			}
			if (i < stack - 1) {
				file << (r - ((i + 1)*t))*(sin(alfa + 2 * M_PI / slice)) << "," << (i + 1)*l << "," << (r - ((i + 1)*t))*cos(alfa + 2 * M_PI / slice) << endl;
				file << (r - ((i + 1)*t)) * (sin(alfa)) << "," << (i + 1)*l << "," << (r - ((i + 1)*t)) * cos(alfa) << endl;
				file << (r - (i*t)) * (sin(alfa)) << "," << i*l << "," << (r - (i*t)) * cos(alfa) << endl;

				file << (r - (i*t)) * (sin(alfa)) << "," << i*l << "," << (r - (i*t)) * cos(alfa) << endl;
				file << (r - (i*t))*(sin(alfa + 2 * M_PI / slice)) << "," << i*l << "," << (r - (i*t))*cos(alfa + 2 * M_PI / slice) << endl;
				file << (r - ((i + 1)*t))*(sin(alfa + 2 * M_PI / slice)) << "," << (i + 1)*l << "," << (r - ((i + 1)*t))*cos(alfa + 2 * M_PI / slice) << endl;
			}
			else {
				file << (r - (i*t)) * (sin(alfa)) << "," << i*l << "," << (r - (i*t)) * cos(alfa) << endl;
				file << (r - (i*t))*(sin(alfa + 2 * M_PI / slice)) << "," << i*l << "," << (r - (i*t))*cos(alfa + 2 * M_PI / slice) << endl;
				file << 0.0f << "," << (i + 1)*l << "," << 0.0f << endl;
			}
		}
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

float* calculaBezier(float t, float *p1, float *p2, float *p3, float *p4) {
	float it = 1.0 - t;
	float* res = new float[3];

	float b0 = pow(it, 3);
	float b1 = 3 * t*pow(it, 2);
	float b2 = 3 * t*t*it;
	float b3 = t*t*t;

	res[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
	res[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
	res[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];



	return res;
}

float* bezier(float u, float v, int* indice, float** pontos, int ni, int np) {
	float* ponto = new float[3];
	float bz[4][3], res[4][3];
	int i, j = 0, k = 0;

	for (i = 0; i < 16; i++) {
		bz[j][0] = pontos[indice[i]][0];
		bz[j][1] = pontos[indice[i]][1];
		bz[j][2] = pontos[indice[i]][2];

		j++;

		if (j % 4 == 0) {
			ponto = calculaBezier(u, bz[0], bz[1], bz[2], bz[3]);
			res[k][0] = ponto[0];
			res[k][1] = ponto[1];
			res[k][2] = ponto[2];

			k++;
			j = 0;
		}
	}
	return calculaBezier(v, res[0], res[1], res[2], res[3]);
}

void patch(string fich, int tess, string nome) {

	ofstream fileo(nome);
	string line, saux;
	ifstream filei(fich);
	int iaux;

	//leitura
	if (filei.is_open()) {
		getline(filei, line);
		int npatch = atoi(line.c_str());
		int** indices = new int*[npatch];
		cout << npatch << endl;
		for (int i = 0; i < npatch; i++) {
			getline(filei, line);
			indices[i] = new int[16];
			for (int j = 0; j < 16; j++) {
				iaux = line.find(",");
				saux = line.substr(0, iaux);
				indices[i][j] = atoi(saux.c_str());
				line.erase(0, iaux + 1);
			}
		}
		getline(filei, line);
		int npontos = atoi(line.c_str());
		cout << npontos << endl;
		float** pontos = new float*[npontos];
		for (int i = 0; i < npontos; i++) {
			getline(filei, line);
			pontos[i] = new float[3];
			for (int j = 0; j < 3; j++) {
				iaux = line.find(",");
				saux = line.substr(0, iaux);
				pontos[i][j] = atof(saux.c_str());
				line.erase(0, iaux + 1);				
			}
		}		

		//calculo
		float inc = 1.0 / tess, u, v, u2, v2;
		float*** pontoRes = new float**[npatch];
		for (int p = 0; p < npatch; p++) {
			pontoRes[p] = new float*[4];
			for (int i = 0; i < tess; i++) {
				for (int j = 0; j < tess; j++) {
					u = i*inc;
					v = j*inc;
					u2 = (i + 1)*inc;
					v2 = (j + 1)*inc;
					pontoRes[p][0] = bezier(u, v, indices[p], pontos, npatch, npontos);
					pontoRes[p][1] = bezier(u, v2, indices[p], pontos, npatch, npontos);
					pontoRes[p][2] = bezier(u2, v, indices[p], pontos, npatch, npontos);
					pontoRes[p][3] = bezier(u2, v2, indices[p], pontos, npatch, npontos);

					fileo << pontoRes[p][0][0] << "," << pontoRes[p][0][1] << "," << pontoRes[p][0][2] << endl;
					fileo << pontoRes[p][2][0] << "," << pontoRes[p][2][1] << "," << pontoRes[p][2][2] << endl;
					fileo << pontoRes[p][3][0] << "," << pontoRes[p][3][1] << "," << pontoRes[p][3][2] << endl;
 
					fileo << pontoRes[p][0][0] << "," << pontoRes[p][0][1] << "," << pontoRes[p][0][2] << endl;
					fileo << pontoRes[p][3][0] << "," << pontoRes[p][3][1] << "," << pontoRes[p][3][2] << endl;
					fileo << pontoRes[p][1][0] << "," << pontoRes[p][1][1] << "," << pontoRes[p][1][2] << endl;

				}
			}
		}
	}



	/*
	double x, y, z;
	y = 0;

	if (!(lado % 2))
		x = z = lado / 2;
	else x = z = lado / 2 + 0.5;

	//1 triangulo
	printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;
	printf("%f %f %f\n", x, y, -z); file << x << "," << y << "," << -z << endl;
	printf("%f %f %f\n", -x, y, -z); file << -x << "," << y << "," << -z << endl;
	//2 triangulo
	printf("%f %f %f\n", -x, y, z); file << -x << "," << y << "," << z << endl;
	printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;
	printf("%f %f %f\n", -x, y, -z); file << -x << "," << y << "," << -z << endl;
	*/

	filei.close();
	fileo.close();
}

int main(int argc, char **argv) {
	
	string str1("Sphere");
	string str2("Plane");
	string str3("Box");
	string str4("Cone");
	string str5("Patch");
	
	patch("teapot.patch", 5, "teapot.3d");

	/*
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
			printf(" faz uma %s  com %d raio %d altura %d stacks e %d fatias chamada %s", argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
			cone(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
		}
		else if (!str5.compare(argv[1])) {
			printf(" faz um modelo basiado nos patch de Bezier com tesselação de %d", atoi(argv[3]));
			patch(argv[2],atoi(argv[3]), argv[4]);
		}
		else printf("Essa figura nao  possivel");
	}
	else printf("Nao ha argumentos suficientes");*/
	return 1;
}