#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataStructures.h"
#include "Logical.h"
#include "Jaratok_Print.h"
#include "debugmalloc.h"

/*SZABAD ÜLÖHELYEK MEGSZÁMOLÁSA*/
int Free_seats_count(Jarat elem, Foglalasok *eleje){
    int helyek_db = 0;
    Foglalasok *mozgas;
    for(mozgas = eleje; mozgas != NULL; mozgas = mozgas->kov_fogl){
        if(strcmp(elem.honnan, mozgas->elem.honnan) == 0 && strcmp(elem.hova, mozgas->elem.hova) == 0){/*TELJES EGYEZÉS ESETÉN*/
            for(int i = 0; strcmp(mozgas->elem.foglalt_helyek[i], "0") != 0; i++){ /*AMEDDIG A LEFOGLALT HELY NEM NULLA =*/
                                                                                   /*AMEDDIG VAN LEFOGLALT HELY*/
                helyek_db++; /*FOGLALT HELY TÉNYÉNEK ELTÁROLÁSA*/
            }
        }
    }
    return (elem.sor * elem.oszlop) - helyek_db;/*AZ ÖSSZES HELYBÖL KIVONJA A FOGLALT HELYEKET.*/
}

/*EGY JÁRAT MEGJELENÍTÉSE*/
static void Jarat_show_one(Jarat elem, Foglalasok *eleje){
    printf("%s\t-> %s\t%d\tFt-\t%d - free seats", elem.honnan, elem.hova, elem.ar, Free_seats_count(elem, eleje));
}

/*EGY JÁRAT MEGJELENÍTÉSE FORMÁZVA*/
static void Jarat_valaszto_print(Jaratok *mozgo, Foglalasok *f_eleje, int i){
    printf("[%d] ", i);
    Jarat_show_one(mozgo->elem, f_eleje);
    printf("\n");
}

/*ÖSSZES JÁRAT MEGJELENÍTÉSE FORMÁZVA*/
void Jaratok_show_all(Jaratok *j_eleje, Foglalasok *f_eleje, int *idx){
    int gomb; int i = 1; int halad = 0;
    Jaratok *mozgatas;
    Jaratok *utolso = NULL; /*A JARAT ELSÖ ÉS AZ UTOLSÓ, A MÁR MEG NEM JELENÍTHETÖ (VAGYIS A 9.) ELEMÉRE MUTATÓ POINTEREK.*/
    for(mozgatas = j_eleje; mozgatas != NULL; mozgatas = mozgatas->kov_elem){ /*LISTA VÉGÉIG*/
        if(i > 8) break; /*DE 8-NÁL ÁLLJON MEG*/
        Jarat_valaszto_print(mozgatas, f_eleje, i); /*ADOTT JÁRAT KIÍRÁSA*/
        i++;}
    if(i > 8 && mozgatas != NULL){/*HA AZ INDEX > 8 ÉS NEM ÉRT EL A LISTA VÉGÉIG*/
        printf("\n[9] Kovetkezo oldal");
        utolso = mozgatas;}/*A KILENCEDIK ELEM ELTÁROLÁSA*/
    printf("\n");
    do{
        printf("Kerem valasszon jaratot: ");
        scanf("%d", &gomb);
        switch(gomb){
        case 0:
            if(halad == 0) break; /*HA NEM LÉPTÜNK KÖVETKEZÖ OLDALRA (AZ ELSÖN MARADTUNK)*/
            system("cls");
            halad = 0; i = 1; /*ELSÖ OLDALRA LÉPTÜNK, HALAD = 0*/
            for(mozgatas = j_eleje; mozgatas != NULL; mozgatas = mozgatas->kov_elem){ /*LISTA VÉGÉIG*/
                if(i > 8) break; /*DE 8-NÁL ÁLLJON MEG*/
                Jarat_valaszto_print(mozgatas, f_eleje, i);
                i++;}
            if(i > 8){ utolso = mozgatas; printf("\n[9] Kovetkezo oldal\n");} /*HA AZ INDEX > 8, AKKOR AZ UTOLSÓ*/
                                                                            /*MÁR NEM MEGJELENÍTHETÖ ELEM ELTÁROLÁSA*/
            break;
        case 9:
            if(i <= 9 && mozgatas == NULL) break; /*HA AZ INDEX <= 9 (HA 9, AKKOR AZ INDEX MÁR ELÉRT A KÖVETKEZÖ ELEMIG,*/
                                                  /*DE A MOZGATAS MÉG NEM), ÉS NINCS TÖBB MEGJELENÍTENDÖ ELEM*/
            system("cls"); i = 1;
            for(mozgatas = utolso; mozgatas != NULL; mozgatas = mozgatas->kov_elem){/*KEZDÖÉRTÉK: MOZGATAS = KILENCEDIK ELEM*/
                if(i > 8) break; /*8 ELEM KIIRÁSA UTÁN ÁLLJON MEG*/
                Jarat_valaszto_print(mozgatas, f_eleje, i);
                i++;}
            halad++; /*JELEZVE, HOGY TOVÁBB MENTÜNK A KÖVETKEZÖ OLDALRA*/
            if(i > 8 && mozgatas != NULL){/*HA VAN MÉG KIÍRANDÓ ELEM*/
                utolso = mozgatas;        /*A KILENCEDIK ELEM ELTÁROLÁSA*/
                printf("\n[0] Elso oldal\n[9] Kovetkezo oldal\n");}
            else if(i > 8 && mozgatas == NULL){ printf("\n[0] Elso oldal\n");}/*MÁR NINCSENEK KIÍRANDÓ ELEMEK*/
            else if(i <= 8){ printf("\n[0] Elso oldal\n");}
            break;}
        ///!!!DEFAULT ÁG SZÁNDÉKOSAN NINCS!!!///
    }while(gomb < 1 || gomb >= i);/*AMÍG A GOMB (LEÜTÖTT BILLENTYÜ) KISEBB 1-NÉL (LEGKISEBB VÁLASZTHATÓ) ÉS*/
                                  /*NAGYOBB VAGY EGYENLÖ, MINT I (I = LEGNAGYOBB VÁLASZTHATÓ UTÁNI JELÖLÉSE)*/
    mozgatas = j_eleje;
    *idx = gomb + (8 * halad); /*HÁNYAT KELL MENNI A KÍVÁNT ELEMIG*/
}

/*SZÜKSÉGES ÉTELEK KILISTÁZÁSA*/
void etelek_show_all(Jaratok *eleje){
    Jaratok *mozgo;
    if(eleje == NULL) {printf("Nincsenek szukseges etelek"); return;} /*ÜRES LISTA*/
    printf("Szukseges etelek:\n");
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov_elem){ /*LISTA VÉGÉIG*/
        printf("____________________________\n");
        printf("%s -> %s:", mozgo->elem.honnan, mozgo->elem.hova);
        if(!food_exists(mozgo->elem)){/*NINCSENEK ÉTELEK A JÁRATON*/
                printf("\n\tNincsenek szukseges etelek ezen a jaraton!");
        }
        else{
            for(int i = 0; i < 4; i++){
                if(mozgo->elem.kert_menuk[i] != 0){
                    printf("\n\t%s - %d db", etel[i], mozgo->elem.kert_menuk[i]);
                }
            }
        }
        printf("\n");
    }
}
