#include <stdlib.h>
#include <stdio.h>
#include "PrintHandler.h"
#include "debugmalloc.h"

/*FÖMENÜ*/
void alap_opciok_kiir(void){
    system("cls");
    printf(
"                . .                                                                            . .\n"
"              .   /                                                                            \\   .\n"
"            _/   /                                                                              \\   \\_\n"
"           ()____)       _____   _______________________________________________   _____        (____()\n"
"         ()____)        /    /  | ________ ______  __________ ________________  |  \\   \\         (____()\n"
"    _____/   /_________/    /   | ___  __ )___   |/  /___    |____  _/___  __ \\ |   \\   \\__________\\   \\_____\n"
"  _/_)  /   /) () () ()    /    | __  __  |__  /|_/ / __  /| | __  /  __  /_/ / |    \\    () () () (\\   \\  (_\\_\n"
" /|    ===================/     | _  /_/ / _  /  / /  _  ___ |__/ /   _  _, _/  |     \\===================    |\\\n"
" \\|______________________/      | /_____/  /_/  /_/   /_/  |_|/___/   /_/ |_|   |      \\______________________|/\n"
"    _/   /                      |_______________________________________________|                      \\   \\_\n"
"   ()____)                                                                                             (____()\n"
"  ()____)                                                                                               (____()\n"
"  /   /                                                                                                   \\   \\\n"
"  .  /                                                                                                     \\  .\n"
"   ..                                                                                                       ..\n"
        "\nUdvozli a BMAir!\n"
        "____________________________________________\n"
        "Kerem valasszon az alabbi lehetosegek kozul:\n"
        "[1] Adminisztracios mod\n"
        "[2] Vasarloi mod\n"
        "[0] Kilepes\n"
        "____________________________________________\n"
        );
        //ASCII-ART (BMEAIR) SOURCE: https://patorjk.com/software/taag/#p=display&h=0&v=1&f=Speed&t=BMAIR (2023.11.24)
        //ASCII-ART (AIRPLANE By Gurno) SOURCE: https://ascii.co.uk/art/air (2023.11.24)
}

/*ADMINISZTRACIOS MOD*/
void adm_opciok_kiir(void){
    system("cls");
    printf(
        "Udvozlom! Kerem valasszon:\n"
        "____________________________________\n"
        "[1] Jarat megadasa\n"
        "[2] Szukseges etelek kilistazasa\n"
        "[9] Kilepes\n"
        "____________________________________\n");
}

/*VÁSÁRLÓI MÓD*/
void cust_opciok_kiir(void){
    system("cls");
    printf(
           "Udvozlom! Kerem valasszon:\n"
           "_______________________________________\n"
           "[1] Repulojegy vasarlasa\n"
           "[2] Ulohely kivalasztasa\n"
           "[3] Etel kivalasztasa\n"
           "[9] Kilepes\n"
           "_______________________________________\n");
}

/*KILÉPÉS*/
void end_credits(void){
    printf("Koszonjuk, hogy legitarsasagunkat valasztotta! Varjuk vissza!\n");
    printf(
            " __________________________________________________________________________________\n"
            "|                                                                .____   __ _      |\n"
            "|   __o__   _______ _ _  _                                     /     /             |\n"
            "|   \\    ~\\                                                  /      /              |\n"
            "|     \\     '\\                                         ..../      .'               |\n"
            "|      . ' ' . ~\\                                      ' /       /                 |\n"
            "|     .  _    .  ~ \\  .+~\\~ ~ ' ' " " ' ' ~ - - - - - -''_      /                     |\n"
            "|    .  <#  .  - - -/' . ' \\  __                          '~ - \\                   |\n"
            "|     .. -           ~-.._ / |__|  ( )  ( )  ( )  0  o    _ _    ~ .               |\n"
            "|   .-'                                               .- ~    '-.    -.            |\n"
            "|  <                      . ~ ' ' .             . - ~             ~ -.__~_. _ _    |\n"
            "|    ~- .       N121PP  .          . . . . ,- ~                                    |\n"
            "|          ' ~ - - - - =.   <#>    .         \\.._                                  |\n"
            "|                      .     ~      ____ _ .. ..  .- .                             |\n"
            "|                       .         '        ~ -.        ~ -.                        |\n"
            "|                         ' . . '               ~ - .       ~-.                    |\n"
            "|                                                     ~ - .      ~ .               |\n"
            "|                                                            ~ -...0..~. ____      |\n"
            "|__________________________________________________________________________________|\n");
            //ASCII-ART (Cessna 402 (Wings) By Dick Williams) SOURCE: https://ascii.co.uk/art/cessna (2023.11.24)
}
