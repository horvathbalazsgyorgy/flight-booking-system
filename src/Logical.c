#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DataStructures.h"
#include "Logical.h"
#include "debugmalloc.h"

/*NÉV MEGLÉTÉNEK ELLENÕRZÉSE*/
bool name_exists(Foglalasok *eleje, char *name){
    Foglalasok *mozgas;
    for(mozgas = eleje; mozgas != NULL; mozgas = mozgas->kov_fogl){ /*LISTA VÉGÉIG*/
        if(strcmp(mozgas->elem.nev, name) == 0) return true; /*TELJES EGYEZÉS*/
    }
    return false;
}

/*ÜLÉS FOGLALTSÁGA*/
bool foglalt_e(Foglalasok *eleje, Foglalas elem, char *ules){
    Foglalasok *mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov_fogl){
        if(strcmp(mozgo->elem.honnan, elem.honnan) == 0 && strcmp(mozgo->elem.hova, elem.hova) == 0){ /*TELJES EGYEZÉS*/
            for(int i = 0; strcmp(mozgo->elem.foglalt_helyek[i], "0") != 0; i++){ /*AMEDDIG VAN LEFOGLALT HELY*/
                if(strcmp(mozgo->elem.foglalt_helyek[i], ules) == 0) return true; /*TELJES EGYEZÉS*/
            }
        }
    }
    return false;
}

/*JÁRAT LÉTEZÉSE*/
bool jarat_exists(Jaratok *eleje, char *hon, char *hov){
    Jaratok *mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov_elem){ /*LISTA VÉGÉIG*/
        if(strcmp(mozgo->elem.honnan, hon) == 0 && strcmp(mozgo->elem.hova, hov) == 0) return true; /*TELJES EGYEZÉS ESETÉN*/
    }
    return false;
}

/*ÉTEL LÉTEZÉSE*/
bool food_exists(Jarat elem){
    int db = 0;
    for(int i = 0; i < 4; i++){
        if(elem.kert_menuk[i] != 0) db++; /*HA MÁR RENDELTEK*/
    }
    return db == 0 ? false : true;
}
