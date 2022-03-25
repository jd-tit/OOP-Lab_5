//
// Created by jdt on 2022-03-25.
//

#include "Lista.h"
#include "Cheltuiala.h"
#include <stdlib.h>

#include "ctrl.h"

Lista* get_weekend_expenses(Lista* expenseList){
    Lista* result = malloc(sizeof(Lista));

    initList(result, sizeof(Cheltuiala), distrugereCheltuiala, (copy_function) copiereCheltuiala);
    for(size_t i = 0; i < expenseList->lungime; ++i){
        Cheltuiala* crt = get_element(expenseList, i);
        if(crt->zi % 7 == 0 || crt->zi % 7 == 6){
            push_back(result, crt);
        }
    }
    return result;
}
