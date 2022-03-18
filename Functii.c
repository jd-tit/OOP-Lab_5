#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Domain.h"

void eliminareNewLine(char v[])
{
	//int i = 0;
	//while (v[i] != '\n' || i<strlen(v))
		//i++;
	//v[i] = '\0';
	v[strlen(v) - 1] = '\0';
}

int verificareDate(int zi, int suma, char tip[17])
{
	if (zi < 1 || zi>31)
		return -1;
	if (suma < 1)
		return -2;
	if (strcmp(tip,"mancare")!=0 && strcmp(tip, "transport")!=0 && strcmp(tip, "telefon&internet")!=0 && strcmp(tip, "imbracaminte")!=0 && strcmp(tip, "altele")!=0)
		return -3;
	return 0;
}

int transformareStringNumar(char string[])
{
	int numar = 0;
	for (int i = 0; i <= strlen(string) - 1; i++)
	{
		if (string[i] > 57 || string[i] < 48)
			return -1;
		else
			numar = numar * 10 + (string[i] - '0');
	}
	return numar;
}

