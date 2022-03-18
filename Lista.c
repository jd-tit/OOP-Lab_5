#include <stdlib.h>
#include <string.h>
#include "Lista.h"

lista initializareLista()
{
	lista l;
	l.element = malloc(sizeof(cheltuiala) * 2);
	l.lungime = 0;
	l.capacitate = 2;
	return l;
}

cheltuiala obtinere(lista* l, int pozitie)
{
	return l->element[pozitie];
}

int getLungime(lista* l)
{
	return l->lungime;
}

void adaugareInLista(lista* l, cheltuiala c)
{
	if (l->lungime == l->capacitate)
	{
		l->capacitate *= 2;
		cheltuiala* aux = malloc(l->capacitate * sizeof(cheltuiala));
		for (int i = 0; i < l->lungime; i++)
		{
			aux[i] = l->element[i];
		}
		free(l->element);
		l->element = aux;
	}

	l->element[l->lungime] = c;
	l->lungime++;
}

cheltuiala inlocuireInLista(lista* l, cheltuiala c, int pozitie)
{
	cheltuiala C = l->element[pozitie];
	l->element[pozitie] = c;
	return C;
}

cheltuiala eliminareDinLista(lista* l, int pozitie)
{
	cheltuiala c = l->element[pozitie];
	for (int i = l->lungime-1; i > pozitie; i--)
		l->element[i - 1] = l->element[i];
	l->lungime--;
	return c;
}

int existaPozitie(int numar, lista* l)
{
	if (numar > l->lungime-1 || numar < 0)
		return -1;
	return 0;
}

void distrugereLista(lista* l)
{
	for (int i = 0; i < l->lungime; i++)
	{
		cheltuiala c = obtinere(l, i);
		distrugereCheltuiala(&c);
	}
	l->lungime = 0;
	free(l->element);
}

lista filt_zi(int mod, int zi, lista* l)
{
	lista filtrare = initializareLista();
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.zi <= zi)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	}
	if (mod == '2')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.zi == zi)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	}
	if (mod == '3')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.zi > zi)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	}
	return filtrare;
}

lista filt_suma(char mod, int suma, lista* l)
{
	lista filtrare = initializareLista();
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.suma < suma)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
		return filtrare;
	}
	if (mod == '2')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.suma == suma)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
		return filtrare;
	}
	for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (c.suma > suma)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	return filtrare;
}

lista filt_tip(char mod, char tip[], lista* l)
{
	lista filtrare = initializareLista();
	if (mod == '1')
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (strcmp(c.tip, tip) == 0)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	}
	else
	{
		for (int i = 0; i < l->lungime; i++)
		{
			cheltuiala c = obtinere(l, i);
			if (strcmp(c.tip, tip) != 0)
				adaugareInLista(&filtrare, formareCheltuiala(c.zi, c.suma, c.tip));
		}
	}
	return filtrare;
}

int compSuma(cheltuiala* c1, cheltuiala* c2,int ordine)
{
	if (c1->suma == c2->suma)
		return 0;
	if (c1->suma > c2->suma)
		return 1*ordine;
	return (-1)*ordine;
}

int compTip(cheltuiala* c1, cheltuiala* c2,int ordine)
{
	if (strcmp(c1->tip, c2->tip)== 0)
		return 0;
	if (strcmp(c1->tip, c2->tip) > 0)
		return 1*ordine;
	return (-1) * ordine;
}

lista sortareLista(lista* l,functieComparare fcomp,int ordine)
{
	lista sortare = initializareLista();
	for (int i = 0; i < l->lungime; i++)
	{
		cheltuiala c = obtinere(l, i);
		adaugareInLista(&sortare, formareCheltuiala(c.zi, c.suma, c.tip));
	}
	for (int i = 0; i < sortare.lungime - 1; i++)
			for (int j = i + 1; j < sortare.lungime; j++)
				if (fcomp(&(sortare.element[i]), &(sortare.element[j]), ordine)==1)
				{
					cheltuiala aux;
					aux = sortare.element[i];
					sortare.element[i] = sortare.element[j];
					sortare.element[j] = aux;
				}
	return sortare;
}