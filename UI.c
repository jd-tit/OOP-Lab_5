#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functii.h"
#include "Lista.h"
#include "Cheltuiala.h"
#include "ctrl.h"
#include "UI.h"

void golireBuffer()
{
	while (getchar() != '\n')
		;
}


void weekend_spending(Lista* cheltuieli){
    Lista* expenses = get_weekend_expenses(cheltuieli);

    if(expenses->lungime == 0){
        puts("Nu s-au facut cheltuieli in weekend");
        distrugereLista(expenses);
        return;
    }

    puts("Cheltuielile din weekend sunt: ");
    afisareLista(expenses);
}

void undo(Lista **target, Lista *undoList) {
    if(undoList->lungime == 0){
        puts("Nu se mai poate face Undo (ati ajuns la inceput)");
        return;
    }
    Lista* last = get_element(undoList, undoList->lungime-1);
    distrugereLista(*target);
    eliminareDinLista(undoList, undoList->lungime-1);
    *target = last;
    puts("Undo efectuat cu succes! ");
}

int adaugareCheltuiala(Lista *l, Lista *undoList)
{
	int zi, suma, v_date;
	char tip[150], zi_s[20], suma_s[20];

	printf("\nAti ales sa adaugati o noua Cheltuiala.\n");
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
        Lista* backup = copyLista(l);
        push_back(undoList,backup);

		Cheltuiala* c = formareCheltuiala(zi, suma, tip);
        push_back(l, c);
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

void afisareLista(Lista* l)
{
	size_t lungime = getLungime(l);
	if (l == 0)
		printf("\nNu exista cheltuieli.\n");
	else
		for (int i = 0; i < lungime; i++)
		{
			Cheltuiala* c = get_element(l, i);
			printf("Cheltuiala nr-> %d: \nZiua - %d", i+1, c->zi);
			printf("\nSuma - %d", c->suma);
			printf("\nTip - %s\n", c->tip);
		}
}

int modificareCheltuiala(Lista *l, Lista *undoList)
{
	int numar, zi, suma, v_date;
	char tip[150], zi_s[20], suma_s[20], numar_s[20];
	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -4;
	}
	printf("\nAti ales sa modificati o Cheltuiala existenta.\n");
	printf("\nLista curenta de cheltuieli este:\n");
	afisareLista(l);
	printf("Introduceti nr. cheltuielii care doriti sa o modificati: "); fgets(numar_s, sizeof(numar_s), stdin);
	eliminareNewLine(numar_s);
	numar = transformareStringNumar(numar_s);
	numar = numar - 1;
	if (!existaPozitie(numar, l))
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
        Lista* backup = copyLista(l);
        push_back(undoList,backup);

		Cheltuiala* c = formareCheltuiala(zi, suma, tip);
		inlocuireInLista(l, c, numar);
		printf("\nCheltuiala nr. %d a fost modificata.\n", numar+1);
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

int stergereCheltuiala(Lista *l, Lista *undoList)
{
	int numar;
	char numar_s[20];
	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -4;
	}
	printf("\nAti ales sa stergeti o Cheltuiala existenta.\n");
	printf("\nLista curenta de cheltuieli este:\n");
	afisareLista(l);
	printf("Introduceti nr. cheltuielii care doriti sa o stergeti: ");
    fgets(numar_s, sizeof(numar), stdin);
    eliminareNewLine(numar_s);
	numar = transformareStringNumar(numar_s);
	numar = numar - 1;

	if (!existaPozitie(numar, l))
	{
		printf("Nu exista aceasta pozitie.\n");
		return -5;
    }

    Lista* backup = copyLista(l);
    push_back(undoList,backup);

    eliminareDinLista(l, numar);
	printf("Cheltuiala de pe pozitia %d a fost stearsa.\n", numar);
	return 0;
}

