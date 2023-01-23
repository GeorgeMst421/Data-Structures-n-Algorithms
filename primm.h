#ifndef primm
#define primm

#include "utility.h"
#include "edgeFunctions.h"
#include "bfs.h"

/*Primm's Algorithm*/
void Main_Primm(Graph graph);
void init_queue(Graph graph,Node_list_ptr queue);
void Queue_Insert(Node_list_ptr queue,node_ptr node);
void Update_Key(Node_list_ptr queue,int node,int newkey);
node_ptr merge(node_ptr first,node_ptr second);
node_ptr split(node_ptr head);
node_ptr Mergesort(node_ptr head);
node_ptr dequeue(Node_list_ptr queue);
void Push_Edge_List_Insert(Edge_list_ptr list,edge_ptr edge);

#endif