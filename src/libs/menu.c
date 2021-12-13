#include "param.h"
#include "structures.h"

// Reads the menu options, that must be in a text file whose the path will be passed as a parameter, and each option of the menu will be in a different line.
linkedStr *menuCreateList(char *file_name, int option, screen scr){
    int count =  -4;                    // Screen control
    screen factor;  
    linkedStr *link =  NULL;
    char str[100];
    FILE *arq = fopen(file_name, "r");
    if (arq == NULL){
        printf("Error file %s didn't open correctly", file_name);
    }
    while (fgets(str, 100, arq)){
       str[strlen(str)-1] = '\0';              

       factor.col = (scr.col-strlen(str))/2;       // Screen control
       factor.row = (scr.row/2+count);

        link = linkedAdd(link, str, factor, option);        

        count += 2;         // Screen control
    }
    fclose(arq);
    return link;
}
