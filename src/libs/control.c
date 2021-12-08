#include "param.h"
#include "structures.h"
#define MAX_MENU 1
#define MIN_MENU 0
#define SELECTED 3
#define NORMAL 2

void printMenu(screen scr);
void rotate_flag(enum Select *flag, int rot);

// Move o Menu
void controlMenu(screen scr, int caracter_inp, enum Select *flag){
   linkedStr *menu = menuCreateList();
    switch(caracter_inp){
        case KEY_DOWN:
                printMenu(scr);
                mvprintw(menu->scr.row,menu->scr.col,"%s",menu->str);
                menu = menu->bef;
                attrset(COLOR_PAIR(SELECTED));
                mvprintw(menu->scr.row,menu->scr.col,"%s",menu->str);
                rotate_flag(flag, -1);
                break;
        case KEY_UP: 
                printMenu(scr);
                attrset(COLOR_PAIR(SELECTED));
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


// Função print menu deve usar  menuCreate
void printMenu(screen scr){
    attroff(A_BOLD);
    attrset(COLOR_PAIR(NORMAL));
   // mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"Entrada");
}
