#include "param.h"
#include "structures.h"
#define MAX_MENU 1
#define MIN_MENU 0

void printMenu(screen scr, enum Select flag);
void rotate_flag(enum Select *flag, int rot);

// Move o Menu
void controlMenu(screen scr, int caracter_inp, enum Select *flag){
    switch(caracter_inp){
        case KEY_DOWN:
                printMenu(scr);
                attrset(COLOR_PAIR(3));
                mvprintw(scr.row/2-2,(scr.col-strlen("Saída"))/2,"%s","Saída");
                rotate_flag(flag, -1);
                break;
        case KEY_UP: 
                printMenu(scr);
                attrset(COLOR_PAIR(3));
                mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"%s","Entrada");
                rotate_flag(flag, 1);
                break;
            default:
                break;
        }
    attrset(COLOR_PAIR(2));
}
void rotate_flag(enum Select *flag, int rot){
        (*flag) += rot;
        if (*flag < 0)
                *flag = MAX_MENU;            
        if (*flag > MAX_MENU)
                *flag = MIN_MENU;
}

void printMenu(screen scr, enum Select flag){
    attroff(A_BOLD);
    attrset(COLOR_PAIR(2));
    mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"Entrada");
    mvprintw(scr.row/2-2,(scr.col-strlen("Saída"))/2,"Saída");
    mvprintw(scr.row/2,(scr.col-strlen("Sair e Salvar"))/2,"Sair e Salvar");
}
