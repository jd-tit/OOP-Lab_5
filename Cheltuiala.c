#include <string.h>
#include <stdlib.h>
#include "Cheltuiala.h"

cheltuiala formareCheltuiala(int zi, int suma, char* tip)
{
	cheltuiala c;

	c.zi = zi;
	c.suma = suma;

	int alocare = (int)strlen(tip) + 1;
	c.tip = malloc(alocare * sizeof(char));
	strcpy_s(c.tip, alocare, tip);

	return c;
}

cheltuiala copiereCheltuiala(cheltuiala c)
{
	return formareCheltuiala(c.zi, c.suma, c.tip);
}

void distrugereCheltuiala(cheltuiala* c)
{
	c->zi = -1;
	c->suma = -1;
	free(c->tip);
}