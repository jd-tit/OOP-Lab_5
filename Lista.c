#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include <stdbool.h>

void initList(Lista* l, size_t elem_size, destructor element_destructor, copy_function copy)
{
    l->element_size = elem_size;
	l->elements = malloc(elem_size * INIT_MAX_SIZE);
	l->lungime = 0;
	l->capacitate = INIT_MAX_SIZE;
    l->destroy_element = element_destructor;
    l->copy = copy;
}

void* get_element(Lista* l, size_t index)
{
    char** res = l->elements + index * l->element_size;
	return *res;
}

void** get_pointer_to_position(Lista* l, size_t index){
    void** res = l->elements + index * l->element_size;
    return res;
}

size_t getLungime(Lista* l)
{
	return l->lungime;
}

int increase_size(Lista* l){

    void* aux = realloc(l->elements ,l->capacitate * l->element_size * RESIZE_FACTOR);
    if(aux == NULL){
        return ALLOC_ERROR;
    }
    l->capacitate *= RESIZE_FACTOR;
    l->elements = aux;
    return EXIT_SUCCESS;
}

Lista* copyLista(Lista* original){
    Lista* copy = malloc(sizeof(Lista));
    initList(copy, original->element_size, original->destroy_element, original->copy);
    for(size_t i = 0; i < original->lungime; ++i){
        void* elem = original->copy(get_element(original, i));
        push_back(copy, elem);
    }
    return copy;
}

void push_back(Lista* l, void* elem)
{
    if(l->lungime >= l->capacitate -1){
        increase_size(l);
    }
    char* dest = l->elements + l->lungime * l->element_size;
    memcpy(dest, &elem, l->element_size);
	l->lungime++;
}

void inlocuireInLista(Lista* l, void* elem, size_t index)
{
    l->destroy_element(get_element(l, index));
    void** dest = get_pointer_to_position(l, index);
    memcpy(dest, &elem, l->element_size);
}

Cheltuiala eliminareDinLista(Lista *l, size_t index)
{
	void* last = get_element(l, l->lungime);
    void* target = get_element(l, index);
    l->destroy_element(target);
    memcpy(&target, &last, l->element_size);
	l->lungime--;
}

bool existaPozitie(int numar, Lista* l)
{
	if (numar > l->lungime-1 || numar < 0)
		return false;
	return true;
}

void distrugereLista(Lista *l)
{
	for (int i = 0; i < l->lungime; i++)
	{
		char* elem = get_element(l, i);
        l->destroy_element(elem);
	}
	l->lungime = 0;
	free(l->elements);
    l->elements = NULL;
    free(l);
    l = NULL;
}

Lista * filt_zi(int mod, int zi, Lista* l)
{
    Lista* filtrare = malloc(sizeof(Lista));
    initList(filtrare, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			Cheltuiala* c = (Cheltuiala*) get_element(l, i);
			if (c->zi <= zi) {
                Cheltuiala* new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
		}
	}
	if (mod == '2')
	{
		for (int i = 0; i < l->lungime; i++)
		{
            Cheltuiala* c = (Cheltuiala*) get_element(l, i);
            if (c->zi == zi) {
                Cheltuiala* new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
		}
	}
	if (mod == '3')
	{
		for (int i = 0; i < l->lungime; i++)
		{
            Cheltuiala* c = (Cheltuiala*) get_element(l, i);
            if (c->zi > zi) {
                Cheltuiala* new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
		}
	}
	return filtrare;
}

Lista * filt_suma(char mod, int suma, Lista* l)
{
    Lista* filtrare = malloc(sizeof(Lista));
    initList(filtrare, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			Cheltuiala* c = get_element(l, i);
			if (c->suma < suma) {
                Cheltuiala* new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
		}
		return filtrare;
	} else if (mod == '2')
	{
        for (int i = 0; i < l->lungime; i++)
        {
            Cheltuiala* c = get_element(l, i);
            if (c->suma == suma) {
                Cheltuiala* new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
        }
		return filtrare;
	} else if (mod == '3') {
        for (int i = 0; i < l->lungime; i++)
        {
            Cheltuiala* c = get_element(l, i);
            if (c->suma > suma) {
                Cheltuiala *new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
        }
    }
    return filtrare;
}

Lista * filt_tip(char mod, char tip[], Lista* l)
{
    Lista* filtrare = malloc(sizeof(Lista));
    initList(filtrare, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			Cheltuiala* c = get_element(l, i);
			if (strcmp(c->tip, tip) == 0) {
                Cheltuiala *new_c = formareCheltuiala(c->zi, c->suma, c->tip);
                push_back(filtrare, new_c);
            }
		}
	}
	else
	{
		for (int i = 0; i < l->lungime; i++)
		{
			Cheltuiala* c = get_element(l, i);
			if (strcmp(c->tip, tip) != 0)
                push_back(filtrare, formareCheltuiala(c->zi, c->suma, c->tip));
		}
	}
	return filtrare;
}

int compSuma(Cheltuiala* c1, Cheltuiala* c2, int ordine)
{
	if (c1->suma == c2->suma)
		return 0;
	if (c1->suma > c2->suma)
		return 1*ordine;
	return (-1)*ordine;
}

int compTip(Cheltuiala* c1, Cheltuiala* c2, int ordine)
{
	if (strcmp(c1->tip, c2->tip) == 0)
		return 0;
	if (strcmp(c1->tip, c2->tip) > 0)
		return 1 * ordine;
	return (-1) * ordine;
}

Lista* sortareLista(Lista* l, functieComparare cmp_function, int ordine)
{
    Lista* sorted;
    sorted = copyLista(l);
    void* aux;

    for (int i = 0; i < sorted->lungime - 1; i++)
        for (int j = i + 1; j < sorted->lungime; j++)
            if (cmp_function(get_element(sorted, i), get_element(sorted, j), ordine) == 1)
            {
                memcpy(&aux, get_pointer_to_position(sorted, i), sorted->element_size);
                memcpy(get_pointer_to_position(sorted, i), get_pointer_to_position(sorted, j), sorted->element_size);
                memcpy(get_pointer_to_position(sorted, j), &aux, sorted->element_size);
            }
    return sorted;
}