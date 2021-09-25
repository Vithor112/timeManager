#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SEGUNDOS_TRABALHO 6*3600

/*Problema: É que o site de bate o ponto não registra o horário que eu já trabalhei. Então eu quero um programa que cuide do horário que eu já trabalhei e receba meus pontos de entrada e saída.
Continue rodando até fechar 6 horas trabalhadas.

- Contar o Tempo:
    - Marca um tempo inicial ( TI );
    - Tempo atual ( Olhando pro relógio ) -  TI = Tempo que já passou;
Entradas e saídas: 
    - Começar a contar o tempo quando tem entrada e parar quando tem saída;
    - Armazenar total de horas trabalhadas;
Encerrar o Programa: 
    - Somente quando ultrapassar 6 horas diárias
    - Dar Aviso sonoro
Previsão de Saída; * Tirar horas já trabalhadas da previsão de saída

*/


/* 
    localtime() struct time
    time() Retorna o tempo em segundos desde 1970 ( retorna um time_t) 
    struct tm Campo pra seg, min, hora, dia, mes ,ano
    time_t segundos desde 1970 tipo inteiro
*/

struct tm *get_time();

enum turn {ON, OFF};
enum Select {ENTR,SAID};

int main(void){
    // Flag pra Gerenciar o Rastreio do tempo 
    enum turn is_on = OFF;
    // Flag pra Gerenciar o Menu
    enum Select flag = ENTR;

    int horasTrabalhadas = 0, minutosTrabalhadas = 0, segundosTrabalhados = 0, segundosTrabalhadosTotais =0,  Backup_seg = 0;
    struct tm *tempo;
    time_t tempoInicial, tempoFinal;
    int row,col row_entr = 0;
    
    // Inicializando Ncurses e imprimindo o menu
    initscr();
    raw();		
    noecho();		
	keypad(stdscr, TRUE);	
    // Determina tempo de resposta para 1 seg, importante para sincronia do tempo!
    halfdelay(10);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    getmaxyx(stdscr,row,col);
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(row/2-6,(col-strlen("Menu"))/2,"Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(3));
    mvprintw(row/2-4,(col-strlen("Entrada"))/2,"Entrada");
    attrset(COLOR_PAIR(2));
    mvprintw(row/2-2,(col-strlen("Saída"))/2,"Saída");

    int caracter_inp;
    while(true){         
        switch(caracter_inp){
            // Move o Menu
            case KEY_DOWN:
                            attrset(COLOR_PAIR(3));
                            mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                            attrset(COLOR_PAIR(2));
                            mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                            flag = SAID;
                            break;
            case KEY_UP: 
                            attrset(COLOR_PAIR(3));
                            mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                            attrset(COLOR_PAIR(2));
                            mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                            flag = ENTR;
                            break;
            default:
                            break;
        }
        // Atualiza o Relógio no canto direito inferior
        mvprintw(row-1,0,"%s",asctime(get_time()));

        // Adiciona uma Entrada e começa a contar o tempo  
        if (caracter_inp == 10 && flag == ENTR&& is_on == OFF){
            tempo = get_time();
            mvprintw(row_entr,0,"%s %dh %dm %ds","Entrada:", tempo->tm_hour, tempo->tm_min, tempo->tm_sec);
            row_entr++;
            time(&tempoInicial);
            is_on = ON;
        }
        // Adiciona uma Saida e para de contar o tempo, salvando-o na var Bakcup_seg
        if (caracter_inp == 10 && flag == SAID && row_entr&& is_on == ON){
            tempo = get_time();
            mvprintw(row_entr,0,"%s %dh %dm %ds","Saida:", tempo->tm_hour, tempo->tm_min, tempo->tm_sec);
            row_entr++;
            is_on = OFF;
            Backup_seg += segundosTrabalhadosTotais;
        }

        // Conta o tempo
        if (is_on == ON){
            time(&tempoFinal);
            segundosTrabalhadosTotais =  tempoFinal - tempoInicial;
            horasTrabalhadas = (Backup_seg + segundosTrabalhadosTotais)/3600;
            minutosTrabalhadas = ((Backup_seg + segundosTrabalhadosTotais)%3600)/60;
            segundosTrabalhados = (Backup_seg + segundosTrabalhadosTotais)%60;
        }
        // Encerra se cumprir todas as horas diárias e toca uma música
        if((segundosTrabalhados+Backup_seg) >= SEGUNDOS_TRABALHO){
            endwin();
            system("play a.mp3");
            exit(0);
        }
        // Imprime a quantidade de tempo trabalhado
        mvprintw(0,col-28,"Tempo trabalhado: %2d :%2d :%2d", horasTrabalhadas,minutosTrabalhadas,segundosTrabalhados);
        caracter_inp = getch();
    }
    endwin();
    return 0;
}


// Retorna o tempo atual 
struct tm *get_time(){
    time_t raw_time;
    struct tm *actual_time;
    time(&raw_time);
    actual_time = localtime(&raw_time);
    return actual_time;
}
