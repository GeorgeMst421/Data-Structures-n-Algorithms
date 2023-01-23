#include "kruskal.h"

/*Initialize the Array of sets for Kruskal's Alg*/
void init_sets(Node_list_ptr* Array_of_sets,Graph graph){
    for(int i = 0; i<SIZE; i++){
        if(graph.pinV[i].head != NULL)
            Array_of_sets[i] = Make_set(i);  
        else
            Array_of_sets[i] = NULL;
    }
}

/*Creates a Vertex N for Kruskal's Alg and makes it a set with itself*/
Node_list_ptr Make_set(int N){
    Node_list_ptr newSet = Create_Node_list();
    node_ptr newNode = Create_node(N,N);
    newSet->head = newSet->tail = newNode;
    newNode->Representative = newSet;
    return newSet;
}

/*Returns the Representative of the Node*/
int Find_Set(Node node){
    return node.Representative->head->n;
}

/*Main Function for Kruskal's Algorithm*/
void Main_Kruskal(Graph graph){
   
    /*Create and initilize an Array of sets.A Set is implemented as a node list*/
    Node_list_ptr Array_of_sets[SIZE];  
    init_sets(Array_of_sets,graph);
    
    /*Create and initialize the list that will contain the edges of the Kruskal's Alg*/
    Edge_list Kruskal;
    Kruskal.head = Kruskal.tail = NULL;
    
    /*Create and initialize the list that will contain the sorted by weight edges of the Graph*/
    Edge_list Edges;
    Edges.head = Edges.tail = NULL;

    /*Sorting the edges into non decreasing order by weight into the List Edges*/
    for(int i=0; i<SIZE; i++){
        if(graph.pinV[i].head != NULL){
            edge_ptr aux = graph.pinV[i].head;
            while(aux != NULL){
                if(!Edge_List_Search(Edges,aux->j,i)){//Searching for the antidiametrical
                    edge_ptr newEdge = Create_Edge(i,aux->j,aux->weight);
                    Edge_List_Insert(&Edges,newEdge);
                }
                aux = aux->next;
            }
        }
    }
    
    /*For Each edge {i,j} taken into non decreasing order by weight,
    if FindSet(i) != FindSet(j) we add the edge at the Main-List Kruskal, change
    the representatives of the second set and finaly we union the 2 sets*/

    edge_ptr aux = Edges.head;
    while(aux != NULL){
        int i = aux->i, j = aux->j;

        if(Find_Set(*(Array_of_sets[i]->head)) != Find_Set(*(Array_of_sets[j]->head))){
            
            /*Adding the edge on the Main-List*/
            edge_ptr newEdge = Create_Edge(i,j,aux->weight);
            Edge_List_Insert(&Kruskal,newEdge);
            
            /* Change the representative of the second set*/
            Node_list_ptr new_representative = Array_of_sets[i]->head->Representative;;
            
            int Old_representative = Array_of_sets[j]->head->Representative->head->n;
            node_ptr node_aux = Array_of_sets[Old_representative]->head;
            
            while(node_aux != NULL){
                node_aux->Representative = new_representative;
                node_aux = node_aux->next;
            }
           
            /* Union the 2 sets*/
            Array_of_sets[i]->tail->next = Array_of_sets[j]->head;
            Array_of_sets[i]->tail = Array_of_sets[j]->tail;
        }
        aux = aux->next;
    }
    
    if(Kruskal.head == NULL){
        printf("No results\n");
        return;
    }

    /*The Edges that belongs to Kruskal's Algorithm and the
    total weight are printed with the functions bellow */
    print_Edges_list(Kruskal);
    print_List_total_weight(Kruskal);
    
    /*Finally we free the allocated memory*/
    free_Edges_list(&Edges);
    free_Edges_list(&Kruskal);
}


