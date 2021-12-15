#include "param.h"
#include "structures.h"

void interfacePrintMenu(screen scr, linkedStr *menu){
    linkedStr *beginning = menu;
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(scr.row/2-6,(scr.col-strlen("-Menu"))/2,"-Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(SELECTED));
    interfacePrintEntry(menu);
    menu = menu->next;
    attrset(COLOR_PAIR(NORMAL));
    for (; menu != beginning; menu = menu->next)
        interfacePrintEntry(menu);
    refresh();
}

void interfacePrintEntry(linkedStr *menu){
        mvprintw(menu->scr.row,menu->scr.col,"%s",menu->str);
}