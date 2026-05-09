#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataStructures.h"
#include "Check_Search.h"
#include "Logical.h"
#include "debugmalloc.h"

/*ADOTT ELEM KERESÉSE*/
/*A KERENDÕ ELEMEK KETTÕS INDIREKCIÓVAL VANNAK ÁTADVA, MIVEL VÁLTOZTATJUK ÕKET*/
void elem_keres(Foglalasok *f_e, Foglalasok **f_m, Jaratok *j_e, Jaratok **j_m, char *name){
    for((*f_m) = f_e; (*f_m) != NULL; (*f_m) = (*f_m)->kov_fogl){
        if(strcmp((*f_m)->elem.nev, name) == 0) break; /*TELJES EGYEZÉS*/
    }
    for((*j_m) = j_e; (*j_m) != NULL; (*j_m) = (*j_m)->kov_elem){
        if(strcmp((*f_m)->elem.honnan, (*j_m)->elem.honnan) == 0 &&
           strcmp((*f_m)->elem.hova, (*j_m)->elem.hova) == 0) break; /*TELJES EGYEZÉS*/
    }
}

/*NÉV ELLENÕRZÉSE*/
void enter_name(Foglalasok *f_eleje, char *name){
    printf("Kerem adja meg a nevet: ");
    scanf("\n%[^\n]s", name);
    while(!name_exists(f_eleje, name)){/*AMEDDIG A NÉV NEM LÉTEZIK*/
        system("cls");
        printf("Ilyen nevvel nincsen foglalas! Kerem adjon meg egy masikat: ");
        scanf("\n%[^\n]s", name);
    }
    system("cls");
}
