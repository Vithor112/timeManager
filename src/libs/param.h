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
#define ENTER 10

// Protótipo funções

void initializeNCurses();
void initializeTimeTotal(timeTotal *tt);
void initializeScreen(screen *scr);

void interfacePrintMenu(screen scr);

struct tm *timeGetTime();

linkedStr *controlMenu(screen scr, int caracter_inp, linkedStr *menu);

linkedStr *menuCreateList();

linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr);
linkedStr *linkedDestruct(linkedStr *lin);

void logsExitRoutine(FILE *log, int row_entr, enum turn is_on, linkedStr *menu, timeTotal totalWorked);
FILE *logsOpenLog();
void logsPrintEntry(int *row_entr,FILE *log, enum turn *is_on);

#endif
