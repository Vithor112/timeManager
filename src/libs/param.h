#ifndef PARAM
#define PARAM 1

#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "structures.h"

#define MAIN_MENU_FILE "./options/mainMenu.txt"
#define MAIN_MENU 0

#define INITIAL_MENU_FILE "./options/initialMenu.txt"
#define INITIAL_MENU 1

#define TIME_LIMIT 60*60*6
#define MUSIC_FILE "a.mp3"
#define MUSIC_TIME 345

#define TIMETOTALPRINT(x) x.hours,x.minutes,x.seconds
#define ENTER 10
#define SELECTED 3
#define NORMAL 2

// Protótipo funções

void initializeNCurses();
void initializeTimeTotal(timeTotal *tt);
void initializeScreen(screen *scr);

void interfacePrintMenu(screen scr, linkedStr *menu);
void interfacePrintEntry(linkedStr *menu);

struct tm *timeGetTime();

linkedStr *controlMenu(screen scr, int caracter_inp, linkedStr *menu);

linkedStr *menuCreateList(char *file_name, int option, screen scr);

linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr, int option);
linkedStr *linkedDestruct(linkedStr *lin);

void logsExitRoutine(FILE *log, int row_entr, enum turn is_on, linkedStr *menu, timeTotal totalWorked);
FILE *logsOpenLog();
void logsPrintEntry(int *row_entr,FILE *log, enum turn *is_on);

#endif
