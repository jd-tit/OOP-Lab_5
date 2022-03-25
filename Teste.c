#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "Lista.h"
#include "Functii.h"

void testEliminareNewLine()
{
	char v[10] = { 'a','l','t','e','l','e','\n' };
	eliminareNewLine(v);
	assert(strcmp(v,"altele")==0);
}

void testTransformareStringNumar()
{
	assert(transformareStringNumar("1000") == 1000);
	assert(transformareStringNumar("nu") == -1);
}

void testVerificareDate()
{
	assert(verificareDate(-1, 100, "altele") == -1);
	assert(verificareDate(32, 100, "altele") == -1);
	assert(verificareDate(1, 0, "altele") == -2);
	assert(verificareDate(1, 100, "cuvant") == -3);
	assert(verificareDate(1, 100, "Altele") == -3);
	assert(verificareDate(1, 100, "altele") == 0);
}

void testeFunctii()
{
	testEliminareNewLine();
	testTransformareStringNumar();
	testVerificareDate();
}

void testFormareCheltuiala()
{
	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
	assert(c->zi == 1);
	assert(c->suma == 1);
	assert(strcmp(c->tip, "altele") == 0);
	distrugereCheltuiala(c);
}

void testDistrugereCheltuiala()
{
	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
	distrugereCheltuiala(c);
}

void testCopiereCheltuiala()
{
	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
	Cheltuiala* copie = copiereCheltuiala(c);
    assert(c->zi == copie->zi);
	assert(c->suma == copie->suma);
	assert(strcmp(c->tip, copie->tip)==0);
	distrugereCheltuiala(c);
	distrugereCheltuiala(copie);
}

void testeCheltuiala()
{
	testFormareCheltuiala();
	testDistrugereCheltuiala();
	testCopiereCheltuiala();
}

void testIntializareLista()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	assert(test->lungime == 0);
	assert(test->capacitate == INIT_MAX_SIZE);
    distrugereLista(test);
}

void testGetLungime()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	assert(getLungime(test) == 0);
    distrugereLista(test);
}

void testAdaugareInLista()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
    push_back(test, c);
	assert(getLungime(test) == 1);
    Cheltuiala* test_c= get_element(test, 0);
	assert(test_c->zi == 1);
	assert(test_c->suma == 1);
	assert(strcmp(test_c->tip, "altele") == 0);
	Cheltuiala* c1 = formareCheltuiala(2, 4, "mancare");
    push_back(test, c1);

    test_c = get_element(test, 1);
	assert(test_c->zi == 2);
	assert(test_c->suma == 4);
	assert(strcmp(test_c->tip, "mancare") == 0);
	Cheltuiala* c2 = formareCheltuiala(3, 6, "transport");

    push_back(test, c2);
	assert(test->capacitate == INIT_MAX_SIZE * 2);
    distrugereLista(test);
}

void testInlocuireInLista()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);
	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
    push_back(test, c);
	Cheltuiala* c1 = formareCheltuiala(2, 4, "mancare");
	inlocuireInLista(test, c1, 0);
    Cheltuiala* test_c = get_element(test, 0);
	assert(test_c->zi == 2);
	assert(test_c->suma == 4);
	assert(strcmp(test_c->tip, "mancare") == 0);

    distrugereLista(test);
}

void testExistaPozitie()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
    push_back(test, c);
	assert(existaPozitie(0, test));
	assert(!existaPozitie(1, test));

    distrugereLista(test);
}

void testEliminareDinLista()
{
//    Lista* test = malloc(sizeof(Lista));
//    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala);
//
//	Cheltuiala* c = formareCheltuiala(1, 1, "altele");
//	Cheltuiala* c1 = formareCheltuiala(2, 4, "mancare");
//    push_back(test, c);
//    push_back(test, c1);
//    eliminareDinLista(test, 0);
//    Cheltuiala* test_c = get_element(test, 0);
//
//	assert(getLungime(test) == 1);
//	assert(test_c->zi == 2);
//	assert(test_c->suma == 4);
//	assert(strcmp(test_c->tip, "mancare") == 0);
//
//    distrugereLista(test);
//	distrugereCheltuiala(&c);
}

void testDistrugereLista()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(42, 42, "altele");
	Cheltuiala* c1 = formareCheltuiala(2, 4, "mancare");
    push_back(test, c);
    push_back(test, c1);
    distrugereLista(test);
}

