#include "param.h"
#include "structures.h"

// Lê as opções do menu, que devem estar em um arquivo de texto chamado menu na pasta options, e cada opção do menu deve estar em uma linha diferente.
linkedStr *menuCreateList(){
    int count =  -4;                    // Para ajustar coordenadas da tela
    screen scr, factor;  
    initializeScreen(&scr);
    getmaxyx(stdscr,scr.row,scr.col);

    linkedStr *link =  NULL;
    char str[100];
    char file_name[] = "./options/menu.txt";
    FILE *arq = fopen(file_name, "r");
    if (arq == NULL){
        printf("Error file %s didn't open correctly", file_name);
    }
    while (fgets(str, 100, arq)){
       str[strlen(str)-1] = '\0';              // Retirando Break line

       factor.col = (scr.col-strlen(str))/2;       // tela
       factor.row = (scr.row/2+count);

        link = linkedAdd(link, str, factor);        // Criando lista e adicionando nodos

        count += 2;         // tela 
    }
    fclose(arq);
    return link;
}
