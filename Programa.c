#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SEGUNDOS_TRABALHO 100
#define MUSICA_ARQUIVO "a.mp3"
#define TELA row,col


void inicializandoNcurses();
void print_menu(int row, int col);
struct tm *get_time();
enum turn {ON, OFF};
enum Select {ENTR,SAID};
void Control_menu(int row, int col, int caracter_inp, enum Select *flag);

int main(void){
    // Flag pra Gerenciar o Rastreio do tempo 
    enum turn is_on = OFF;
    // Flag pra Gerenciar o Menu
    enum Select flag = ENTR;

    int horasTrabalhadas = 0, minutosTrabalhadas = 0, segundosTrabalhados = 0, segundosTrabalhadosTotais =0,  Backup_seg = 0;
    struct tm *tempo;
    time_t tempoInicial, tempoFinal;
    int row,col, row_entr = 0;
    
    // Inicializando Ncurses e imprimindo o menu

    inicializandoNcurses();
    getmaxyx(stdscr,row,col);
    print_menu(TELA);

    int caracter_inp;
    while(true){    
             
        Control_menu(TELA, caracter_inp, &flag);

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
        if((segundosTrabalhadosTotais+Backup_seg) >= SEGUNDOS_TRABALHO){
            endwin();
            system("play "MUSICA_ARQUIVO);
            exit(0);
        }
        // Imprime a quantidade de tempo trabalhado
        mvprintw(0,col-28,"Tempo trabalhado: %2d :%2d :%2d", horasTrabalhadas,minutosTrabalhadas,segundosTrabalhados);
        caracter_inp = getch();
    }
    endwin();
    return 0;
}

// Move o Menu
void Control_menu(int row, int col, int caracter_inp, enum Select *flag){
    switch(caracter_inp){

        case KEY_DOWN:
                attrset(COLOR_PAIR(3));
                mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                attrset(COLOR_PAIR(2));
                mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                *flag = SAID;
                break;
        case KEY_UP: 
                attrset(COLOR_PAIR(3));
                mvprintw(row/2-4,(col-strlen("Entrada"))/2,"%s","Entrada");
                attrset(COLOR_PAIR(2));
                mvprintw(row/2-2,(col-strlen("Saída"))/2,"%s","Saída");
                *flag = ENTR;
                break;
            default:
                break;
        }
}

// Retorna o tempo atual 
struct tm *get_time(){
    time_t raw_time;
    struct tm *actual_time;
    time(&raw_time);
    actual_time = localtime(&raw_time);
    return actual_time;
}

void inicializandoNcurses(){
    initscr();
    raw();		
    noecho();		
	keypad(stdscr, TRUE);	
    // Determina tempo de resposta para 1 seg, importante para sincronia do tempo!
    halfdelay(10);
    start_color();
}

void print_menu(int row, int col){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(row/2-6,(col-strlen("-Menu"))/2,"-Menu");
    attroff(A_BOLD);
    attrset(COLOR_PAIR(3));
    mvprintw(row/2-4,(col-strlen("Entrada"))/2,"Entrada");
    attrset(COLOR_PAIR(2));
    mvprintw(row/2-2,(col-strlen("Saída"))/2,"Saída");
}