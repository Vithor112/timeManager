#ifndef PARAM
#define PARAM 1

#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "structures.h"
#include <ctype.h>

#define MAIN_MENU_FILE "./options/mainMenu.txt"
#define MAIN_MENU 0

#define INITIAL_MENU_FILE "./options/initialMenu.txt"
#define INITIAL_MENU 1


#define MUSIC_TIME 500 // AVERAGE

#define TIMETOTALPRINT(x) x.hours,x.minutes,x.seconds
#define ENTER 10
#define ESQ 27
#define BACKSPACE 263
#define SPACE 32
#define SELECTED 3
#define NORMAL 2
#define BACKGROUND_WIN 4
#define BACKGROUND_TYPE 5

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


void windowDestructWin(WINDOW *win, linkedStr *menu, screen scr);
WINDOW* windowCreateWin(int y, int x, char *string);
char * windowInputReceiving(WINDOW* win);

#endif
