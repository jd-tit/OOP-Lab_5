#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "UI.h"
#include "Teste.h"

int main()
{
	teste();
	printf("Teste efectuate cu succes.");
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}