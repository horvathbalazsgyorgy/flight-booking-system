#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataStructures.h"
#include "Check_Search.h"
#include "Logical.h"
#include "SeatHandler.h"
#include "Jaratok_Print.h"
#include "debugmalloc.h"

/*ÜLÉS MEGVÁLTOZTATÁSA*/
static void seat_change(Foglalasok *f_eleje, Foglalas *elem, char *ules, int *idx){
    printf("\nKerem valassza ki az uleseket (sor[szokoz]oszlop):\n");
    while(scanf("\n%[^\n]s", ules) == 1){ /*AMEDDIG VAN BEMENETI ADAT*/
        char *seged = strtok(ules, " ");
        strcpy(ules, seged);
        seged = strtok(NULL, " ");
        strcat(ules, seged);
        if(foglalt_e(f_eleje, (*elem), ules)){ /*HA FOGLALT A VÁLASZTOTT ÜLÉS*/
            printf("Ez az ules mar foglalt!\n");
        }else{
            strcpy((*elem).foglalt_helyek[(*idx)], ules); /*ELLENKEZÕ ESETBEN HOZZÁADJA*/
            (*idx)++;
        }
        strcpy((*elem).foglalt_helyek[(*idx)], "0"); /*NINCSEN TÖBB FOGLALT ÜLÉS*/
    }
}

/*OSZLOPSZÁMOK KIIRÁSA*/
static void fogl_terkep_oszlopszamok(Jarat elem){
    for(int i = 0; i <= elem.oszlop*3+1; i++){
        if(i < 3) printf(" ");
        else printf("_");}
    printf("\n");
    for(int i = 0; i <= elem.oszlop; i++){
        if(i == 0) printf("   ");
        else if(i < 10) printf("0%d ", i);
        else printf("%d ", i);}
    printf("\n");
    for(int i = 0; i <= elem.oszlop*3+1; i++){
        if(i < 3) printf(" ");
        else printf("_");}
    printf("\n");
}

/*FOGLALTSÁGI TÉRKÉP*/
static void fogl_terkep(Foglalasok *f_eleje, Jarat elem){
    int kari = 22; /*SPECIÁLIS KARAKTER*/
    Foglalasok *mozgo;
    char matrix[elem.sor][elem.oszlop];
    for(int i = 0; i < elem.sor; i++){
        for(int j = 0; j < elem.oszlop; j++){
            matrix[i][j] = kari;} } /*MATRIX FELTÖLTÉSE*/
    for(mozgo = f_eleje; mozgo != NULL; mozgo = mozgo->kov_fogl){ /*LISTA VÉGÉIG*/
        if(strcmp(elem.honnan, mozgo->elem.honnan) == 0 && strcmp(elem.hova, mozgo->elem.hova) == 0){ /*TELJES EGYEZÉS*/
            for(int i = 0; strcmp(mozgo->elem.foglalt_helyek[i], "0") != 0; i++){ /*AMEDDIG VAN FOGLALT HELY*/
                char elso = mozgo->elem.foglalt_helyek[i][0];
                char masodik = mozgo->elem.foglalt_helyek[i][1];
                int ei = (elso - '0') * 10 + (masodik - '0');
                elso = mozgo->elem.foglalt_helyek[i][2];
                masodik = mozgo->elem.foglalt_helyek[i][3];
                int mi = (elso - '0') * 10 + (masodik - '0');
                matrix[ei-1][mi-1] = 'X';} } } /*FOGLALT HELY JELZÉSE*/
    printf("A(z) |%s -> %s| jarat foglaltsagi terkepe (szabad helyek: %d):\n\n", elem.honnan, elem.hova, Free_seats_count(elem, f_eleje));
    fogl_terkep_oszlopszamok(elem);
    for(int i = 0; i < elem.sor; i++){
        for(int j = 0; j < elem.oszlop; j++){
            if(j == 0){
                if(i < 10 && i != 9) printf("0%d|%c%c ", i+1, matrix[i][j], matrix[i][j]);
                else if(i == 9) printf("%d|%c%c ", i+1, matrix[i][j], matrix[i][j]);
                else printf("%d|%c%c ", i+1, matrix[i][j], matrix[i][j]);
            }else{
                printf("%c%c ", matrix[i][j], matrix[i][j]); }
        }printf("\n");
    }
}

/*ÜLÉS MEGADÁSA*/
Foglalasok *ules_megadas(Foglalasok *f_eleje, Jaratok *j_eleje){
    int idx = 0;
    char ules[6];
    Foglalasok *f_mozgato;
    Jaratok *j_mozgato;
    char name[50];
    enter_name(f_eleje, name); /*AMEDDIG LÉTEZÕ NEVET NEM AD MEG*/
    elem_keres(f_eleje, &f_mozgato, j_eleje, &j_mozgato, name); /*A NÉVHEZ TARTOZÓ FOGLALÁS ÉS JÁRAT MEGKERESÉSE*/
    if(strcmp(f_mozgato->elem.foglalt_helyek[0], "0") == 0){ /*MÉG NEM FOGLALTAK*/
        fogl_terkep(f_eleje, j_mozgato->elem);
        seat_change(f_eleje, &f_mozgato->elem, ules, &idx);
    }else{ /*MÁR FOGLALTAK*/
        for(int i = 0; strcmp(f_mozgato->elem.foglalt_helyek[i], "0") != 0; i++){ /*AMEDDIG VANNAK FOGLALT HELYEK*/
            strcpy(f_mozgato->elem.foglalt_helyek[i], "0");
        }
        fogl_terkep(f_eleje, j_mozgato->elem);
        seat_change(f_eleje, &f_mozgato->elem, ules, &idx);
    }
    return f_eleje;
}
