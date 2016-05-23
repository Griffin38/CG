#include "Luz.h"

Luz::Luz() {
	posX = 0;
	posY = 0;
	posZ = 0;
	tipo = "";
}

Luz::Luz(float x, float y, float z, string t) {
	posX = x;
	posY = y;
	posZ = z;
	tipo = t;
}

Luz::~Luz(void) {

}