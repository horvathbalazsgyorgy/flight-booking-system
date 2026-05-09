#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataStructures.h"
#include "Logical.h"
#include "Jaratok_Print.h"
#include "Foglalas_InputHandler.h"
#include "debugmalloc.h"

/*ÚJ FOGLALÁS MEGADÁSA*/
Foglalas fogl_megadas(Jaratok *j_eleje, Foglalasok *f_eleje){
    int idx;
    Jaratok *mozgatas = j_eleje;
    Foglalas uj_fogl;
    printf("Kerem adja meg a nevet: ");
    scanf("\n%[^\n]s", uj_fogl.nev);
    while(name_exists(f_eleje, uj_fogl.nev)){ /*AMEDDIG A NÉV LÉTEZIK*/
        system("cls");
        printf("Ilyen nev mar letezik! Kerem adjon meg egy masikat: ");
        scanf("\n%[^\n]s", uj_fogl.nev);
    }
    Jaratok_show_all(j_eleje, f_eleje, &idx); /*JÁRATOK KÍÍRÁSA*/
    int j = 1;
    while(j != idx){
        j++;
        mozgatas = mozgatas->kov_elem;
    }
    strcpy(uj_fogl.honnan, mozgatas->elem.honnan);
    strcpy(uj_fogl.hova, mozgatas->elem.hova);
    uj_fogl.ar = mozgatas->elem.ar;
    strcpy(uj_fogl.foglalt_helyek[0], "0");
    uj_fogl.valasztott_menuk[0] = -1; /*NEM RENDELTEK MÉG EGYSZER SEM*/
    for(int i = 1; i < 4; i++){
        uj_fogl.valasztott_menuk[i] = 0; /*MINDEN TOVÁBBI MENÜBÕL NULLA VAN RENDELVE KEZDETBEN*/
    }
    return uj_fogl;
}

/*FOGLALÁS ADATSZERKEZETBE ÍRÁSA*/
Foglalasok *fogl_beiras(Foglalasok *eleje, Foglalas uj_fogl){
    Foglalasok *uj =(Foglalasok*)malloc(sizeof(Foglalasok));
    if(uj == NULL) return NULL; /*SIKERTELEN MEMÓRIA FOGLALÁS*/
    uj->elem = uj_fogl;
    uj->kov_fogl = NULL;
    if(eleje == NULL){ /*ÜRES LISTA*/
        eleje = uj;
    }else{
        Foglalasok *mozgato = eleje;
        while(mozgato->kov_fogl != NULL){ /*AMEDDIG AZ UTOLSÓ ELEMHEZ NEM ÉRTÜNK*/
            mozgato = mozgato->kov_fogl;
        }
        mozgato->kov_fogl = uj;
    }
    return eleje;
}
