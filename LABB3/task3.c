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
    append_to_list(L1, create_node(2, 'C'));
    append_to_list(L1, create_node(3, 'D'));
    append_to_list(L1, create_node(1, 'E'));
    append_to_list(L1, create_node(2, 'F'));
    append_to_list(L1, create_node(3, 'G'));
    append_to_list(L1, create_node(1, 'H'));
    append_to_list(L1, create_node(2, 'I'));
    append_to_list(L1, create_node(3, 'J'));

    print_list(L1);

    Node* tmp = L1;
    int list_int_size = 0;
    int list_char_size = 0;
    int list_struct_size = 0;
    int list_pointer_size = 0; 
    int only_fields_size = 0;

    if(tmp!= NULL){
        list_struct_size += sizeof(*tmp); //size of struct Node

        list_int_size += sizeof(tmp->val);
        list_char_size += sizeof(tmp->c);
        list_pointer_size += sizeof(tmp->next);
    }
    only_fields_size = list_int_size + list_char_size + list_pointer_size;
    printf("\nChecking one struct Node:\n");
    printf("Only size of struct Node: %d\n", list_struct_size);
    printf("Sum of all fields in struct node: %d\n", only_fields_size);

    //skip first to continue with rest of list 
    tmp = tmp->next;
    while(tmp!=NULL){
        //total size of all struct nodes in list
        list_struct_size += sizeof(*tmp);

        //total sizes of the seperate fields. 
        list_int_size += sizeof(tmp->val);
        list_char_size += sizeof(tmp->c);
        list_pointer_size += sizeof(tmp->next);

        tmp = tmp->next;
    }
    only_fields_size = list_int_size + list_char_size + list_pointer_size;

    printf("\nChecking 10 element list with size:\n");
    printf("Struct size list: %d\n", list_struct_size);
    printf("Only all fields in list size: %d", only_fields_size);

    free(tmp);
    free_list(L1);
    return 1; 
}