#ifndef STRUCTURES
#define STRUCTURES 1
// Flags 
enum turn {ON, OFF};

// Flag pra Gerenciar o Menu ( indica a opção selecionada )
enum Select {ENTRY,FINISH,SAVE};


// Structs 

// Tamanho tela
typedef struct {
    int col;
    int row; 
}screen; 

// Tempo (hrs, min, secs)
typedef struct timeTotal {
    int hours;
    int minutes;
    int seconds;
}timeTotal; 

// Lista linkadas de Strings
typedef struct linkedStr{
    char *str;
    struct linkedStr *next;
    struct linkedStr *bef;
    enum Select flag;
    screen scr;
}linkedStr;
#endif