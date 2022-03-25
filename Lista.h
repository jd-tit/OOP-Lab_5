#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "Cheltuiala.h"
#include "errors.h"

#define RESIZE_FACTOR 2
#define INIT_MAX_SIZE 2

typedef void (*destructor)(void* elem);
typedef void* (*copy_function)(void*);

typedef struct Lista
{
	void* elements;
    size_t element_size;
    size_t lungime;
    size_t capacitate;
    copy_function copy;
    destructor destroy_element;
} Lista;


/**
 * Copy a list.
 * @param original - the list to be copied
 * @return The copy of the given list.
 */
Lista* copyLista(Lista* original);


/*
   Functie de comparare pentru 2 elemente
   Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/
typedef int(*functieComparare)(Cheltuiala* c1, Cheltuiala* c2, int ordine);

/*
* Formeaza o variabila de tip Lista
* Functia returneaza variabila formata
*/
void initList(Lista* list, size_t elem_size, destructor element_destructor, copy_function copy);



/*
* Returneaza lungimea listei spre care pointeaza l
*/
size_t getLungime(Lista* l);


/*
* Adauga in Lista spre care pointeaza l elementul dat
*/
void push_back(Lista* l, void* elem);


/*
* Pune Cheltuiala c pe pozitia data din Lista spre care pointeaza l
* Returneaza elementul inlocuit
*/
void inlocuireInLista(Lista* l, void* elem, size_t index);


/*
* Elimina elementul de pe pozitia data din Lista spre care pointeaza l
* Returneaza elementul eliminat
*/
Cheltuiala eliminareDinLista(Lista *l, size_t index);


/*
* Verifica daca exista pozitia data in Lista spre care pointeaza l
* Returneaza:
  -1, daca nu exista
   0, daca exista
*/
bool existaPozitie(int numar, Lista* l);


/*
* Distruge Lista
*/
void distrugereLista(Lista *l);


/*
* Formeaza o noua variabila de tip Lista care sa contina toate elementele din Lista spre care pointeaza l
  care respecta modul dat referitor la zi
* Returneaza noua Lista
*/
Lista * filt_zi(int mod, int zi, Lista* l);

/*
* Formeaza o noua variabila de tip Lista care sa contina toate elementele din Lista spre care pointeaza l
  care respecta modul dat referitor la suma
* Returneaza noua Lista
*/
Lista * filt_suma(char mod, int suma, Lista* l);


/*
* Formeaza o noua variabila de tip Lista care sa contina toate elementele din Lista spre care pointeaza l
  care respecta modul dat referitor la tip
* Returneaza noua Lista
*/
Lista * filt_tip(char mod, char tip[], Lista* l);


/*
* Functie de comparare pentru sumele celor doua elemente
  Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/
int compSuma(Cheltuiala* c1, Cheltuiala* c2, int ordine);


/*
* Functie de comparare pentru tipurile celor doua elemente
  Returneaza:
	0, daca sunt egale
	1, daca c1>c2
   -1, altfel
*/
int compTip(Cheltuiala* c1, Cheltuiala* c2, int ordine);


/*
* Formează o nouă variabila de tip listă in care elementele din Lista spre care arată l sunt
  sortate după funcția de comparare dată și în ordinea dată
* Returnează noua Lista
*/
Lista* sortareLista(Lista* l, functieComparare cmp_function, int ordine);


/*
* Returnează Cheltuiala de pe poziția dată
*/
void* get_element(Lista* l, size_t index);


/**
 * Crește mărimea unei liste.
 * @param l - Lista de mărit
 * @return Codul de ieșire: ALLOC_ERROR sau EXIT_SUCCESS.
 * @post Dacă alocarea eșuează, pointerul `l` va rămâne valid și va arăta către aceeași zonă din memorie.
 */
int increase_size(Lista* l);