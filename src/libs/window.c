#include "param.h"
#include "structures.h"

void windowDestructWin(WINDOW *win, linkedStr *menu, screen scr){
    werase(win); 
    wrefresh(win);
    curs_set(0);
    refresh();
    delwin(win);
}

WINDOW* windowCreateWin(int y, int x, char *string){
    WINDOW *win;
    int width = strlen(string)+4;
    win = newwin(4,width,y, x);
    wattrset(win,COLOR_PAIR(BACKGROUND_WIN));
    for (int j  = 1; j < 3; j++){
        wmove(win,j,0);
        for (int i = 0; i < strlen(string)+4;i++)
            wprintw(win, " ");
    }
    wmove(win,2,3);
    wattrset(win,COLOR_PAIR(BACKGROUND_TYPE));
    for (int i = 0; i < width - 6;i++)
        wprintw(win, " ");
    wattrset(win,COLOR_PAIR(BACKGROUND_WIN));
    curs_set(2);
    box(win,0,0);
    wmove(win, 1,2);
    wprintw(win, string);
    wmove(win,2,3);
    wrefresh(win);
    return win;
}

void windowInputReceiving(WINDOW* win){
    int caracter_inp = -1;
    int initial_x, initial_y;
    int max_x, max_y;
    getmaxyx(win, max_y, max_x);
    getyx(win, initial_y,initial_x);
    while(caracter_inp != ESQ){
        int x = 0, y;
        getyx(win,y,x);
        if (isalnum(caracter_inp) && x < max_x - 3){
            wattrset(win, COLOR_PAIR(SELECTED));
            waddch(win, caracter_inp);
            getyx(win,y,x);
            if (x == max_x - 3)
                wmove(win, y,x-1);
            wrefresh(win);
        }    
        if (caracter_inp == BACKSPACE && x+1 != initial_x){ 
            wattrset(win, COLOR_PAIR(BACKGROUND_TYPE));
            wmove(win, y,x);
            waddch(win, SPACE);
            if (x == initial_x)
                wmove(win, y,x);
            else
                wmove(win, y,x-1);
            wrefresh(win);
        }      
        wrefresh(win);
        caracter_inp  = getch();
    }   
}