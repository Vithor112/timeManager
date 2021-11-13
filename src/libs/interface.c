#include "param.h"
// Printa Registro  e atualiza variáveis 
void interfacePrintEntry(int *row_entr, struct tm *time, enum turn *is_on){
    char str[30];
    if (*is_on == OFF){
        strcpy(str, "Entrada: ");
        *is_on = ON;
    }
    else {
        strcpy(str,"Saida: ");
        *is_on = OFF;
    }

    mvprintw(*row_entr,0,"%s %dh %dm %ds",str, time->tm_hour, time->tm_min, time->tm_sec);
    (*row_entr)++;
}



void interfacePrintMenu(int row, int col){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(row/2-6,(col-strlen("-Menu"))/2,"-Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(3));
    mvprintw(row/2-4,(col-strlen("Entrada"))/2,"Entrada");
    attrset(COLOR_PAIR(2));
    mvprintw(row/2-2,(col-strlen("Saída"))/2,"Saída");
}