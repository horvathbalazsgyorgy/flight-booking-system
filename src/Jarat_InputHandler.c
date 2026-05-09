#include <stdlib.h>
#include <stdio.h>
#include "DataStructures.h"
#include "Logical.h"
#include "Jarat_InputHandler.h"
#include "debugmalloc.h"

/*�J J�RAT MEGAD�SA*/
Jarat jarat_megadas(Jaratok *eleje){
    Jarat uj;
    printf("Kerem adja meg a kiindulopontot: ");
    scanf("\n%[^\n]s", uj.honnan);
    printf("Kerem adja meg az uticelt: ");
    scanf("\n%[^\n]s", uj.hova);
    while(jarat_exists(eleje, uj.honnan, uj.hova)){ /*AMEDDIG M�R L�TEZ� J�RATOT AD MEG*/
        system("cls");
        printf("Ilyen jarat mar letezik! Adjon meg egy masikat!\n");
        printf("Kerem adja meg a kiindulopontot: ");
        scanf("\n%[^\n]s", uj.honnan);
        printf("Kerem adja meg az uticelt: ");
        scanf("\n%[^\n]s", uj.hova);
    }
    printf("Kerem adja meg a jegyarat: ");
    scanf("%d", &uj.ar);
    printf("Kerem adja meg az ulesek szamat (sor x oszlop): ");
    scanf("%d %d", &uj.sor, &uj.oszlop);
    for(int i = 0; i < 4; i++){ /*KEZDETBEN MINDEN �TETB�L NULLA KELL*/
        uj.kert_menuk[i] = 0;
    }
    return uj;
}

/*J�RAT BE�R�SA ADATSZERKEZETBE*/
Jaratok *jarat_beiras(Jaratok *eleje, Jarat uj_jarat){
    Jaratok *uj = (Jaratok*)malloc(sizeof(Jaratok));
    if(uj == NULL) return NULL; /*SIKERTELEN MEM�RIA FOGLAL�S*/
    uj->elem = uj_jarat;
    uj->kov_elem = NULL;
    if(eleje == NULL){ /*�RES LISTA*/
        eleje = uj;
    }else{
        Jaratok *mozgato = eleje;
        while(mozgato->kov_elem != NULL){ /*AMEDDIG AZ UTOLS� ELEMHEZ NEM �RT�NK*/
            mozgato = mozgato->kov_elem;
        }
        mozgato->kov_elem = uj;
    }
    return eleje;
}
