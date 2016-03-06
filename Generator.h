#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void plano(int lado, string nome);
void caixa(int x, int y, int z, string nome);
void cone(int rr, int hr, int slice, int stack, string nome);
void esfera(int r, int slice, int stack, string nome);