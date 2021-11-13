#ifndef PARAM
#define PARAM 1

#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SEGUNDOS_TRABALHO 120
#define MUSICA_ARQUIVO "a.mp3"
#define SCREEN row,col

#define TIMETOTALPRINT(x) x.hours,x.minutes,x.seconds

// Flags 
enum turn {ON, OFF};
enum Select {ENTR,SAID};

// Structs 
typedef struct timeTotal {
    int hours;
    int minutes;
    int seconds;
}timeTotal;

// Protótipo funções
void initializeNCurses();
void interfacePrintMenu(int row, int col);
struct tm *timeGetTime();
void controlMenu(int row, int col, int caracter_inp, enum Select *flag);
void initializeTimeTotal(timeTotal *tt);
void interfacePrintEntry(int *row_entr, struct tm *time, enum turn *is_on);

#endif
