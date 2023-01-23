#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "edgeInsert.h"


/*Main Insert Function*/
void Main_Insert(graph_ptr graph){
    int i,j,weight;
    char Str_i[3],Str_j[3],Str_w[3];
   
    printf("\n[INSERT]\n");
    printf("Give me the i,j of the edge \n"); 

    fgets(Str_i,sizeof(Str_i),stdin);
    fflush(stdin);
    i = SpellingCheck(Str_i);
   
    fgets(Str_j,sizeof(Str_j),stdin);
    fflush(stdin);
    j = SpellingCheck(Str_j);    

    if(EdgeExists(*graph,i,j)){
        printf("Edge already exists\n");
        return;
    }
    
    printf("What weight has the edge?\n");      
    
    fgets(Str_w,sizeof(Str_w),stdin);
    fflush(stdin);        
    weight = SpellingCheck(Str_w);
    
    edge_ptr New_Edge = Create_Edge(i,j,weight);
    InsertV(graph,New_Edge);
    InsertH(graph,New_Edge); 

    /*The graph is undirected so if i!=j we call again the 
    Insert function with swapped i,j so that the antidiametric 
    edge gets inserted*/
    if(i!=j){
        New_Edge = Create_Edge(j,i,weight);
        InsertV(graph,New_Edge);
        InsertH(graph,New_Edge);
        printf("Installation of {%d,%d} & {%d,%d} Completed\n",i,j,j,i);
    }
    else printf("Installation of {%d,%d} Completed\n",i,j);
    
}

/*Inserts the edge on the Row*/
void InsertV(graph_ptr graph,edge_ptr New_edge){
    int i = New_edge->i;
    int j = New_edge->j;
    
    // //Case of empty list
    if(graph->pinV[i].head == NULL){        
        graph->pinV[i].head = graph->pinV[i].tail = New_edge;
        return;
    }
    
    edge_ptr aux = graph->pinV[i].head;

    while(aux != NULL && aux->j < j){
        aux = aux->next;
    }
    New_edge->next = aux;
    if(aux == NULL){
        New_edge->prev = graph->pinV[i].tail;
        graph->pinV[i].tail->next = New_edge;
        graph->pinV[i].tail = New_edge;
    }
    else if(aux == graph->pinV[i].head){
        aux->prev = New_edge;
        graph->pinV[i].head = New_edge;
    }
    else{
        New_edge->prev = aux->prev;
        aux->prev->next = New_edge;
        aux->prev = New_edge;
    }
}

/*Inserts the edge on the column*/
void InsertH(graph_ptr graph,edge_ptr New_Edge){
    int i = New_Edge->i;
    int j = New_Edge->j;
    
    //Case of empty list
    if(graph->pinH[j].head== NULL){
        graph->pinH[j].head = graph->pinH[j].tail = New_Edge;
        return;
    }
    
    edge_ptr aux = graph->pinH[j].head;

    while(aux != NULL && aux->i < i){
        aux = aux->down;
    }
    
    New_Edge->down = aux;
    
    /*Case of insertion at the end of the list*/
    if(aux == NULL){
        New_Edge->up = graph->pinH[j].tail;
        graph->pinH[j].tail->down = New_Edge;
        graph->pinH[j].tail = New_Edge;
    }
    /*Case of insertion at the beggining of the list*/
    else if(aux == graph->pinH[j].head){
        aux->up = New_Edge;
        graph->pinH[j].head = New_Edge;
    }
    /*Case of insertion between two edges*/
    else{
        New_Edge->up = aux->up;
        aux->up->down = New_Edge;
        aux->up = New_Edge;
    }

}