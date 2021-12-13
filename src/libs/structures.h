#ifndef STRUCTURES
#define STRUCTURES 1
// Flags 
enum turn {ON, OFF};

// Flag to manage the menu ( shows the options that's selected )
enum Select {ENTRY,FINISH,SAVE};


// Structs 

// Screen size
typedef struct {
    int col;
    int row; 
}screen; 

// Time (hrs, min, secs)
typedef struct timeTotal {
    int hours;
    int minutes;
    int seconds;
}timeTotal; 

// Linked list used to construct the menu
typedef struct linkedStr{
    char *str;
    struct linkedStr *next;
    struct linkedStr *bef;
    enum Select flag;
    screen scr;
}linkedStr;
#endif