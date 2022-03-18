#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <string.h>
#include "Functii.h"
#include "Lista.h"

void golireBuffer()
{
	while (getchar() != '\n')
		;
}

int adaugareCheltuiala(lista* l)
{
	int zi, suma, v_date;
	char tip[150], zi_s[20], suma_s[20];

	printf("\nAti ales sa adaugati o noua cheltuiala.\n");
	printf("\nZiua: "); fgets(zi_s, sizeof(zi_s), stdin);
	eliminareNewLine(zi_s);
	printf("\nSuma: "); fgets(suma_s, sizeof(suma_s), stdin);
	eliminareNewLine(suma_s);
	printf("\nTipul: "); fgets(tip, sizeof(tip), stdin);
	eliminareNewLine(tip);

	zi = transformareStringNumar(zi_s);
	suma = transformareStringNumar(suma_s);

	v_date = verificareDate(zi, suma, tip);
	if (v_date == 0)
	{
		cheltuiala c = formareCheltuiala(zi, suma, tip);
		adaugareInLista(l, c);
		printf("\nCheltuiala a fost introdusa.\n");
	}
	else
	{
		if (v_date == -1)
		{
			printf("Zi incorecta.\n");
			return -1;
		}
		if (v_date == -2)
		{
			printf("Suma incorecta.\n");
			return -2;
		}

		printf("Tip incorect.\n");
		return -3;

	}
	return 0;
}

void afisareLista(lista* l)
{
	int lungime = getLungime(l);
	if (l == 0)
		printf("\nNu exista cheltuieli.\n");
	else
		for (int i = 0; i < lungime; i++)
		{
			cheltuiala c = l->element[i];
			printf("Cheltuiala nr. %d: \nZiua - %d", i+1, c.zi);
			printf("\nSuma - %d", c.suma);
			printf("\nTip - %s\n", c.tip);
		}
}

int modificareCheltuiala(lista* l)
{
	int numar, zi, suma, v_date;
	char tip[150], zi_s[20], suma_s[20], numar_s[20];
	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -4;
	}
	printf("\nAti ales sa modificati o cheltuiala existenta.\n");
	printf("\nLista curenta de cheltuieli este:\n");
	afisareLista(l);
	printf("Introduceti nr. cheltuielii care doriti sa o modificati: "); fgets(numar_s, sizeof(numar_s), stdin);
	eliminareNewLine(numar_s);
	numar = transformareStringNumar(numar_s);
	numar = numar - 1;
	if (existaPozitie(numar, l) == -1)
	{
		printf("Nu exista aceasta pozitie.\n");
		return -5;
	}

	printf("\nIntroduceti noile date: ");
	printf("\nZiua: "); fgets(zi_s, sizeof(zi_s), stdin);
	eliminareNewLine(zi_s);
	printf("\nSuma: "); fgets(suma_s, sizeof(suma_s), stdin);
	eliminareNewLine(suma_s);
	printf("\nTipul: "); fgets(tip, sizeof(tip), stdin);
	eliminareNewLine(tip);

	zi = transformareStringNumar(zi_s);
	suma = transformareStringNumar(suma_s);

	v_date = verificareDate(zi, suma, tip);
	if (v_date == 0)
	{
		cheltuiala c = formareCheltuiala(zi, suma, tip);
		cheltuiala inlocuita =	inlocuireInLista(l, c, numar);
		printf("\nCheltuiala nr. %d a fost modificata.\n", numar+1);
		distrugereCheltuiala(&inlocuita);
	}
	else
	{
		if (v_date == -1)
		{
			printf("Zi incorecta.\n");
			return -1;
		}
		if (v_date == -2)
		{
			printf("Suma incorecta.\n");
			return -2;
		}

		printf("Tip incorect.\n");
		return -3;

	}
	return 0;
}

int stergereCheltuiala(lista* l)
{
	int numar;
	char numar_s[20];
	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -4;
	}
	printf("\nAti ales sa stergeti o cheltuiala existenta.\n");
	printf("\nLista curenta de cheltuieli este:\n");
	afisareLista(l);
	printf("Introduceti nr. cheltuielii care doriti sa o stergeti: "); fgets(numar_s, sizeof(numar), stdin);
	eliminareNewLine(numar_s);
	numar = transformareStringNumar(numar_s);
	numar = numar - 1;
	if (existaPozitie(numar, l) == -1)
	{
		printf("Nu exista aceasta pozitie.\n");
		return -5;
	}
	cheltuiala eliminat = eliminareDinLista(l, numar);
	printf("Cheltuiala de pe pozitia %d a fost stearsa.\n", numar);
	distrugereCheltuiala(&eliminat);
	return 0;
}

