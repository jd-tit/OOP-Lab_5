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
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	assert(c.zi == 1);
	assert(c.suma == 1);
	assert(strcmp(c.tip, "altele") == 0);
	distrugereCheltuiala(&c);
}

void testDistrugereCheltuiala()
{
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	distrugereCheltuiala(&c);
}

void testCopiereCheltuiala()
{
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	cheltuiala copie = copiereCheltuiala(c);
	assert(c.zi == copie.zi);
	assert(c.suma == copie.suma);
	assert(strcmp(c.tip, copie.tip)==0);
	distrugereCheltuiala(&c);
	distrugereCheltuiala(&copie);
}

void testeCheltuiala()
{
	testFormareCheltuiala();
	testDistrugereCheltuiala();
	testCopiereCheltuiala();
}

void testIntializareLista()
{
	lista test = initializareLista();
	assert(test.lungime == 0);
	assert(test.capacitate == 2);
	distrugereLista(&test);
}

void testGetLungime()
{
	lista test = initializareLista();
	assert(getLungime(&test) == 0);
	distrugereLista(&test);
}

void testAdaugareInLista()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	adaugareInLista(&test, c);
	assert(getLungime(&test) == 1);
	assert(test.element[0].zi == 1);
	assert(test.element[0].suma == 1);
	assert(strcmp(test.element[0].tip,"altele")==0);
	cheltuiala c1 = formareCheltuiala(2, 4, "mancare");
	adaugareInLista(&test, c1);
	assert(test.element[1].zi == 2);
	assert(test.element[1].suma == 4);
	assert(strcmp(test.element[1].tip, "mancare") == 0);
	cheltuiala c2 = formareCheltuiala(3, 6, "transport");
	adaugareInLista(&test, c2);
	assert(test.capacitate == 4);
	
	distrugereLista(&test);
}

void testInlocuireInLista()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	adaugareInLista(&test, c);
	cheltuiala c1 = formareCheltuiala(2, 4, "mancare");
	inlocuireInLista(&test, c1, 0);
	assert(test.element[0].zi == 2);
	assert(test.element[0].suma == 4);
	assert(strcmp(test.element[0].tip, "mancare") == 0);

	distrugereLista(&test);
	distrugereCheltuiala(&c);
}

void testExistaPozitie()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	adaugareInLista(&test, c);
	assert(existaPozitie(0, &test) == 0);
	assert(existaPozitie(1, &test) == -1);

	distrugereLista(&test);
}

void testEliminareDinLista()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	cheltuiala c1 = formareCheltuiala(2, 4, "mancare");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);
	eliminareDinLista(&test, 0);
	assert(getLungime(&test) == 1);
	assert(test.element[0].zi == 2);
	assert(test.element[0].suma == 4);
	assert(strcmp(test.element[0].tip, "mancare") == 0);

	distrugereLista(&test);
	distrugereCheltuiala(&c);
}

void testDistrugereLista()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(1, 1, "altele");
	cheltuiala c1 = formareCheltuiala(2, 4, "mancare");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);
	distrugereLista(&test);
}

void testFiltrareZi()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(2, 1, "altele");
	cheltuiala c1 = formareCheltuiala(4, 4, "mancare");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);

	lista zi1_1 = filt_zi('1', 1, &test);
	lista zi1_2 = filt_zi('1', 2, &test);

	assert(getLungime(&zi1_1) == 0);
	assert(getLungime(&zi1_2) == 1);
	assert(zi1_2.element[0].zi == 2);
	assert(zi1_2.element[0].suma == 1);
	assert(strcmp(zi1_2.element[0].tip, "altele") == 0);

	lista zi2_1 = filt_zi('2', 3, &test);
	lista zi2_2 = filt_zi('2', 4, &test);

	assert(getLungime(&zi2_1) == 0);
	assert(getLungime(&zi2_2) == 1);
	assert(zi2_2.element[0].zi == 4);
	assert(zi2_2.element[0].suma == 4);
	assert(strcmp(zi2_2.element[0].tip, "mancare") == 0);

	lista zi3_1 = filt_zi('3', 5, &test);
	lista zi3_2 = filt_zi('3', 3, &test);

	assert(getLungime(&zi3_1) == 0);
	assert(getLungime(&zi3_2) == 1);
	assert(zi3_2.element[0].zi == 4);
	assert(zi3_2.element[0].suma == 4);
	assert(strcmp(zi3_2.element[0].tip, "mancare") == 0);

	distrugereLista(&test);
	distrugereLista(&zi1_1);
	distrugereLista(&zi1_2);
	distrugereLista(&zi2_1);
	distrugereLista(&zi2_2);
	distrugereLista(&zi3_1);
	distrugereLista(&zi3_2);
}

