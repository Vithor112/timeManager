#include "param.h"
void initializeNCurses(){
    initscr();
    raw();		
    noecho();		
	keypad(stdscr, TRUE);	
    // Determina tempo de resposta para 1 seg, importante para sincronia do tempo!
    halfdelay(10);
    start_color();
}

void initializeTimeTotal(timeTotal *tt){
    tt->hours = 0;
    tt->minutes = 0;
    tt->seconds = 0;
}