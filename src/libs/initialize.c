#include "param.h"
#include "structures.h"

void initializeNCurses(){
    initscr();
    raw();		
    cbreak();
    noecho();		
	keypad(stdscr, TRUE);	
    // Determines the answer time to one second, that's important to sync the time!
    halfdelay(10);
    start_color();
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(NORMAL, COLOR_BLUE, COLOR_BLACK);
    init_pair(SELECTED, COLOR_BLUE, COLOR_WHITE);
    init_pair(4, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(5, COLOR_YELLOW, COLOR_RED);
}

void initializeTimeTotal(timeTotal *tt){
    tt->hours = 0;
    tt->minutes = 0;
    tt->seconds = 0;
}

void initializeScreen(screen *scr){
    scr->row = 0;
    scr->col = 0;
}

