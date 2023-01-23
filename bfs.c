#include <bfs.h>

/*Initializes the color of the edges to White(0) for BFS Alg*/
void InitColors(graph_ptr graph){
    edge_ptr aux;
    int i;
    for(i=0; i<SIZE; i++){
        if(graph->pinV[i].head!=NULL){
            aux = graph->pinV[i].head;
            while(aux!=NULL){
                aux->color = white;
                aux = aux->next;
            }
        }
    }
}


/*Main Function for BFS Algorithm*/
void Main_BFS(graph_ptr graph){
    int i,j;
    char option = 'a',CircleOption,Str_i[2],Str_j[2];
    
    /*Creates the Node List*/
    Node_list N_list;
    N_list.head = N_list.tail = NULL;
    
    if(EmptyGraph(*graph)) return;
   
    /*Initializing the colors of the edges to white(0)*/
    InitColors(graph);
    
    printf("Input the starting vertex\n");   
    fgets(Str_i,sizeof(Str_i),stdin);
    fflush(stdin);
    i = SpellingCheck(Str_i);

    if(graph->pinV[i].head == NULL){
        printf("Vertex does not exist\n");
        return;
    }
   
    /*Function for The BFS algorithm is called*/
    BFS_Alg(graph,&N_list,i);
   
    /*BFS MENU*/
    while(option != 'r'){
        fflush(stdin);
        printf("Your options are: (p)Print, (c)Circle Check, (r)Return to Main\n");
        option = getchar();
        getchar();
        option = tolower(option);
        if(option == 'r'){
            free_Node_list(&N_list);
            break;
        }
        if(option == 'p')
            BFS_print(*graph,N_list);
        
        if(option == 'c'){
            
            CircleOption = 'a';
            
            if(!CircleCheck(*graph,N_list)){
                printf("No Circles found\n");              
            }
            else{
                while(CircleOption != 'n'){
                    
                    printf("Do you want to print a circle?(Y/N)\n");
                    CircleOption = getchar();
                    getchar();
                    CircleOption = tolower(CircleOption);
                    if(CircleOption == 'y'){
                       
                        printf("Give me the {i,j} to print the circle\n");
                        
                        fgets(Str_i,sizeof(Str_i),stdin);
                        fflush(stdin);
                        i = SpellingCheck(Str_i);

                        fgets(Str_j,sizeof(Str_j),stdin);
                        fflush(stdin);
                        j = SpellingCheck(Str_j);                           
                        
                        if(!EdgeExists(*graph,i,j)) printf("Edge does not Exist\n");
                        else if(!White_Edge(*graph,i,j)) printf("No Circles from this Edge\n");                             
                        else CirclePrint(N_list,i,j);
                    }
                }
            } 
        }
    }
}
    
/*BFS Algorithm*/
void BFS_Alg(graph_ptr graph,Node_list_ptr N_list,int i){
    edge_ptr Edge_aux;
    node_ptr Node_aux;
    
    node_ptr FirstNode = Create_node(i,0);
    N_list->head = N_list->tail = FirstNode;
    
    /*The first Graph_Row_run runs at the graph's row of the BFS root.
    All the nodes will be inputed in the list so we do not want to check
    for the parents, that's why we put -1 in the function*/
    Graph_Row_run(graph,N_list,i,-1);

    Node_aux = N_list->head->next;
    while(Node_aux!=NULL){
        Graph_Row_run(graph,N_list,Node_aux->n,Node_aux->P);       
        Node_aux = Node_aux->next;
    }
    printf("Breadth First Search Completed!\n");
}

/*  Graph_Row_run combined with Node_list_Check "runs" at the desirable 
    row on the graph and puts the edges on a list. Before we insert the
    edge on the BFS list we check if it already exists on the list */
void Graph_Row_run(graph_ptr graph,Node_list_ptr N_list,int i,int P){
    edge_ptr Edge_aux = graph->pinV[i].head;
    while(Edge_aux != NULL){
        if(!Node_List_Check(*N_list,Edge_aux,P)){
            Edge_aux->color = grey;
            node_ptr newNode = Create_node(Edge_aux->j,i);
            N_list->tail->next = newNode;
            newNode->prev = N_list->tail;
            N_list->tail = newNode;
        }
        Edge_aux = Edge_aux->next;
    }
}

/*  Node_List_Check returns true if the edge is already on the list.
    With the int P(Parent) we check if the edge is an antidiametric to color it 
    grey without putting it in the list */
bool Node_List_Check(Node_list N_list,edge_ptr Edge_aux,int P){
    node_ptr aux = N_list.head;
    while(aux!=NULL){
        if(aux->n == Edge_aux->j){
            if(aux->n == P) Edge_aux->color = grey;
            return true;
        }
        aux = aux->next;
    }
    return false;
}

/*Print the edges that belongs to Breadth First Search*/
void BFS_print(Graph graph,Node_list N_list){
    edge_ptr Edge_aux;
    node_ptr Node_aux = N_list.head;
    while(Node_aux!=NULL){
        Edge_aux = graph.pinV[Node_aux->n].head;
        while(Edge_aux!=NULL){
            if(Edge_aux->color == grey)
                printf("{%d,%d}\n",Node_aux->n,Edge_aux->j);
            Edge_aux = Edge_aux->next;
        }
        Node_aux = Node_aux->next;
    }
}


