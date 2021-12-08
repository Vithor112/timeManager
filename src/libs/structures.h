#ifndef STRUCTURES
#define STRUCTURES 1
// Flags 
enum turn {ON, OFF};
enum Select {ENTR,SAID,CHECK};


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
    screen scr;
}linkedStr;
#endif