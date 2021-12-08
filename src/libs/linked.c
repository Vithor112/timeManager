#include "structures.h"
#include "param.h"

// Cria lista duplamente encadeada circular
linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr){
    if (lin == NULL){                                       // Criando Lista
        lin = (linkedStr *) malloc(sizeof(linkedStr));
        lin->str = (char *) malloc(strlen(string));
        strcpy(lin->str, string);
        lin->scr = scr;
        lin->next = lin;
        lin->bef = lin; 
        lin->flag = 0;
    }

    else {                                              // Adicionando na Lista
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

// Desaloca memória
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