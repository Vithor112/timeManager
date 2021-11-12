#include "param.h"
// Move o Menu
void controlMenu(int row, int col, int caracter_inp, enum Select *flag){
    switch(caracter_inp){
        case KEY_DOWN:
                attrset(COLOR_PAIR(3));
                mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                attrset(COLOR_PAIR(2));
                mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                *flag = SAID;
                break;
        case KEY_UP: 
                attrset(COLOR_PAIR(3));
                mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                attrset(COLOR_PAIR(2));
                mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                *flag = ENTR;
                break;
            default:
                break;
        }
}