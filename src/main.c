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

    FILE *log = logsOpenLog();
    
    // Inicializando Ncurses e imprimindo o menu
    initializeScreen(&scr);
    initializeTimeTotal(&totalWorked);
    initializeNCurses();
    getmaxyx(stdscr,scr.row,scr.col);
    interfacePrintMenu(scr);

    int caracter_inp;
    linkedStr *menu = menuCreateList();
    while(true){    
        
        menu = controlMenu(scr, caracter_inp, menu);

        // Atualiza o Relógio no canto direito inferior
        mvprintw(scr.row-1,0,"%s",asctime(timeGetTime()));

        // Adiciona uma Entrada e começa a contar o tempo  
        if (caracter_inp == ENTER && menu->flag == ENTRY && is_on == OFF){
            logsPrintEntry(&row_entr,log, &is_on);
            time(&initialTime);
        }
        // Adiciona uma Saida e para de contar o tempo, salvando-o na var Backup_seg
        if (caracter_inp == ENTER && menu->flag == FINISH && row_entr && is_on == ON){
            logsPrintEntry(&row_entr,log, &is_on); 
            Backup_seg += totalSecsWorked; 
            totalSecsWorked = 0;           
        }

        if (caracter_inp == ENTER && menu->flag == SAVE){
            logsExitRoutine(log, row_entr, is_on, menu, totalWorked);
            exit(0);
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
        if((totalSecsWorked+Backup_seg) >= SEGUNDOS_TRABALHO){
            logsExitRoutine(log, row_entr, is_on, menu, totalWorked);
            system("play "MUSICA_ARQUIVO);
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