int filtrare_zi(lista* l)
{
	char comanda, zi_s[20];
	int zi;
	golireBuffer();
	printf("\n1- Primele 'n' zile ale lunii.");
	printf("\n2- Ziua 'n'.");
	printf("\n3- Toate zilele de dupa ziua 'n'.");
	printf("\nComanda: "); scanf_s("%c", &comanda, 1);
	golireBuffer();
	if (comanda < '1' || comanda>'3')
	{
		printf("Comanda gresita.\n");
		return -1;
	}
	printf("\nZiua: "); fgets(zi_s, sizeof(zi_s), stdin);
	eliminareNewLine(zi_s);
	zi = transformareStringNumar(zi_s);
	int v_date = verificareDate(zi, 1, "altele");
	if (v_date == -1)
	{
		printf("Zi incorecta.\n");
		return -2;
	}
	lista rez = filt_zi(comanda, zi, l);
	if (rez.lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(&rez);
	distrugereLista(&rez);
	return 0;
}

int filtrare_suma(lista* l)
{
	char comanda, suma_s[20];
	int suma;
	golireBuffer();
	printf("\n1- Sume mai mici decat 'n'");
	printf("\n2- Suma 'n'.");
	printf("\n3- Sume mai mari decat 'n'.");
	printf("\nComanda: "); scanf_s("%c", &comanda, 1); 
	golireBuffer();
	if (comanda < '1' || comanda > '3')
	{
		printf("Comanda gresita.\n");
		return -1;
	}
	printf("\nSuma: "); fgets(suma_s, sizeof(suma_s), stdin);
	eliminareNewLine(suma_s);
	suma = transformareStringNumar(suma_s);
	int v_date = verificareDate(1, suma, "altele");
	if (v_date == -2)
	{
		printf("Suma incorecta.\n");
		return -2;
	}
	lista rez = filt_zi(comanda, suma, l);
	if (rez.lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(&rez);
	distrugereLista(&rez);
	return 0;
}

int filtrare_tip(lista* l)
{
	char comanda, tip[20];
	golireBuffer();
	printf("\n1- Tipul 'n'");
	printf("\n2- Toate cu exceptia tipului 'n'");
	printf("\nComanda: "); scanf_s("%c", &comanda, 1); 
	golireBuffer();
	if (comanda < '1' || comanda>'2')
	{
		printf("Comanda gresita.\n");
		return -1;
	}
	printf("\nTip: "); fgets(tip, sizeof(tip), stdin);
	eliminareNewLine(tip);
	int v_date = verificareDate(1, 1, tip);
	if (v_date == -3)
	{
		printf("Tip incorecta.\n");
		return -2;
	}
	lista rez = filt_tip(comanda, tip, l);
	if (rez.lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(&rez);
	distrugereLista(&rez);
	return 0;
}

int filtrare(lista* l)
{
	int ok = 1;
	char proprietate[10];

	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -1;
	}
	printf("\nAti ales sa filtrati lista dupa o proprietate. (zi, suma sau tip)");
	printf("\nProprietatea este: "); fgets(proprietate, sizeof(proprietate), stdin);
	eliminareNewLine(proprietate);
	if (strcmp(proprietate, "zi") == 0)
	{
		filtrare_zi(l);
		ok = 0;
	}
	if (strcmp(proprietate, "suma") == 0)
	{
		filtrare_suma(l);
		ok = 0;
	}
	if (strcmp(proprietate, "tip") == 0)
	{
		filtrare_tip(l);
		ok = 0;
	}
	if (ok == 1)
	{
		printf("\nProprietate incorecta.");
		return -2;
	}
	return 0;
}

int sortare(lista* l)
{
	char proprietate[10], ordine[15];

	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -1;
	}
	printf("\nAti ales sa sortati lista dupa o proprietate. (suma sau tip)");
	printf("\nProprietatea este: "); fgets(proprietate, sizeof(proprietate), stdin);
	eliminareNewLine(proprietate);
	if (strcmp(proprietate, "suma") != 0 && strcmp(proprietate, "tip") != 0)
	{
		printf("\nProprietate incorecta.");
		return -2;
	}
	printf("\nLista poate fi sortata crescator sau descrescator.");
	printf("\nLista va fi sortata: "); fgets(ordine, sizeof(ordine), stdin);
	eliminareNewLine(ordine);
	if (strcmp(ordine, "crescator") != 0 && strcmp(ordine, "descrescator") != 0)
	{
		printf("\nOrdine incorecta.");
		return -3;
	}
	
	lista rez;
	int ord;
	if (strcmp(ordine, "crescator") == 0)
		ord = 1;
	else
		ord = -1;
	if(strcmp(proprietate, "suma") == 0)
		rez = sortareLista(l,compSuma,ord);
	else
		rez = sortareLista(l,compTip,ord);
	printf("\n");
	afisareLista(&rez);
	distrugereLista(&rez);
	return 0;
}

void run()
{
	lista listaCheltuieli = initializareLista();
	int ok = 1, corect;
	char comanda[10];
	while (ok == 1)
	{
		printf("\nAceasta aplicatie permite gestionarea cheltuielilor unei familii.\n");
		printf("1 - Adaugarea unei noi cheltuieli\n");
		printf("2 - Modificarea unei cheltuieli\n");
		printf("3 - Stergerea unei cheltueli\n");
		printf("4 - Vizualizarea listei de cheltuieli, filtrata dupa o proprietate\n");
		printf("5 - Vizualizarea listei de cheltuieli, ordonata dupa suma sau tip\n");
		printf("6 - Afisare lista cheltuieli\n");
		printf("7 - Inchiderea aplicatiei\n");
		printf("Comanda: ");
		corect = 0;
		//scanf_s("%c", &comanda, 1);
		fgets(comanda, sizeof(comanda), stdin);
		eliminareNewLine(comanda);
		if (strcmp(comanda,"1")==0)
		{
			adaugareCheltuiala(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "2") == 0)
		{
			modificareCheltuiala(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "3") == 0)
		{
			stergereCheltuiala(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "4") == 0)
		{
			filtrare(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "5") == 0)
		{
			sortare(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "6") == 0)
		{
			afisareLista(&listaCheltuieli);
			corect = 1;
		}
		if (strcmp(comanda, "7") == 0)
		{
			distrugereLista(&listaCheltuieli);
			break;
		}
		if (corect == 0)
			printf("\nComanda incorecta.\n");
	}
}