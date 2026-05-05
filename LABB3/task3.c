#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    char c;
    struct Node* next; 
}Node;

Node* create_node(int value, char chr){
    Node* new_node = malloc(sizeof(Node));
    new_node->val = value;
    new_node->c = chr; 
    new_node->next = NULL;
    return new_node;
}

Node* append_to_list(Node* head, Node* insert_node){
    Node* tmp = head; 
    if(head == NULL){    //if list is empty
        return insert_node; 
    }
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = insert_node;
    return head;
}

void print_list(Node* head){
    Node* tmp = head;
    int node_count = 0;  

    while(tmp!=NULL){
        printf("Node %d: int: %d char: %c\n", ++node_count, tmp->val, tmp->c);
        tmp = tmp->next;
    }
    free(tmp);
    return; 
}
void free_list(Node* L){
    Node* tmp = L;

    while(L!=NULL){
        tmp = L; 
        L = L->next;
        free(tmp);
    }
    return;
}

int main(){

    Node* L1 = create_node(0, 'A');
    append_to_list(L1, create_node(1, 'B'));
    append_to_list(L1, create_node(1, 'C'));
    
    print_list(L1);
    
    free_list(L1);
    return 1; 
}