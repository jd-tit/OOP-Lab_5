#pragma once
typedef struct Cheltuiala
{
	int zi;
	int suma;
	char* tip;
}Cheltuiala;

Cheltuiala * formareCheltuiala(int zi, int suma, char* tip);
/*
* Formeaza o variabila de tip Cheltuiala cu datele transmise
* Functia returneaza variabila formata
*/

Cheltuiala * copiereCheltuiala(Cheltuiala *c);
/*
* Copiaza datele cheltuielii
* Returneaza o Cheltuiala cu date identice
*/

void distrugereCheltuiala(void* elem);
/*
* Elibereaza memoria de pe heap la Cheltuiala
*/