#include "libs/param.h"
#include "libs/structures.h"


int main(void){
    // Flag pra Gerenciar o Rastreio do tempo ( indica se já está contando o tempo )
    enum turn is_on = OFF;
    timeTotal totalWorked;          // Armazena tempo trabalhado ( display relógio )
    int totalSecsWorked =0;         // Armazena o tempo trabalhado no período atual
    int Backup_seg = 0;             // Armazena o tempo trabalhado em toda execução do programa          
    time_t initialTime, finalTime;  // Armazena o tempo de entrada e o tempo de saída
    screen scr;                     // Armazena tamanho da tela
    int row_entr = 0;               // Cuida da posição y para printar o histórico;
    int timeLimit = 6*3600;
    char* musicFile =  NULL;
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
    WINDOW *win = NULL;
    while(true){   
        menu = controlMenu(scr, caracter_inp, menu);
        if (caracter_inp == ENTER){ 
            if (menu->flag.initial == NEXT){ // AVANÇAR
                erase();
                caracter_inp = 0;
                break;
            }
            char* str = NULL;
            if (menu->flag.initial == NAMEFILE){
                win = windowCreateWin(menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA O NOME DO ARQUIVO");
                str = windowInputReceiving(win);
                musicFile = (char *) malloc(sizeof(char)*(strlen(str)+1));
                strcpy(musicFile, str);
                windowDestructWin(win, menu, scr);
            }
            if (menu->flag.initial == MAX){
                win = windowCreateWin( menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA O TEMPO MAXIMO (mins)");
                str = windowInputReceiving(win);
                timeLimit = atoi(str)*60;
                windowDestructWin(win, menu, scr);
            }

            if (menu->flag.initial == LOAD_LOG){
                win = windowCreateWin(menu->scr.row-2,menu->scr.col+strlen(menu->str)+2, "INSIRA A DATA DO LOG");
                str = windowInputReceiving(win);
                windowDestructWin(win, menu, scr);
            }
            free(str);
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
        if((totalSecsWorked+Backup_seg) >= timeLimit){
            logsExitRoutine(log, row_entr, is_on, menu, totalWorked);
            if (!musicFile)
                musicFile = "a.mp3";
            char *command = (char *) malloc(sizeof(char)*(strlen(musicFile)+5));
            sprintf(command, "play %s", musicFile);
            system(command);
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


