#include <stdbool.h>
#ifndef LOGICAL_H_INCLUDED
#define LOGICAL_H_INCLUDED

bool name_exists(Foglalasok *eleje, char *name);

bool foglalt_e(Foglalasok *eleje, Foglalas elem, char *ules);

bool jarat_exists(Jaratok *eleje, char *hon, char *hov);

bool food_exists(Jarat elem);

#endif // LOGICAL_H_INCLUDED