void testFiltrareZi()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(2, 1, "altele");
	Cheltuiala* c1 = formareCheltuiala(4, 4, "mancare");
    push_back(test, c);
    push_back(test, c1);

	Lista* zi1_1 = filt_zi('1', 1, test);
	Lista* zi1_2 = filt_zi('1', 2, test);

    Cheltuiala* t2 = get_element(zi1_2, 0);
	assert(getLungime(zi1_1) == 0);
	assert(getLungime(zi1_2) == 1);
	assert(t2->zi == 2);
	assert(t2->suma == 1);
	assert(strcmp(t2->tip, "altele") == 0);

	Lista* zi2_1 = filt_zi('2', 3, test);
	Lista* zi2_2 = filt_zi('2', 4, test);


    Cheltuiala* t4 = get_element(zi2_2, 0);

	assert(getLungime(zi2_1) == 0);
	assert(getLungime(zi2_2) == 1);
	assert(t4->zi == 4);
	assert(t4->suma == 4);
	assert(strcmp(t4->tip, "mancare") == 0);

	Lista* zi3_1 = filt_zi('3', 5, test);
	Lista* zi3_2 = filt_zi('3', 3, test);


    Cheltuiala* t6 = get_element(zi3_2, 0);

	assert(getLungime(zi3_1) == 0);
	assert(getLungime(zi3_2) == 1);
	assert(t6->zi == 4);
	assert(t6->suma == 4);
	assert(strcmp(t6->tip, "mancare") == 0);

    distrugereLista(test);
    distrugereLista(zi1_1);
    distrugereLista(zi1_2);
    distrugereLista(zi2_1);
    distrugereLista(zi2_2);
    distrugereLista(zi3_1);
    distrugereLista(zi3_2);
}

void testFiltrareSuma()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(2, 3, "altele");
	Cheltuiala* c1 = formareCheltuiala(4, 5, "mancare");
    push_back(test, c);
    push_back(test, c1);
	Lista* suma1_1 = filt_suma('1', 2, test);
	Lista* suma1_2 = filt_suma('1', 4, test);

	assert(getLungime(suma1_1) == 0);
	assert(getLungime(suma1_2) == 1);

    Cheltuiala* s2 = get_element(suma1_2, 0);

	assert(s2->zi == 2);
	assert(s2->suma == 3);
	assert(strcmp(s2->tip, "altele") == 0);

	Lista* suma2_1 = filt_suma('2', 4, test);
	Lista* suma2_2 = filt_suma('2', 5, test);


    Cheltuiala* s4 = get_element(suma2_2, 0);

	assert(getLungime(suma2_1) == 0);
	assert(getLungime(suma2_2) == 1);
	assert(s4->zi == 4);
	assert(s4->suma == 5);
	assert(strcmp(s4->tip, "mancare") == 0);

	Lista* suma3_1 = filt_suma('3', 7, test);
	Lista* suma3_2 = filt_suma('3', 4, test);


    Cheltuiala* s6 = get_element(suma3_2, 0);

	assert(getLungime(suma3_1) == 0);
	assert(getLungime(suma3_2) == 1);
	assert(s6->zi == 4);
	assert(s6->suma == 5);
	assert(strcmp(s6->tip, "mancare") == 0);

    distrugereLista(test);
    distrugereLista(suma1_1);
    distrugereLista(suma1_2);
    distrugereLista(suma2_1);
    distrugereLista(suma2_2);
    distrugereLista(suma3_1);
    distrugereLista(suma3_2);
}

void testFiltrareTip()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(2, 1, "altele");
	Cheltuiala* c1 = formareCheltuiala(4, 4, "mancare");
    push_back(test, c);
    push_back(test, c1);

	Lista* tip1_1 = filt_tip('1', "transport", test);
	Lista* tip1_2 = filt_tip('1', "altele", test);


    Cheltuiala* e0 = get_element(tip1_2, 0);

	assert(getLungime(tip1_1) == 0);
	assert(getLungime(tip1_2) == 1);
	assert(e0->zi == 2);
	assert(e0->suma == 1);
	assert(strcmp(e0->tip, "altele") == 0);

	Lista* tip2 = filt_tip('2', "transport", test);

    Cheltuiala* e1 = get_element(tip2, 0);
    Cheltuiala* e2 = get_element(tip2, 1);

	assert(getLungime(tip2) == 2);
	assert(e1->zi == 2);
	assert(e1->suma == 1);
	assert(strcmp(e1->tip, "altele") == 0);
	assert(e2->zi == 4);
	assert(e2->suma == 4);
	assert(strcmp(e2->tip, "mancare") == 0);

    distrugereLista(test);
    distrugereLista(tip1_1);
    distrugereLista(tip1_2);
    distrugereLista(tip2);

}

