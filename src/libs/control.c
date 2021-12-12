#include "param.h"
#include "structures.h"


void printMenu(linkedStr *menu);
void printEntry(linkedStr *menu);

// Move o Menu
linkedStr *controlMenu(screen scr, int caracter_inp, linkedStr *menu){
        switch(caracter_inp){
                case KEY_DOWN:
                        printMenu(menu);
                        menu = menu->next;
                        attrset(COLOR_PAIR(SELECTED));
                        interfacePrintEntry(menu);
                        break;
                case KEY_UP: 
                        printMenu(menu);
                        menu = menu->bef;
                        attrset(COLOR_PAIR(SELECTED));
                        interfacePrintEntry(menu);
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
        interfacePrintEntry(menu);  
}

