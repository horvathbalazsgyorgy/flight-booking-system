#include <stdlib.h>
#include "DataStructures.h"
#include "Free_Memory.h"
#include "debugmalloc.h"

/*JÁRATOK FELSZABADÍTÁSA*/
void Jaratok_felszabadit(Jaratok *eleje){
    Jaratok *szabadito = eleje;
    while(szabadito != NULL){
        Jaratok *kov_jarat = szabadito->kov_elem;
        free(szabadito);
        szabadito = kov_jarat;
    }
}

/*FOGLALÁSOK FELSZABADÍTÁSA*/
void Foglalasok_felszabadit(Foglalasok *eleje){
    Foglalasok *felszabadit = eleje;
    while(felszabadit != NULL){
        Foglalasok *kov_fogl = felszabadit->kov_fogl;
        free(felszabadit);
        felszabadit = kov_fogl;
    }
}
