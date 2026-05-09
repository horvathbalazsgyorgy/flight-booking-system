#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "DataStructures.h"
#include "FileHandler.h"
#include "Jarat_InputHandler.h"
#include "Jaratok_Print.h"
#include "Foglalas_InputHandler.h"
#include "debugmalloc.h"

/*LEFOGLALT �L�SEK F�JLBA �R�SA*/
static void seats_to_write(Jarat elem, Foglalasok *f_eleje, FILE *ptr){
    int idb = 0;
    Foglalasok *mozgo;
    for(mozgo = f_eleje; mozgo != NULL; mozgo = mozgo->kov_fogl){/*AMEDDIG VAN FOGLAL�S*/
        if(strcmp(elem.honnan, mozgo->elem.honnan) == 0 && strcmp(elem.hova, mozgo->elem.hova) == 0){/*TELJES EGYEZ�S*/
            if(strcmp(mozgo->elem.foglalt_helyek[0], "0") != 0){/*ELS� LEFOGLALT HELY NEM NULLA*/
                if(idb != 0) fprintf(ptr, ",");
                fprintf(ptr, "%s", mozgo->elem.foglalt_helyek[0]);
                idb++;
                for(int i = 1; strcmp(mozgo->elem.foglalt_helyek[i], "0") != 0; i++){/*AMEDDIG A LEFOGLALT HELY NEM NULLA*/
                    fprintf(ptr, ",%s", mozgo->elem.foglalt_helyek[i]);
                    idb++;
                }
            }
        }
    }
    if(idb != 0) fprintf(ptr, ";");
}

/*SZTRINGB�L INT*/
static int string_to_int(char *str){
    int r_value = 0; int index = 0;
    int h = strlen(str) - 1; /*SZTRING HOSSZA*/
    int i = pow(10, h); /*10 H-ADIK HATV�NYA*/
    if(strcmp(str, "-1") == 0) return (-1);
    if(h == 0) return (str[0] - '0'); /*HA HOSSZ = 1: VISSZAADJUK �NMAG�BAN*/
    while(str[index] != '\0'){/*AMEDDIG VAN KARAKTER*/
        r_value += (str[index] - '0') * i; /*MEGSZOROZZUK A HELYI�RT�KE SZERINT*/
        i = i / 10;
        index++;
    }
    return r_value;
}

/*J�RATOK BEOLVAS�SA*/
Jaratok *Jaratok_read(Jaratok *j_eleje){
    FILE *file_ptr;
    file_ptr = fopen("src/Jaratok.txt", "r");
    if(file_ptr == NULL){
        perror("Nem letezik a(z) 'Jaratok.txt' nevu fajl"); return NULL;
    }
    char seged_str[1000];
    while(fgets(seged_str, 1000, file_ptr)){
        Jarat uj_j; int index = 0;
        char *felesleg, *kertmenuk;
        strcpy(uj_j.honnan, strtok(seged_str, ";"));
        strcpy(uj_j.hova, strtok(NULL, ";"));
        uj_j.ar = string_to_int(strtok(NULL, ";"));
        uj_j.sor = string_to_int(strtok(NULL, ";"));
        uj_j.oszlop = string_to_int(strtok(NULL, ";"));
        felesleg = strtok(NULL, ";");
        felesleg = strtok(NULL, ";");
        kertmenuk = strtok(NULL, ";");
        if(kertmenuk == NULL) kertmenuk = felesleg; /*HA NEM VOLTAK BEOLVASAND� LEFOGLALT HELYEK*/
        char *seged_menu = strtok(kertmenuk, ",");
        while(index < 3){
            uj_j.kert_menuk[index] = string_to_int(seged_menu);
            index++;
            seged_menu = strtok(NULL, ",");
        }
        char last_menu[2];
        last_menu[0] = seged_menu[0]; /*UTOLS� BEOLVASAND� ELEM*/
        last_menu[1] = '\0'; /*�S �J SOR KARAKTER LEKEZEL�SE*/
        uj_j.kert_menuk[index] = string_to_int(last_menu);
        j_eleje = jarat_beiras(j_eleje, uj_j);
    }
    fclose(file_ptr);
    return j_eleje;
}

