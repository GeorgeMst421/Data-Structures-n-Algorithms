#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "edgeFunctions.h"

/*Creates a new edge*/
edge_ptr Create_Edge(int i,int j,int weight){
    edge_ptr NewEdge = (edge_ptr) malloc(sizeof(Edge));    
    NewEdge->i = i;
    NewEdge->j = j;
    NewEdge->weight = weight;
    NewEdge->next = NewEdge->prev = NewEdge->up = NewEdge->down = NULL;
    return NewEdge;
}


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



/*Main Delete Function*/
void Main_Delete(graph_ptr graph){
    int i,j;
    char Str_i[5],Str_j[5];
    edge_ptr aux;
    printf("\n[DELETE]\n");
   
    if(EmptyGraph(*graph)) return;

    printf("Give me the i,j of the edge you want to be deleted \n"); 
    
    fgets(Str_i,sizeof(Str_i),stdin);
    fflush(stdin);
    i = SpellingCheck(Str_i);
    
    fgets(Str_j,sizeof(Str_j),stdin);
    fflush(stdin);
    j = SpellingCheck(Str_j);
   
    if(!EdgeExists(*graph,i,j)){
        printf("Edge does not exist\n");
        return;
    }
    
    aux = graph->pinV[i].head;
    while(aux->j != j) aux = aux->next;
    
    DeleteV(graph,aux);
    DeleteH(graph,aux);
    free(aux);
    /*The graph is undirected so we must also delete the antidiametrical edge */
    if(i!=j){
        aux = graph->pinV[j].head;
        while(aux->j != i) aux = aux->next;
        DeleteV(graph,aux);
        DeleteH(graph,aux);
        free(aux);
        printf("Deletion of {%d,%d} & {%d,%d}  Completed\n",i,j,j,i);
    }
    else printf("Deletion of {%d,%d} Completed\n",i,j);
}

/*Deletes the edge on the row*/
void DeleteV(graph_ptr graph,edge_ptr aux){
    int i = aux->i;
    
    //Case when the edge is the only element on the row
    if(graph->pinV[i].head == aux && graph->pinV[i].tail == aux){
        graph->pinV[i].head = graph->pinV[i].tail = NULL;
    }
    //Case when the edge is the first element on the row
    else if(graph->pinV[i].head == aux && aux->next != NULL){
        aux->next->prev = NULL;
        graph->pinV[i].head = aux->next;
    }
    //Case when the edge is the last element on the row 
    else if (graph->pinV[i].tail == aux && aux->prev != NULL){
        aux->prev->next = NULL;
        graph->pinV[i].tail = aux->prev;
    }
    //Case when the edge is between two other edges
    else{
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }  
}

/*Deletes the edge on the column*/
void DeleteH(graph_ptr graph,edge_ptr aux){
    int j = aux->j;
   
    //Case when the edge is the only element on the column
    if(graph->pinH[j].head == aux && graph->pinH[j].tail == aux){
        graph->pinH[j].head = graph->pinH[j].tail = NULL;
    }
    //Case when the edge is the first element in the column
    else if(graph->pinH[j].head == aux && aux->down != NULL){
        aux->down->up = NULL;
        graph->pinH[j].head = aux->down;
    }
    //Case when the edge is the last element on the columbn 
    else if (graph->pinH[j].tail == aux && aux->up != NULL){
        aux->up->down = NULL;
        graph->pinH[j].tail = aux->up;
    }
    //Case when the edge is between two other edges
    else{
        aux->up->down = aux->down;
        aux->down->up = aux->up;
    }  
}

