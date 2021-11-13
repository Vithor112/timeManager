#include "param.h"
// Move o Menu
void controlMenu(screen scr, int caracter_inp, enum Select *flag){
    switch(caracter_inp){
        case KEY_DOWN:
                attrset(COLOR_PAIR(3));
                mvprintw(scr.row/2-2,(scr.col-strlen("Saída"))/2,"%s","Saída");
                attrset(COLOR_PAIR(2));
                mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"%s","Entrada");
                *flag = SAID;
                break;
        case KEY_UP: 
                attrset(COLOR_PAIR(3));
                mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"%s","Entrada");
                attrset(COLOR_PAIR(2));
                mvprintw(scr.row/2-2,(scr.col-strlen("Saída"))/2,"%s","Saída");
                *flag = ENTR;
                break;
            default:
                break;
        }
}