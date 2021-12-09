#include "param.h"
#include "structures.h"

// Prints a register in a log file and update variables
void logsPrintEntry(int *row_entr, FILE *log, enum turn *is_on){
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

//  Deallocate memory, exit NCurses, print exit in file, if necessary, and save log file
void logsExitRoutine(FILE *log, int row_entr, enum turn is_on, linkedStr *menu, timeTotal totalWorked){
        endwin();
        linkedDestruct(menu);
        if (is_on == ON)
            logsPrintEntry(&row_entr,log, &is_on);
        fprintf(log, "%d:%d:%d\n", TIMETOTALPRINT(totalWorked));
        fclose(log);
}


// Create new Csv File and return pointer to it
FILE *logsOpenLog(){
    struct tm *timeNow;
    timeNow = timeGetTime();
    char str[30];
    sprintf(str, "Log-%d-%d-%d.csv", timeNow->tm_year+1900, timeNow->tm_mon+1, timeNow->tm_mday);
    FILE *ret = fopen(str, "w");
    if (ret == NULL){
        fprintf(stderr, "ERROR OPENING FILE");
        exit(1);
    }
    fprintf(ret, "Type,Hours,Minutes,Seconds\n");
    return ret;
}