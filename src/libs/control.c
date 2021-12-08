#include "param.h"
#include "structures.h"
#define MAX_MENU 1
#define MIN_MENU 0
#define SELECTED 3
#define NORMAL 2

void printMenu(linkedStr *menu);
void printEntry(linkedStr *menu);

// Move o Menu
linkedStr *controlMenu(screen scr, int caracter_inp, linkedStr *menu){
        switch(caracter_inp){
                case KEY_DOWN:
                        printMenu(menu);
                        menu = menu->next;
                        attrset(COLOR_PAIR(SELECTED));
                        printEntry(menu);
                        break;
                case KEY_UP: 
                        printMenu(menu);
                        menu = menu->bef;
                        attrset(COLOR_PAIR(SELECTED));
                        printEntry(menu);
                        break;
                default:
                        break;
                }
                attrset(COLOR_PAIR(NORMAL));
                return menu;
}


// Função print menu deve usar  menuCreate
void printMenu(linkedStr *menu){
        attroff(A_BOLD);
        attrset(COLOR_PAIR(NORMAL));
        printEntry(menu);  
}

void printEntry(linkedStr *menu){
        mvprintw(menu->scr.row,menu->scr.col,"%s",menu->str);
}
