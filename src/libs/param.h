#ifndef PARAM
#define PARAM 1

#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "structures.h"


#define SEGUNDOS_TRABALHO 120
#define MUSICA_ARQUIVO "a.mp3"

#define TIMETOTALPRINT(x) x.hours,x.minutes,x.seconds

// Protótipo funções

void initializeNCurses();
void interfacePrintMenu(screen scr);
struct tm *timeGetTime();
void controlMenu(screen scr, int caracter_inp, enum Select *flag);
void initializeTimeTotal(timeTotal *tt);
void interfacePrintEntry(int *row_entr,FILE *log, enum turn *is_on);
void initializeScreen(screen *s);
linkedStr *menuCreateList();
linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr);
void screenInitialize(screen *scr);

#endif
