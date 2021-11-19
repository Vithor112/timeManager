#include "structures.h"
#include "param.h"

// Cria lista encadeada
linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr){
    if (lin == NULL){                                       // Criando Lista
        lin = (linkedStr *) malloc(sizeof(linkedStr));
        lin->str = (char *) malloc(strlen(string));
        strcpy(lin->str, string);
        lin->scr = scr;
        lin->ptr = NULL;
    }

    else {                                              // Adicionando na Lista
        linkedStr *path = lin;  
        for (;path->ptr; path = path->ptr);             // Andando pela lista até o fim

        linkedStr *new = (linkedStr *) malloc(sizeof(linkedStr)); // Alocando memória para novo nodo
        new->str = (char *) malloc(strlen(string));
        strcpy(new->str, string);
        new->scr = scr;
        new->ptr = NULL;

        path->ptr = new;                            // linkando
    }

    return lin;
}

// Desaloca memória
linkedStr *linkedDestruct(linkedStr *lin){
    if (lin == NULL);
        return NULL;
    linkedStr *path = lin->ptr;
    free(lin->str);
    free(lin);
    return linkedDestruct(path);
}
