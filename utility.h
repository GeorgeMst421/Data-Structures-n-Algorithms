#ifndef utility
#define utility

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define SIZE 30

typedef enum{
    white = 0,
    grey = 1,
    black = 2
}Color;

/*Edge Structure*/
typedef struct edge Edge;
typedef Edge* edge_ptr;

struct edge{
    int i,j;
    Color color; 
    int weight;
    edge_ptr next,prev,up,down;
};


/*Node Structure*/
typedef struct node Node;
typedef Node* node_ptr;

struct node{
    int n,P,key;
    struct node_list* Representative;
    node_ptr prev,next;
};

/*Linked List of  Nodes*/
typedef struct node_list Node_list ;
typedef Node_list* Node_list_ptr;

struct node_list{
    node_ptr head,tail;
};

/*Linked List of Edges*/
typedef struct list_edge Edge_list;
typedef Edge_list* Edge_list_ptr;
struct list_edge{
    edge_ptr head,tail;
};

/*Graph Structure*/
typedef struct graph Graph;
typedef Graph* graph_ptr;

struct graph{
    Edge_list pinV[SIZE];
    Edge_list pinH[SIZE];           
};


/*Utility Functions*/
void initGraph(graph_ptr graph);
void printGraph(Graph graph);
bool EmptyGraph(Graph graph);
bool EdgeExists(Graph graph,int a,int b);
int  SpellingCheck(char *c);

node_ptr Create_node(int n, int P);
Node_list_ptr Create_Node_list();
void print_Node_list(Node_list N_list);
void free_Node_list(Node_list_ptr N_list);


void Edge_List_Insert(Edge_list_ptr List,edge_ptr edge);
bool Edge_List_Search(Edge_list Edges,int i,int j);
void print_Edges_list(Edge_list Edges);
void free_Edges_list(Edge_list_ptr Edges);
void print_List_total_weight(Edge_list Edges);

#endif