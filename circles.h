#ifndef circles
#define circles
#include "utility.h"

/*Circles Functions*/
bool CircleCheck(Graph graph,Node_list N_list);
void CirclePrint(Node_list N_list,int i,int j);
void N_to_root_List_Creation(Node_list N_list, Node_list_ptr N_to_root,int N);
bool White_Edge(Graph graph, int i,int j);

#endif