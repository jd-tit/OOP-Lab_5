#pragma once
#include "Lista.h"

void golireBuffer(lista* l);
/*
* Goleste buffer-ul a.i. sa se poata utiliza fgets
*/
void afisare_lista(lista* l);
/*
* Afiseaza lista
*/
int adaugareCheltuiala(lista* l);
/*
* Rezolva prima cerinta a programului
* Returneaza:
  -1, daca ziua este gresita
  -2, daca suma este gresita
  -3, daca tipul este gresit
   0, altfel
*/
int modificare_cheltuiala(lista* l);
/*
* Rezolva a doua cerinta a programului
* Returneaza:
  -1, daca ziua este gresita
  -2, daca suma este gresita
  -3, daca tipul este gresit
  -4, daca nu exista cheltuieli
  -5, daca nu exista pozitia data
   0, altfel
*/
int stergereCheltuiala(lista* l);
/*
* Rezolva a treia cerinta a programului
* Returneaza:
  -4, daca nu exista cheltuieli
  -5, daca nu exista pozitia data
   0, altfel
*/
int filtrare_zi(lista* l);
/*
* Rezolva a treia cerinta pentru filtrarea dupa zi
* Returneaza:
  -1, daca comanda este gresita
  -2, daca ziua data este gresita
  -3, daca nu exista cheltuieli cu proprietatea data
   0, altfel
*/
int filtrare_suma(lista* l);
/*
* Rezolva a treia cerinta pentru filtrarea dupa suma
* Returneaza:
  -1, daca comanda este gresita
  -2, daca suma data este gresita
  -3, daca nu exista cheltuieli cu proprietatea data
   0, altfel
*/
int filtrare_tip(lista* l);
/*
* Rezolva a treia cerinta pentru filtrarea dupa tip
* Returneaza:
  -1, daca comanda este gresita
  -2, daca tipul dat este gresit
  -3, daca nu exista cheltuieli cu proprietatea data
   0, altfel
*/
int filtrare(lista* l);
/*
* Rezolva a treia cerinta a programului
* Returneaza:
  -1, daca nu exista cheltuieli
  -2, daca proprietatea data este gresita
   0, altfel
*/
int sortare(lista* l);
/*
* Rezolva a patra cerinta a programului
* Returneaza:
  -1, daca nu exista cheltuieli
  -2, daca proprietatea data este gresita
  -3, daca ordinea data este gresita
   0, altfel
*/
void run();
/*
* Ruleaza programul
*/