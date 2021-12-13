#include "structures.h"
#include "param.h"

// Creates doubly circular linked list
linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr){
    if (lin == NULL){                                       // Creates list
        lin = (linkedStr *) malloc(sizeof(linkedStr));
        lin->str = (char *) malloc(strlen(string));
        strcpy(lin->str, string);
        lin->scr = scr;
        lin->next = lin;
        lin->bef = lin; 
        lin->flag = 0;
    }

    else {                                              // Adds in list
        linkedStr *path = lin;  
        int i = 1;
        for (;path->next != lin; path = path->next){i++;}
        linkedStr *new = (linkedStr *) malloc(sizeof(linkedStr)); 
        new->flag = i;
        new->str = (char *) malloc(strlen(string));
        strcpy(new->str, string);
        new->scr = scr;
        new->next = lin;
        lin->bef = new;
        new->bef = path; 
        path->next = new;                          
    }

    return lin;
}

// Deallocate memory
linkedStr *linkedDestruct(linkedStr *lin){
    linkedStr *path = lin, *aux;
    do{
        aux = path->next;
        free(path->str);
        free(path);
        path = aux;
    }while(path != lin);
    return NULL;
}