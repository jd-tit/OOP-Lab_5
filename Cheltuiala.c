#include <string.h>
#include <stdlib.h>
#include "Cheltuiala.h"

Cheltuiala * formareCheltuiala(int zi, int suma, char* tip)
{
    Cheltuiala* c = malloc(sizeof(Cheltuiala));

	c->zi = zi;
	c->suma = suma;

	int alocare = (int)strlen(tip) + 1;
	c->tip = malloc(alocare * sizeof(char));
	strcpy(c->tip, tip);

	return c;
}

Cheltuiala * copiereCheltuiala(Cheltuiala *c)
{
	return formareCheltuiala(c->zi, c->suma, c->tip);
}

void distrugereCheltuiala(void* elem)
{
    Cheltuiala* c = elem;
	c->zi = -1;
	c->suma = -1;
	free(c->tip);
	free(elem);
}