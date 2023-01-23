#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "utility.h"

void initGraph(graph_ptr graph){
	int i;
    for(i=0; i<SIZE; i++){
        graph->pinV[i].head = NULL;
        graph->pinH[i].head = NULL;
    }        
}


/*Prints the existing edges of the graph*/
void printGraph(Graph graph){
    int i;
    edge_ptr aux; 
    if(EmptyGraph(graph)) return;  
    for(i=0; i<SIZE; i++){
        aux=graph.pinV[i].head;
        if(aux!=NULL) printf("%d:  ",i);              
        while(aux!=NULL){
            printf("%d   ",aux->j);
            aux=aux->next;
            if(aux==NULL)  printf("\n");                
        }
    }
}

/*Returns True if the Graph is empty*/
bool EmptyGraph(Graph graph){
   	int i;
    for(i = 0; i<SIZE; i++){
        if(graph.pinV[i].head!= NULL) return false;        
    }
    printf("Graph is Empty\n");
    return true;
}

/*Returns True if the edge {i,j} exists on the Graph*/
bool EdgeExists(Graph graph,int i,int j){
    edge_ptr aux = graph.pinV[i].head;
    if(aux == NULL) return false;
    while(aux!=NULL){
        if(aux->j == j)  return true;                       
        else aux = aux->next;
    }
    return false;
}

/*Makes sure that the user inputs an integer*/
int SpellingCheck(char *c){
    int i = atoi(c);
    while(i == 0){
        printf("Wrong input data! Try again\n");
        fgets(c,sizeof(c),stdin);
        fflush(stdin);
        i=atoi(c);
    }
    return i;
}

/*Creates a new Node*/
node_ptr Create_node(int n, int P){
    node_ptr newNode = (node_ptr) malloc(sizeof(Node));
    newNode->prev = newNode->next = NULL;
    newNode->Representative = NULL;
    newNode->n = n;
    newNode->P = P;
    newNode->key = INT_MAX;
    return newNode;
}

Node_list_ptr Create_Node_list(){
    Node_list_ptr newSet = (Node_list_ptr) malloc(sizeof(Node_list));
    newSet->head = newSet->tail = NULL;
    return newSet;
}

void print_Node_list(Node_list N_list){
    if(N_list.head == NULL) return;
    node_ptr aux = N_list.head;
    while(aux != NULL){
        printf("{%d,%d}\n",aux->n,aux->P);
        aux = aux->next;
    }
}

/*Frees the memory that has been allocated for a Node list*/
void free_Node_list(Node_list_ptr N_list){     
    if(N_list->head == NULL) return;   
    node_ptr aux;
    while(N_list->head != NULL){
        aux = N_list->tail;
        if(N_list->tail != N_list->head){
            aux->prev->next = NULL;
            N_list->tail = aux->prev;
        }
        else{
            N_list->head = N_list->tail = NULL;
        }
        free(aux);
    }
}




/*Inserts a new edge on the Edges list*/
void Edge_List_Insert(Edge_list_ptr List,edge_ptr edge){
    if(List->head == NULL){
        List->head = List->tail = edge;
        return;
    } 
    edge_ptr aux = List->head;
    while(aux !=NULL){
        if(aux->weight > edge->weight) break;
        aux = aux->next;
    }
    if(aux == NULL){
        List->tail->next = edge;
        edge->prev = List->tail;
        List->tail = edge;
    }
    else if(aux == List->head){
        List->head->prev = edge;
        edge->next = List->head;
        List->head = edge;
    }
    else{
        edge->next = aux;
        edge->prev = aux->prev;
        aux->prev->next = edge;
        aux->prev = edge;
    }   
}


/*Returns true if the edge {i,j} exists in the list*/
bool Edge_List_Search(Edge_list Edges,int i,int j){
    edge_ptr aux = Edges.head;
    while(aux != NULL){
        if(aux->i == i && aux->j == j) return true;
        aux = aux->next;
    }
    return false;
}


/*Prints the Edges of the list*/
void print_Edges_list(Edge_list Edges){
    if(Edges.head == NULL){
        printf("Edge list is empty\n");
        return;
    }
    edge_ptr aux = Edges.head;
    while (aux != NULL){
        printf("{%d,%d}  weight: %d\n",aux->i,aux->j,aux->weight);
        aux = aux->next;
    }
}

/*Frees the allocated memory of a List of Edges*/
void free_Edges_list(Edge_list_ptr Edges){
    if(Edges->head == NULL) return;
    edge_ptr aux;
    while(Edges->head != NULL){
        aux = Edges->tail;
        if(Edges->tail != Edges->head){
            aux->prev->next = NULL;
            Edges->tail = aux->prev;
        }
        else{
            Edges->head = Edges->tail = NULL;
        }
        free(aux);
    }
}

/*Prints the List of Edges total weight*/
void print_List_total_weight(Edge_list Edges){
    int total = 0;
    edge_ptr aux = Edges.head;
    while(aux != NULL){
        total += aux->weight;
        aux = aux->next;
    }
    printf("Total weight: %d\n",total);
}
