#pragma once
typedef struct
{
	int zi;
	int suma;
	char* tip;
}cheltuiala;

cheltuiala formareCheltuiala(int zi, int suma, char* tip);
/*
* Formeaza o variabila de tip cheltuiala cu datele transmise
* Functia returneaza variabila formata
*/

cheltuiala copiereCheltuiala(cheltuiala c);
/*
* Copiaza datele cheltuielii
* Returneaza o cheltuiala cu date identice
*/

void distrugereCheltuiala(cheltuiala* c);
/*
* Elibereaza memoria de pe heap la cheltuiala
*/