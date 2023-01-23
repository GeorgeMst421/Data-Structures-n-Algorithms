#include "circles.h"


/*Returns true if there are circles in the graph*/
bool CircleCheck(Graph graph,Node_list N_list){
    edge_ptr Edge_aux;
    node_ptr Node_aux = N_list.head;
    bool Circles = false;
    while(Node_aux!=NULL){
        Edge_aux = graph.pinV[Node_aux->n].head;
        while(Edge_aux!=NULL){
            if(Edge_aux->color == white){
                printf("Circle found from %d to %d\n",Edge_aux->i,Edge_aux->j);
                Circles = true;
            }
            Edge_aux = Edge_aux->next;
        }
        Node_aux = Node_aux->next;
    }
    return Circles;
}

/*  Creating two lists from the verteces of the edge {i,j} back to the root.
    Each list contains the node structs with the number of the node N and it's parent P.
    Then, starting from the tails of the two lists, deleting the same edges and lastly
    adding the edge {i,j} results in revealing the actual circle */
void CirclePrint(Node_list N_list,int i,int j){  
   
    /*Initializing the node lists*/
    Node_list i_to_root;
    i_to_root.head = i_to_root.tail = NULL;
    
    Node_list j_to_root;
    j_to_root.head = j_to_root.tail = NULL;
    
    /*Creating the two lists from the two verteces back to the root*/
    N_to_root_List_Creation(N_list,&i_to_root,i);
    N_to_root_List_Creation(N_list,&j_to_root,j);
    
    /*Deleting the same edges*/
    while(i_to_root.tail->n == j_to_root.tail->n && i_to_root.tail->P == j_to_root.tail->P){
              
        node_ptr tail_i = i_to_root.tail;
        node_ptr tail_j = j_to_root.tail;
       
        if (i_to_root.tail->prev != NULL) i_to_root.tail->prev->next = NULL;       
        i_to_root.tail = i_to_root.tail->prev;
                     
        if (j_to_root.tail->prev != NULL) j_to_root.tail->prev->next = NULL;      
        j_to_root.tail = j_to_root.tail->prev;
        
        free(tail_i);
        free(tail_j);     
    }
 
    printf("{%d,%d}\n",i,j);
    print_Node_list(i_to_root);
    print_Node_list(j_to_root);
    
    free_Node_list(&i_to_root);
    free_Node_list(&j_to_root);
}

/*Creates a list with the route of the element N back to the BFS Root*/
void N_to_root_List_Creation(Node_list N_list, Node_list_ptr N_to_root,int N){
    int temp_P;
    node_ptr Node_aux = N_list.head;
    node_ptr newNode;
    
    while(Node_aux != NULL){
        if(Node_aux->n == N)
            break;       
        Node_aux = Node_aux->next;
    }
    temp_P = Node_aux->P;

    N_to_root->head = N_to_root->tail = Create_node(Node_aux->n,Node_aux->P);

    while(Node_aux != NULL){
        if(Node_aux->n == temp_P){
            temp_P = Node_aux->P;
            newNode = Create_node(Node_aux->n,Node_aux->P);
            newNode->prev = N_to_root->tail;
            N_to_root->tail->next = newNode;
            N_to_root->tail = newNode;
        }
        Node_aux = Node_aux->prev;
    }
}

/*Returns true if the edge's color is white*/
bool White_Edge(Graph graph, int i,int j){
    edge_ptr aux = graph.pinV[i].head;
    while(aux!=NULL){    
        if(aux->j == j) break;
        aux = aux->next;
    }
    if(aux->color == white) return true;
    else return false;
}


