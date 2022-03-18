#pragma once
#include "Domain.h"

int transformareStringNumar(char string[]);
/*
* Transforma valoarea din string intr-un numar
* Returneaza:
              -1, daca intalneste un caracter care nu reprezinta o cifra
  numarul format, daca toate caracterele sunt cifre
*/


void eliminareNewLine(char v[]);
/*
* Va inlocui caracterul '\n' din v cu '\0'
*/

int verificareDate(int zi, int suma, char tip[15]);
/*
* Determina daca datele sunt valide
*/