void testFiltrareSuma()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(2, 3, "altele");
	cheltuiala c1 = formareCheltuiala(4, 5, "mancare");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);

	lista suma1_1 = filt_suma('1', 2, &test);
	lista suma1_2 = filt_suma('1', 4, &test);

	assert(getLungime(&suma1_1) == 0);
	assert(getLungime(&suma1_2) == 1);
	assert(suma1_2.element[0].zi == 2);
	assert(suma1_2.element[0].suma == 3);
	assert(strcmp(suma1_2.element[0].tip, "altele") == 0);

	lista suma2_1 = filt_suma('2', 4, &test);
	lista suma2_2 = filt_suma('2', 5, &test);

	assert(getLungime(&suma2_1) == 0);
	assert(getLungime(&suma2_2) == 1);
	assert(suma2_2.element[0].zi == 4);
	assert(suma2_2.element[0].suma == 5);
	assert(strcmp(suma2_2.element[0].tip, "mancare") == 0);

	lista suma3_1 = filt_suma('3', 7, &test);
	lista suma3_2 = filt_suma('3', 4, &test);

	assert(getLungime(&suma3_1) == 0);
	assert(getLungime(&suma3_2) == 1);
	assert(suma3_2.element[0].zi == 4);
	assert(suma3_2.element[0].suma == 5);
	assert(strcmp(suma3_2.element[0].tip, "mancare") == 0);

	distrugereLista(&test);
	distrugereLista(&suma1_1);
	distrugereLista(&suma1_2);
	distrugereLista(&suma2_1);
	distrugereLista(&suma2_2);
	distrugereLista(&suma3_1);
	distrugereLista(&suma3_2);
}

void testFiltrareTip()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(2, 1, "altele");
	cheltuiala c1 = formareCheltuiala(4, 4, "mancare");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);

	lista tip1_1 = filt_tip('1',"transport", &test);
	lista tip1_2 = filt_tip('1',"altele", &test);

	assert(getLungime(&tip1_1) == 0);
	assert(getLungime(&tip1_2) == 1);
	assert(tip1_2.element[0].zi == 2);
	assert(tip1_2.element[0].suma == 1);
	assert(strcmp(tip1_2.element[0].tip, "altele") == 0);

	lista tip2 = filt_tip('2', "transport", &test);

	assert(getLungime(&tip2) == 2);
	assert(tip2.element[0].zi == 2);
	assert(tip2.element[0].suma == 1);
	assert(strcmp(tip2.element[0].tip, "altele") == 0);
	assert(tip2.element[1].zi == 4);
	assert(tip2.element[1].suma == 4);
	assert(strcmp(tip2.element[1].tip, "mancare") == 0);

	distrugereLista(&test);
	distrugereLista(&tip1_1);
	distrugereLista(&tip1_2);
	distrugereLista(&tip2);

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
	cheltuiala c = formareCheltuiala(2, 1, "altele");
	cheltuiala c1 = formareCheltuiala(4, 4, "mancare");
	cheltuiala c2 = formareCheltuiala(6, 1, "mancare");
	assert(compSuma(&c, &c2, 1) == 0);
	assert(compSuma(&c, &c1, 1) == -1);
	assert(compSuma(&c1, &c2, 1) == 1);

	distrugereCheltuiala(&c);
	distrugereCheltuiala(&c1);
	distrugereCheltuiala(&c2);
}

void testCompTip()
{
	cheltuiala c = formareCheltuiala(2, 1, "altele");
	cheltuiala c1 = formareCheltuiala(4, 4, "mancare");
	cheltuiala c2 = formareCheltuiala(6, 1, "mancare");
	assert(compTip(&c1, &c2, 1) == 0);
	assert(compTip(&c, &c1, 1) == -1);
	assert(compTip(&c2, &c, 1) == 1);

	distrugereCheltuiala(&c);
	distrugereCheltuiala(&c1);
	distrugereCheltuiala(&c2);
}

void testSortareLista()
{
	lista test = initializareLista();
	cheltuiala c = formareCheltuiala(2, 1, "mancare");
	cheltuiala c1 = formareCheltuiala(4, 4, "altele");
	adaugareInLista(&test, c);
	adaugareInLista(&test, c1);

	lista rez1 = sortareLista(&test, compSuma, 1);
	assert(rez1.element[0].zi == 2);
	assert(rez1.element[0].suma == 1);
	assert(strcmp(rez1.element[0].tip, "mancare") == 0);
	assert(rez1.element[1].zi == 4);
	assert(rez1.element[1].suma == 4);
	assert(strcmp(rez1.element[1].tip, "altele") == 0);

	lista rez2 = sortareLista(&test, compSuma, -1);
	assert(rez2.element[1].zi == 2);
	assert(rez2.element[1].suma == 1);
	assert(strcmp(rez2.element[1].tip, "mancare") == 0);
	assert(rez2.element[0].zi == 4);
	assert(rez2.element[0].suma == 4);
	assert(strcmp(rez2.element[0].tip, "altele") == 0);

	lista rez3 = sortareLista(&test, compTip, 1);
	assert(rez3.element[1].zi == 2);
	assert(rez3.element[1].suma == 1);
	assert(strcmp(rez3.element[1].tip, "mancare") == 0);
	assert(rez3.element[0].zi == 4);
	assert(rez3.element[0].suma == 4);
	assert(strcmp(rez3.element[0].tip, "altele") == 0);

	lista rez4 = sortareLista(&test, compTip, -1);
	assert(rez4.element[0].zi == 2);
	assert(rez4.element[0].suma == 1);
	assert(strcmp(rez4.element[0].tip, "mancare") == 0);
	assert(rez4.element[1].zi == 4);
	assert(rez4.element[1].suma == 4);
	assert(strcmp(rez4.element[1].tip, "altele") == 0);

	distrugereLista(&test);
	distrugereLista(&rez1);
	distrugereLista(&rez2);
	distrugereLista(&rez3);
	distrugereLista(&rez4);

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