#include "libs/param.h"

int main(void){
    // Flag pra Gerenciar o Rastreio do tempo ( indica se já está contando o tempo )
    enum turn is_on = OFF;
    // Flag pra Gerenciar o Menu ( indica a opção selecionada )
    enum Select flag = ENTR;

    timeTotal totalWorked; 
    int segundosTrabalhadosTotais =0,  Backup_seg = 0;
    struct tm *timeNow;
    time_t tempoInicial, tempoFinal;
    int row,col, row_entr = 0; // row_entr = Variável que cuida da posição y para printar o histórico;
    
    // Inicializando Ncurses e imprimindo o menu
    initializeTimeTotal(&totalWorked);
    initializeNCurses();
    getmaxyx(stdscr,row,col);
    interfacePrintMenu(SCREEN);

    int caracter_inp;
    while(true){    
             
        controlMenu(SCREEN, caracter_inp, &flag);

        // Atualiza o Relógio no canto direito inferior
        mvprintw(row-1,0,"%s",asctime(timeGetTime()));

        // Adiciona uma Entrada e começa a contar o tempo  
        if (caracter_inp == 10 && flag == ENTR && is_on == OFF){
            timeNow = timeGetTime();
            interfacePrintEntry(&row_entr, timeNow, &is_on);
            time(&tempoInicial);
        }
        // Adiciona uma Saida e para de contar o tempo, salvando-o na var Bakcup_seg
        if (caracter_inp == 10 && flag == SAID && row_entr && is_on == ON){
            timeNow = timeGetTime();
            interfacePrintEntry(&row_entr, timeNow, &is_on);
            Backup_seg += segundosTrabalhadosTotais; // Coloca o tempo já contado em uma variável  
            segundosTrabalhadosTotais = 0;           // E zera esse tempo  
        }

        // Conta o tempo
        if (is_on == ON){
            time(&tempoFinal);
            segundosTrabalhadosTotais =  tempoFinal - tempoInicial;                 // Atualiza o tempo já trabalhado
            totalWorked.hours = (Backup_seg + segundosTrabalhadosTotais)/3600;      // Somando o tempo j́a contado previamente com o tempo contado agora obtém o total
            totalWorked.minutes = ((Backup_seg + segundosTrabalhadosTotais)%3600)/60;
            totalWorked.seconds = (Backup_seg + segundosTrabalhadosTotais)%60;
        }
        // Encerra se cumprir todas as horas diárias e toca uma música
        if((segundosTrabalhadosTotais+Backup_seg) >= SEGUNDOS_TRABALHO){
            endwin();
            system("play "MUSICA_ARQUIVO);
            exit(0);
        }
        // Imprime a quantidade de tempo trabalhado
        mvprintw(0,col-28,"Tempo trabalhado: %2d :%2d :%2d", TIMETOTALPRINT(totalWorked));
        caracter_inp = getch();
        refresh();
    }
    endwin();
    return 0;
}




