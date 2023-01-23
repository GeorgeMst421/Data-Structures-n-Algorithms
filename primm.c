#include "primm.h"


void Main_Primm(Graph graph){
    int i,j;
    char Str_i[3];
    
    Node_list queue;
    queue.head = queue.tail = NULL;

    Edge_list Primm;
    Primm.head = Primm.tail = NULL;

    printf("Give me the starting vertex:\n");
    fgets(Str_i,sizeof(Str_i),stdin);
    fflush(stdin);
    i = SpellingCheck(Str_i);

    if(graph.pinV[i].head == NULL){
        printf("Vertex does not exist!\n");
        return;
    }

    init_queue(graph,&queue);

    Update_Key(&queue,i,0);

    while(queue.head != NULL){
        
        node_ptr vertex_u = dequeue(&queue);
        edge_ptr Edge_aux = graph.pinV[vertex_u->n].head;
        
        while(Edge_aux != NULL){
            
            int v = Edge_aux->j;
            node_ptr vertex_v = queue.head;
            
            while(vertex_v != NULL){
                if(vertex_v->n == v) break;
                vertex_v = vertex_v->next;
            }
            
            if(Node_List_Check(queue,Edge_aux,-1) && Edge_aux->weight < vertex_v->key){
                vertex_v->P = vertex_u->n;
                Update_Key(&queue,v,Edge_aux->weight);
            }

            Edge_aux = Edge_aux->next;
        }

        edge_ptr new_Edge = Create_Edge(vertex_u->n,vertex_u->P,vertex_u->key);
        Push_Edge_List_Insert(&Primm,new_Edge);
        
        free(vertex_u);
    }

    /*Remove the first edge of the list aka the root
      because its parent is the number INT_MIN*/

    edge_ptr temp = Primm.head;
    Primm.head = Primm.head->next;
    free(temp);

    print_Edges_list(Primm);
    print_List_total_weight(Primm);

    free_Edges_list(&Primm);

}

void init_queue(Graph graph,Node_list_ptr queue){
    for(int i=0; i<SIZE; i++){
        if(graph.pinV[i].head != NULL){
            node_ptr newNode = Create_node(i,INT_MIN);
            Queue_Insert(queue,newNode);
        }
    }
}

void Queue_Insert(Node_list_ptr queue,node_ptr node){
    if(queue->head == NULL){
        queue->head = queue->tail = node;
        return;
    }
    node->prev = queue->tail;
    queue->tail->next = node;
    queue->tail = node;
}

void Update_Key(Node_list_ptr queue,int node,int newkey){
    node_ptr aux = queue->head;
    while(aux != NULL){
        if(aux->n == node){
            aux->key = newkey;
            break;
        }
        aux = aux->next;
    }

    queue->head = Mergesort(queue->head);
}

node_ptr Mergesort(node_ptr head){

    if(!head || !head->next) return head;

    node_ptr second = split(head);

    head = Mergesort(head);
    second = Mergesort(second);

    return merge(head,second);
}

node_ptr merge(node_ptr first,node_ptr second){

    if(!first) return second;

    if(!second) return first;

    if(first->key < second->key){
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    } 
    else{
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

node_ptr split(node_ptr head){
    node_ptr fast = head,slow = head;
    while(fast->next && fast->next->next){
        fast = fast->next->next;
        slow = slow ->next;
    }

    node_ptr temp = slow->next;
    slow->next = NULL;
    return temp;
}


node_ptr dequeue(Node_list_ptr queue){
    node_ptr n;

    n = queue->head;
    queue->head = queue->head->next;
    n->next = NULL;

    return n ;
}


void Push_Edge_List_Insert(Edge_list_ptr list,edge_ptr edge){

    if(list->head == NULL){
        list->head = list->tail = edge;
        return;
    }
    edge->prev = list->tail;
    list->tail->next = edge;
    list->tail = edge;  
}