void testeLista()
{
	testIntializareLista();
	testGetLungime();
	testVerificareDate();
	testDistrugereLista();
	testAdaugareInLista();
	testInlocuireInLista();
	testExistaPozitie();
	testEliminareDinLista();
	testFiltrareZi();
	testFiltrareSuma();
	testFiltrareTip();
}

void testCompSuma()
{
	Cheltuiala* c = formareCheltuiala(2, 1, "altele");
	Cheltuiala* c1 = formareCheltuiala(4, 4, "mancare");
	Cheltuiala* c2 = formareCheltuiala(6, 1, "mancare");
	assert(compSuma(c, c2, 1) == 0);
	assert(compSuma(c, c1, 1) == -1);
	assert(compSuma(c1, c2, 1) == 1);

	distrugereCheltuiala(c);
	distrugereCheltuiala(c1);
	distrugereCheltuiala(c2);
}

void testCompTip()
{
	Cheltuiala* c = formareCheltuiala(2, 1, "altele");
	Cheltuiala* c1 = formareCheltuiala(4, 4, "mancare");
	Cheltuiala* c2 = formareCheltuiala(6, 1, "mancare");
	assert(compTip(c1, c2, 1) == 0);
	assert(compTip(c, c1, 1) == -1);
	assert(compTip(c2, c, 1) == 1);

	distrugereCheltuiala(c);
	distrugereCheltuiala(c1);
	distrugereCheltuiala(c2);
}

void testSortareLista()
{
    Lista* test = malloc(sizeof(Lista));
    initList(test, sizeof(Cheltuiala*), distrugereCheltuiala, (copy_function) copiereCheltuiala);

	Cheltuiala* c = formareCheltuiala(2, 1, "mancare");
	Cheltuiala* c1 = formareCheltuiala(4, 4, "altele");
    push_back(test, c);
    push_back(test, c1);

	Lista* rez1 = sortareLista(test, compSuma, 1);

    Cheltuiala* e1 = get_element(rez1, 0);
    Cheltuiala* e2 = get_element(rez1, 1);
	assert(e1->zi == 2);
	assert(e1->suma == 1);
	assert(strcmp(e1->tip, "mancare") == 0);
	assert(e2->zi == 4);
	assert(e2->suma == 4);
	assert(strcmp(e2->tip, "altele") == 0);


	Lista* rez2 = sortareLista(test, compSuma, -1);
    e1 = get_element(rez2, 0);
    e2 = get_element(rez2, 1);
	assert(e2->zi == 2);
	assert(e2->suma == 1);
	assert(strcmp(e2->tip, "mancare") == 0);
	assert(e1->zi == 4);
	assert(e1->suma == 4);
	assert(strcmp(e1->tip, "altele") == 0);

	Lista* rez3 = sortareLista(test, compTip, 1);
    e1 = get_element(rez3, 0);
    e2 = get_element(rez3, 1);
	assert(e2->zi == 2);
	assert(e2->suma == 1);
	assert(strcmp(e2->tip, "mancare") == 0);
	assert(e1->zi == 4);
	assert(e1->suma == 4);
	assert(strcmp(e1->tip, "altele") == 0);

	Lista* rez4 = sortareLista(test, compTip, -1);
    e1 = get_element(rez4, 0);
    e2 = get_element(rez4, 1);
	assert(e1->zi == 2);
	assert(e1->suma == 1);
	assert(strcmp(e1->tip, "mancare") == 0);
	assert(e2->zi == 4);
	assert(e2->suma == 4);
	assert(strcmp(e2->tip, "altele") == 0);

    distrugereLista(test);
    distrugereLista(rez1);
    distrugereLista(rez2);
    distrugereLista(rez3);
    distrugereLista(rez4);
}

void testeSortare()
{
	testCompSuma();
	testCompTip();
	testSortareLista();
}

void teste()
{
	testeFunctii();
	testeCheltuiala();
	testeLista();
	testeSortare();
}