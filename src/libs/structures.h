#ifndef STRUCTURES
#define STRUCTURES 1
// Flags 
enum turn {ON, OFF};

// Flag to manage the Main menu ( shows the options that's selected )
enum MainSelect {ENTRY,FINISH,SAVE};

// Flag to manage the Initial menu ( shows the options that's selected )
enum InitialSelect {MAX, NAMEFILE, LOAD_LOG, NEXT};

union flags {
    enum MainSelect main;
    enum InitialSelect initial;
};


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
    union flags flag;
    screen scr;
}linkedStr;
#endif