#include "libs/param.h"
#include "libs/structures.h"

void destructWin(WINDOW *win, linkedStr *menu, screen scr){
    wclear(win); 
    wrefresh(win);
    delwin(win);
    curs_set(0);
}

WINDOW*createWin(int y, int x, char *string){
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

int main(void){
    // Flag pra Gerenciar o Rastreio do tempo ( indica se já está contando o tempo )
    enum turn is_on = OFF;
    timeTotal totalWorked;          // Armazena tempo trabalhado ( display relógio )
    int totalSecsWorked =0;         // Armazena o tempo trabalhado no período atual
    int Backup_seg = 0;             // Armazena o tempo trabalhado em toda execução do programa          
    time_t initialTime, finalTime;  // Armazena o tempo de entrada e o tempo de saída
    screen scr;                     // Armazena tamanho da tela
    int row_entr = 0;               // Cuida da posição y para printar o histórico;

    FILE *log = logsOpenLog();
    
    // Inicializando Ncurses e imprimindo o menu
    initializeScreen(&scr);
    initializeNCurses();
    getmaxyx(stdscr,scr.row,scr.col);
    initializeTimeTotal(&totalWorked);

    // INITIAL MENU
    linkedStr *menu = menuCreateList(INITIAL_MENU_FILE, INITIAL_MENU, scr);
    interfacePrintMenu(scr, menu);
    int caracter_inp;
    WINDOW *test = NULL;
    while(true){   
        menu = controlMenu(scr, caracter_inp, menu);
        if (caracter_inp == ENTER){ 
            if (menu->flag.initial == NEXT){ // AVANÇAR
                erase();
                caracter_inp = 0;
                break;
            }
            if (menu->flag.initial == NAMEFILE){
                createWin( menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA O NOME DO ARQUIVO");
                while(true);
            }
            if (menu->flag.initial == MAX){
                createWin( menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA O TEMPO MAXIMO");
                while(true);
                
            }

            if (menu->flag.initial == LOAD_LOG){
                test = createWin(menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA A DATA DO LOG");
                caracter_inp = 0;
                while(caracter_inp != ESQ){
                    // if (isalnum(caracter_inp))
                    wattrset(test, COLOR_PAIR(SELECTED));
                    waddch(test, 'a');
                    wrefresh(test);
                    caracter_inp  = getch();
                }
                destructWin(test, menu, scr);
            }
        }    
        caracter_inp = getch();
        refresh();
    }
    // MAIN MENU
    menu = menuCreateList(MAIN_MENU_FILE, MAIN_MENU, scr);
    interfacePrintMenu(scr, menu);




    while(true){    
        
        menu = controlMenu(scr, caracter_inp, menu);

        // Atualiza o Relógio no canto direito inferior
        mvprintw(scr.row-1,0,"%s",asctime(timeGetTime()));
        if (caracter_inp == ENTER){
            // Adiciona uma Entrada e começa a contar o tempo  
            if (menu->flag.main == ENTRY && is_on == OFF){
                logsPrintEntry(&row_entr,log, &is_on);
                time(&initialTime);
            }
            // Adiciona uma Saida e para de contar o tempo, salvando-o na var Backup_seg
            if (menu->flag.main == FINISH && row_entr && is_on == ON){
                logsPrintEntry(&row_entr,log, &is_on); 
                Backup_seg += totalSecsWorked; 
                totalSecsWorked = 0;           
            }

            if (menu->flag.main == SAVE){
                logsExitRoutine(log, row_entr, is_on, menu, totalWorked);
                exit(0);
            }
    }

        // Conta o tempo e atualiza o total contado
        if (is_on == ON){
            time(&finalTime);
            totalSecsWorked =  finalTime - initialTime;                
            totalWorked.hours = (Backup_seg + totalSecsWorked)/3600;     
            totalWorked.minutes = ((Backup_seg + totalSecsWorked)%3600)/60;
            totalWorked.seconds = (Backup_seg + totalSecsWorked)%60;
        }
        // Encerra se cumprir todas as horas diárias e toca uma música
        if((totalSecsWorked+Backup_seg) >= TIME_LIMIT){
            logsExitRoutine(log, row_entr, is_on, menu, totalWorked);
            system("play "MUSIC_FILE);
            sleep(MUSIC_TIME);
            exit(0);
        }
        // Imprime a quantidade de tempo trabalhado
        mvprintw(0,scr.col-28,"Tempo trabalhado: %2d :%2d :%2d", TIMETOTALPRINT(totalWorked));
        caracter_inp = getch();
        refresh();
    }
    endwin();
    return 0;
}


