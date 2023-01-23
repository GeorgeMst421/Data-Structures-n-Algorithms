#ifndef kruskal
#define kruskal
#include "utility.h"
#include "edgeFunctions.h"

/*Kruskal's Algorithm*/
Node_list_ptr Make_set(int N);
void Main_Kruskal(Graph graph);
void init_sets(Node_list_ptr* Array_of_sets,Graph graph);
int Find_Set(Node node);


#endif