#include "param.h"
#include "structures.h"
// Printa Registro  e atualiza variáveis 
void interfacePrintEntry(int *row_entr, FILE *log, enum turn *is_on){
    struct tm *time = timeGetTime();
    char str[30];
    if (*is_on == OFF){
        strcpy(str, "Entrada: ");
        fprintf(log, "Entry,");
        *is_on = ON;
    }
    else {
        strcpy(str,"Saida: ");
        fprintf(log, "Exit,");
        *is_on = OFF;
    }
    fprintf(log, "%d,%d,%d\n", time->tm_hour, time->tm_min, time->tm_sec);
    mvprintw(*row_entr,0,"%s %dh %dm %ds",str, time->tm_hour, time->tm_min, time->tm_sec);
    (*row_entr)++;
}



void interfacePrintMenu(screen scr){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(scr.row/2-6,(scr.col-strlen("-Menu"))/2,"-Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(3));
    mvprintw(scr.row/2-4,(scr.col-strlen("Entrada"))/2,"Entrada");
    attrset(COLOR_PAIR(2));
    mvprintw(scr.row/2-2,(scr.col-strlen("Saída"))/2,"Saída");
    mvprintw(scr.row/2,(scr.col-strlen("Sair e Salvar"))/2,"Sair e Salvar");
}