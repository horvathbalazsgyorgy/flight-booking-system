#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

Jaratok *Jaratok_read(Jaratok *j_eleje);

void Jaratok_write(Jaratok *j_eleje, Foglalasok *f_eleje);

Foglalasok *Foglalasok_read(Foglalasok *f_eleje);

void Foglalasok_write(Foglalasok *f_eleje);

#endif // FILEHANDLER_H_INCLUDED