int filtrare_zi(Lista* l)
{
	char comanda, zi_s[20];
	int zi;
	golireBuffer();
	printf("\n1- Primele 'n' zile ale lunii.");
	printf("\n2- Ziua 'n'.");
	printf("\n3- Toate zilele de dupa ziua 'n'.");
	printf("\nComanda: "); scanf("%c", &comanda);
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
	Lista* rez = filt_zi(comanda, zi, l);
	if (rez->lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(rez);
    distrugereLista(rez);
	return 0;
}

int filtrare_suma(Lista* l)
{
	char comanda, suma_s[20];
	int suma;
	golireBuffer();
	printf("\n1- Sume mai mici decat 'n'");
	printf("\n2- Suma 'n'.");
	printf("\n3- Sume mai mari decat 'n'.");
	printf("\nComanda: "); scanf("%c", &comanda);
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
	Lista* rez = filt_zi(comanda, suma, l);
	if (rez->lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(rez);
    distrugereLista(rez);
	return 0;
}

int filtrare_tip(Lista* l)
{
	char comanda, tip[20];
	golireBuffer();
	printf("\n1- Tipul 'n'");
	printf("\n2- Toate cu exceptia tipului 'n'");
	printf("\nComanda: "); scanf("%c", &comanda);
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
	Lista* rez = filt_tip(comanda, tip, l);
	if (rez->lungime == 0)
	{
		printf("\nNu exista elemente cu aceasta proprietate.");
		return -3;
	}
	printf("\n");
	afisareLista(rez);
    distrugereLista(rez);
	return 0;
}

int filtrare(Lista* l)
{
	int ok = 1;
	char proprietate[10];

	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -1;
	}
	printf("\nAti ales sa filtrati Lista dupa o proprietate. (zi, suma sau tip)");
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

int sortare(Lista* l)
{
	char proprietate[10], ordine[15];

	if (getLungime(l) == 0)
	{
		printf("\nNu exista cheltuieli.");
		return -1;
	}
	printf("\nAti ales sa sortati Lista dupa o proprietate. (suma sau tip)");
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
	
	Lista* rez;
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
	afisareLista(rez);
    distrugereLista(rez);
	return 0;
}

void run()
{
    Lista* undoList = malloc(sizeof(Lista));
    Lista* listaCheltuieli = malloc(sizeof(Lista));
    initList(listaCheltuieli, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
    initList(undoList, sizeof (Lista*), (destructor) distrugereLista, (copy_function) copyLista);
	char comanda[10];
	while(true)
	{
		puts("\nAceasta aplicatie permite gestionarea cheltuielilor unei familii");
		puts("1 - Adaugarea unei noi cheltuieli");
		puts("2 - Modificarea unei cheltuieli");
		puts("3 - Stergerea unei cheltueli");
		puts("4 - Vizualizarea listei de cheltuieli, filtrata dupa o proprietate");
		puts("5 - Vizualizarea listei de cheltuieli, ordonata dupa suma sau tip");
		puts("6 - Afisare Lista cheltuieli");
        puts("7 - Cheltuielile din weekend-uri (luna incepe intr-o luni)");
        puts("8 - Undo");
		puts("9 - Inchiderea aplicatiei");
		puts("Comanda: ");
		//scanf_s("%c", &comanda, 1);
		fgets(comanda, sizeof(comanda), stdin);
		eliminareNewLine(comanda);
		if (strcmp(comanda,"1")==0)
        {
            adaugareCheltuiala(listaCheltuieli, undoList);
		} else if (strcmp(comanda, "2") == 0)
		{
            modificareCheltuiala(listaCheltuieli, undoList);
		} else if (strcmp(comanda, "3") == 0)
		{
            stergereCheltuiala(listaCheltuieli, undoList);
		} else if (strcmp(comanda, "4") == 0)
		{
			filtrare(listaCheltuieli);
		} else if (strcmp(comanda, "5") == 0)
		{
			sortare(listaCheltuieli);
		} else if (strcmp(comanda, "6") == 0) {
            afisareLista(listaCheltuieli);
        } else if(strcmp(comanda, "7") == 0){
            weekend_spending(listaCheltuieli);
        } else if(strcmp(comanda, "8") == 0){
            undo(&listaCheltuieli,  undoList);
		} else if (strcmp(comanda, "9") == 0)
		{
            distrugereLista(listaCheltuieli);
            puts("La revedere!");
            exit(0);
		} else {
           puts("\nComanda incorecta.");
        }
	}
}