/*J�RATOK F�JLBA �R�SA*/
void Jaratok_write(Jaratok *j_eleje, Foglalasok *f_eleje){
    FILE *file_ptr;
    file_ptr = fopen("src/Jaratok.txt", "w");
    if(file_ptr == NULL){
        perror("Sikertelen a fajl megnyitasa!");
        return;
    }
    Jaratok *j_mozgo;
    for(j_mozgo = j_eleje; j_mozgo != NULL; j_mozgo = j_mozgo->kov_elem){
        fprintf(file_ptr, "%s;%s;%d;%d;%d;%d;", j_mozgo->elem.honnan, j_mozgo->elem.hova, j_mozgo->elem.ar,
                j_mozgo->elem.sor, j_mozgo->elem.oszlop, Free_seats_count(j_mozgo->elem, f_eleje));
        seats_to_write(j_mozgo->elem, f_eleje, file_ptr); /*LEFOGLALT HELYEK*/
        fprintf(file_ptr, "%d", j_mozgo->elem.kert_menuk[0]);
        for(int i = 1; i < 4; i++){
            fprintf(file_ptr, ",%d", j_mozgo->elem.kert_menuk[i]);
        }
        fprintf(file_ptr, "\n");
    }
    fclose(file_ptr);
}

/*FOGLAL�SOK BEOLVAS�SA*/
Foglalasok *Foglalasok_read(Foglalasok *f_eleje){
    FILE *file_ptr;
    file_ptr = fopen("src/Foglalasok.txt", "r");
    if(file_ptr == NULL){
        perror("Nem letezik a(z) 'Foglalasok.txt' nevu fajl"); return NULL; }
    char seged_str[1000];
    while(fgets(seged_str, 1000, file_ptr)){
        int index = 0;
        char *s, *ss;
        Foglalas uj_f;
        strcpy(uj_f.foglalt_helyek[0], "0");
        strcpy(uj_f.nev, strtok(seged_str, ";"));
        strcpy(uj_f.honnan, strtok(NULL, ";"));
        strcpy(uj_f.hova, strtok(NULL, ";"));
        uj_f.ar = string_to_int(strtok(NULL, ";"));
        s = strtok(NULL, ";");
        ss = strtok(NULL, ";");
        char *s_seged = strtok(s, ",");
        if(strlen(s_seged) == 4){ /*BEOLVASOTT ELEM EGY LEFOGLALT HELY*/
            while(s_seged != NULL){
                strcpy(uj_f.foglalt_helyek[index], s_seged);
                index++;
                s_seged = strtok(NULL, ",");
            } strcpy(uj_f.foglalt_helyek[index], "0");
        }
        if(ss != NULL){ s = ss; s_seged = strtok(s, ","); } /*NEM VOLTAK LEFOGLALT HELYEK*/
        index = 0;
        while(index < 3){
            uj_f.valasztott_menuk[index] = string_to_int(s_seged);
            index++;
            s_seged = strtok(NULL, ",");
        }
        char last_menu[2];
        last_menu[0] = s_seged[0]; last_menu[1] = '\0'; /*UTOLS� ELEM �S �J SOR KARAKTER LEKEZEL�SE*/
        uj_f.valasztott_menuk[index] = string_to_int(last_menu);
        f_eleje = fogl_beiras(f_eleje, uj_f);
        }
    fclose(file_ptr);
    return f_eleje;
}

/*FOGLAL�SOK F�JLBA �R�SA*/
void Foglalasok_write(Foglalasok *f_eleje){
    FILE *file_ptr;
    file_ptr = fopen("src/Foglalasok.txt", "w");
    if(file_ptr == NULL){
        perror("Sikertelen a fajl megnyitasa!");
        return;
    }
    Foglalasok *f_mozgo;
    for(f_mozgo = f_eleje; f_mozgo != NULL; f_mozgo = f_mozgo->kov_fogl){
        fprintf(file_ptr, "%s;%s;%s;%d;", f_mozgo->elem.nev, f_mozgo->elem.honnan, f_mozgo->elem.hova, f_mozgo->elem.ar);
        if(strcmp(f_mozgo->elem.foglalt_helyek[0], "0") != 0){
            fprintf(file_ptr, "%s", f_mozgo->elem.foglalt_helyek[0]);
            for(int i = 1; strcmp(f_mozgo->elem.foglalt_helyek[i], "0") != 0; i++){
                fprintf(file_ptr, ",%s", f_mozgo->elem.foglalt_helyek[i]);
            }
            fprintf(file_ptr, ";");
        }
        fprintf(file_ptr, "%d", f_mozgo->elem.valasztott_menuk[0]);
        for(int i = 1; i < 4; i++){
            fprintf(file_ptr, ",%d", f_mozgo->elem.valasztott_menuk[i]);
        }
        fprintf(file_ptr, "\n");
    }
    fclose(file_ptr);
}
