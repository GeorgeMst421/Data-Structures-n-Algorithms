#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "utility.h"
#define SIZE 30



int main(){

    Graph Graph;
    initGraph(&Graph);
    char option = 'a';

    while(option != 'q'){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\nYour options are:\n(i)Insert, (d)Delete, (p)Print, (b)BFS, (k)Kruskal, (m)Primm, (q)Quit");
        printf("\nGive a new choice: ");
        scanf("%c",&option);
        fflush(stdin);
        option = tolower(option);
        if(option == 'q')
            printf("\n~~QUITING~~");        
        if(option == 'i')
            Main_Insert(&Graph);       
        if(option == 'p')
            printGraph(Graph);
        if(option == 'd' )
            Main_Delete(&Graph);
        if(option == 'b' )
            Main_BFS(&Graph);
        if(option == 'k')
            Main_Kruskal(Graph);
        if(option == 'm')
            Main_Primm(Graph);
    }

    return 0;
}


