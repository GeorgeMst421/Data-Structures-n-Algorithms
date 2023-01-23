#ifndef edgeFunctions.h
#define edgeFunctions.h

#include "utility.h"

edge_ptr Create_Edge(int i,int j,int weight);

/*Edge Instertion Functions*/
void Main_Insert(graph_ptr graph);
void InsertV(graph_ptr graph,edge_ptr New_Edge);
void InsertH(graph_ptr graph,edge_ptr New_Edge);

/*Edge Deletion Functions*/
void Main_Delete(graph_ptr graph);
void DeleteV(graph_ptr graph,edge_ptr aux);
void DeleteH(graph_ptr graph,edge_ptr aux);


#endif