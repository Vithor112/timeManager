#include "param.h"
#include "structures.h"

void initializeNCurses(){
    initscr();
    raw();		
    noecho();		
	keypad(stdscr, TRUE);	
    // Determines the answer time to one second, that's important to sync the time!
    halfdelay(10);
    start_color();
    curs_set(0);
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

