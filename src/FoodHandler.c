#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "DataStructures.h"
#include "Check_Search.h"
#include "FoodHandler.h"
#include "debugmalloc.h"

/*ÉTEL MEGVÁLTOZTATÁSA*/
static void food_change(Foglalas *f_elem, Jarat *j_elem){
    int etel_id, etel_db;
    char valasz[2]; char c[2];
    do{
        system("cls");
        printf("Kerem valassza ki, hogy milyen menut ker:\n");
        for(int i = 0; etel[i] != NULL; i++){
            printf("[%d] %s\n", i+1, etel[i]);
        }
        scanf("%d", &etel_id);
        while(etel_id < 1 || etel_id > 4){ /*AMEDDIG HELYES ADATOT NEM AD MEG*/
            printf("Ervenytelen adatot adott meg! Adja meg ujbol:\n");
            scanf("%d", &etel_id);
        }
        printf("Hany darabot szeretne? Kerem adja meg: ");
        scanf("%d", &etel_db);
        if((*f_elem).valasztott_menuk[(etel_id-1)] == -1){ /*MÉG EGYSZER SEM VÁLASZTOTTAK*/
            (*f_elem).valasztott_menuk[(etel_id-1)] = etel_db;
        }
        else (*f_elem).valasztott_menuk[(etel_id-1)] += etel_db;
        printf("Szeretne meg rendelni? (I/N)");
        scanf(" %s", valasz); c[0] = tolower(valasz[0]);
    }while(strcmp(c, "n") != 0); /*AMEDDIG MÉG VÁLASZT*/
    if((*f_elem).valasztott_menuk[0] == -1) {(*f_elem).valasztott_menuk[0] = 0;} /*JELEZNI, HOGY MÁR VÁLASZTOTTAK*/
    for(int i = 0; i < 4; i++){
        (*j_elem).kert_menuk[i] += (*f_elem).valasztott_menuk[i]; /*ADOTT JÁRAT ÉTELEIT NÖVELNI A MEGADOTT MENNYISÉGEKKEL*/
    }
}

/*ÉTEL MEGADÁSA*/
Foglalasok *etel_megadas(Foglalasok *f_eleje, Jaratok *j_eleje){
    Foglalasok *f_mozgato;
    Jaratok *j_mozgato;
    char name[50];
    enter_name(f_eleje, name); /*AMEDDIG LÉTEZÕ NEVET NEM AD MEG*/
    elem_keres(f_eleje, &f_mozgato, j_eleje, &j_mozgato, name);/*A NÉVHEZ TARTOZÓ FOGLALÁS ÉS JÁRAT MEGKERESÉSE*/
    if(f_mozgato->elem.valasztott_menuk[0] == -1){/*EGYSZER SEM VÁLTOZTATTAK*/
        food_change(&f_mozgato->elem, &j_mozgato->elem);
    }else{
        for(int i = 0; i < 4; i++){ /*ELÕZÕ ÉTELEK TÖRLÉSE*/
            j_mozgato->elem.kert_menuk[i] -= f_mozgato->elem.valasztott_menuk[i];
            f_mozgato->elem.valasztott_menuk[i] = 0;
        }
        food_change(&f_mozgato->elem, &j_mozgato->elem);
    }
    return f_eleje;
}

