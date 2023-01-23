#ifndef bfs.h
#define bfs.h
#include "utility.h"

/*Breadth First Search Functions*/
void InitColors(graph_ptr graph);
void Main_BFS(graph_ptr graph);
void BFS_Alg(graph_ptr graph,Node_list_ptr N_list,int i);
void Graph_Row_run(graph_ptr graph,Node_list_ptr N_list,int i,int P);
bool Node_List_Check(Node_list N_list,edge_ptr Edge_aux,int P);
void BFS_print(Graph graph,Node_list N_list);

#endif