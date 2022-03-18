#pragma once
#include "Cheltuiala.h"

typedef struct
{
	cheltuiala* element;
	int lungime;
	int capacitate;
} lista;

typedef int(*functieComparare)(cheltuiala* c1, cheltuiala* c2,int ordine);
/*
   Functie de comparare pentru 2 elemente
   Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/

lista initializareLista();
/*
* Formeaza o variabila de tip lista
* Functia returneaza variabila formata
*/

int getLungime(lista* l);
/*
* Returneaza lungimea listei spre care pointeaza l
*/

void adaugareInLista(lista* l, cheltuiala c);
/*
* Adauga in lista spre care pointeaza l cheltuiala c
*/

cheltuiala inlocuireInLista(lista* l, cheltuiala c, int pozitie);
/*
* Pune cheltuiala c pe pozitia data din lista spre care pointeaza l
* Returneaza elementul inlocuit
*/

cheltuiala eliminareDinLista(lista* l, int pozitie);
/*
* Elimina elementul de pe pozitia data din lista spre care pointeaza l
* Returneaza elementul eliminat
*/

int existaPozitie(int numar, lista* l);
/*
* Verifica daca exista pozitia data in lista spre care pointeaza l
* Returneaza:
  -1, daca nu exista
   0, daca exista
*/

void distrugereLista(lista* l);
/*
* Distruge lista
*/

lista filt_zi(int mod, int zi, lista* l);
/*
* Formeaza o noua variabila de tip lista care sa contina toate elementele din lista spre care pointeaza l
  care respecta modul dat referitor la zi
* Returneaza noua lista
*/

lista filt_suma(char mod, int suma, lista* l);
/*
* Formeaza o noua variabila de tip lista care sa contina toate elementele din lista spre care pointeaza l
  care respecta modul dat referitor la suma
* Returneaza noua lista
*/

lista filt_tip(char mod, char tip[], lista* l);
/*
* Formeaza o noua variabila de tip lista care sa contina toate elementele din lista spre care pointeaza l
  care respecta modul dat referitor la tip
* Returneaza noua lista
*/

int compSuma(cheltuiala* c1, cheltuiala* c2,int ordine);
/*
* Functie de comparare pentru sumele celor doua elemente
  Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/

int compTip(cheltuiala* c1, cheltuiala* c2,int ordine);
/*
* Functie de comparare pentru tipurile celor doua elemente
  Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/

lista sortareLista(lista* l, functieComparare fcomp,int ordine);
/*
* Formeaza o noua variabila de tip lista in care elementele din lista spre care pointeaza l sunt
  sortate dupa functia de comparare data si in ordinea data
* Returneaza noua lista
*/

cheltuiala obtinere(lista* l, int pozitie);
/*
* Returneaza cheltuiala de pe pozitia data
*/