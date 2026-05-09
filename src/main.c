#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "DataStructures.h"
#include "FileHandler.h"
#include "PrintHandler.h"
#include "Jarat_InputHandler.h"
#include "Foglalas_InputHandler.h"
#include "Jaratok_Print.h"
#include "SeatHandler.h"
#include "FoodHandler.h"
#include "Free_Memory.h"
#include "debugmalloc.h"

int main()
{
    Jaratok *j_eleje = NULL;
    j_eleje = Jaratok_read(j_eleje);
    Foglalasok *f_eleje = NULL;
    f_eleje = Foglalasok_read(f_eleje);
    int menu;
    do{
        alap_opciok_kiir();
        scanf("%d", &menu);
        switch(menu){
            case 1:
                do{
                    adm_opciok_kiir();
                    scanf("%d", &menu);
                    switch(menu){
                        case 1:
                            system("cls");
                            j_eleje = jarat_beiras(j_eleje, jarat_megadas(j_eleje));
                            break;
                        case 2:
                            system("cls");
                            etelek_show_all(j_eleje);
                            getch();
                            break;
                        case 9:
                            system("cls");
                            break;
                        default:
                            break;
                    }
                }while(menu != 9);
                break;
            case 2:
                do{
                    cust_opciok_kiir();
                    scanf("%d", &menu);
                    switch(menu){
                        case 1:
                            system("cls");
                            f_eleje = fogl_beiras(f_eleje, fogl_megadas(j_eleje, f_eleje));
                            getch();
                            break;
                        case 2:
                            system("cls");
                            f_eleje = ules_megadas(f_eleje, j_eleje);
                            break;
                        case 3:
                            system("cls");
                            f_eleje = etel_megadas(f_eleje, j_eleje);
                            getch();
                            break;
                        case 9:
                            system("cls");
                            break;
                        default:
                            break;
                    }
                }while(menu != 9);
                break;
            case 0:
                system("cls");
                break;
            default:
                system("cls");
                alap_opciok_kiir();
                break;
        }
    }while(menu != 0);
    end_credits();
    Jaratok_write(j_eleje, f_eleje);
    Foglalasok_write(f_eleje);
    Jaratok_felszabadit(j_eleje);
    Foglalasok_felszabadit(f_eleje);
    return 0;
}
