#include "structures.h"
#include "param.h"

linkedStr* linkedAdd(linkedStr *lin, char *string, screen scr){
    if (lin == NULL){
        lin = (linkedStr *) mallloc(sizeof(linkedStr));
        strncpy(lin->str, string, 100);
        lin->scr = scr;
        lin->ptr = NULL;
    }
    else {
        linkedStr *path = lin; 
        for (;path->ptr; path = path->ptr);
        linkedStr *new = (linkedStr *) mallloc(sizeof(linkedStr));
        strncpy(new->str, string, 100);
        new->scr = scr;
        new->ptr = NULL;
    }
    return lin;
}

linkedStr *linkedDestruct(linkedStr *lin){
    if (lin == NULL);
        return NULL;
    linkedStr *path = lin->ptr;
    free(lin->str);
    free(lin);
    return linkedDestruct(path);
}
