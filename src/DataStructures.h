#ifndef DATASTRUCTURES_H_INCLUDED
#define DATASTRUCTURES_H_INCLUDED

extern char *etel[];

typedef struct Jarat{
    char honnan[50];
    char hova[50];
    int ar;
    int sor;
    int oszlop;
    int kert_menuk[4];
}Jarat;

typedef struct Foglalas{
    char nev[50];
    char honnan[50];
    char hova[50];
    int ar;
    char foglalt_helyek[256][5];
    int valasztott_menuk[4];
}Foglalas;

typedef struct Jaratok{
    Jarat elem;
    struct Jaratok *kov_elem;
}Jaratok;

typedef struct Foglalasok{
    Foglalas elem;
    struct Foglalasok *kov_fogl;
}Foglalasok;

#endif // DATASTRUCTURES_H_INCLUDED
