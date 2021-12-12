#include "param.h"
#include "structures.h"

void interfacePrintMenu(screen scr, linkedStr *menu){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(NORMAL, COLOR_BLUE, COLOR_BLACK);
    init_pair(SELECTED, COLOR_BLUE, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(scr.row/2-6,(scr.col-strlen("-Menu"))/2,"-Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(SELECTED));
    interfacePrintEntry(menu);
    menu = menu->next;
    attrset(COLOR_PAIR(NORMAL));
    interfacePrintEntry(menu);
    menu = menu->next;
    interfacePrintEntry(menu);
}

void interfacePrintEntry(linkedStr *menu){
        mvprintw(menu->scr.row,menu->scr.col,"%s",menu->str);
}