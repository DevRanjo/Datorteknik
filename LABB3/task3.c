#include <stdio.h>
#include <stdlib.h>
#include "func_task1.h"
#include <string.h>

typedef struct Node{
    char c;
    struct Node* next; 
    int val;
}Node;

Node* create_node(int value, char chr){
    Node* new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        printf("Allocation failed\n");
        return NULL; 
    }
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

//new row major store function to be able not focus only on integer but for entire Node memory blocks
void new_two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, Node* values_at_node, int total_columns){
    ptr = ptr + byte_size * (row_indx * total_columns + col_indx);
    
    //copy full emory block of node into the array for the task
    memcpy(ptr, values_at_node, byte_size);
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
    printf("Only size of struct Node: %d bytes\n", list_struct_size);
    printf("Sum of all fields in struct node: %d bytes\n", only_fields_size);

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
    printf("Struct size list: %d bytes\n", list_struct_size);
    printf("Only all fields in list size: %d bytes\n", only_fields_size);

    //Task 4.2 Storing the list
    tmp = L1; 
    char* arr = two_d_alloc(1, 10, sizeof(Node));

    for(int i=0; i<10 && tmp != NULL; i++){
        new_two_d_store(arr, 0, i, sizeof(Node), tmp, 10);
        tmp = tmp->next;
    }
    
    
    printf("\nElements stored in arr from list:\n");
    for(int i=0; i<10; i++){    //point to i node in arr

        printf("Element %d: \t value: %d\n", i+1, ((Node*)(arr + i * sizeof(Node)))->val); //value at i node in array
    }
    printf("\n");

    mem_dump(arr, sizeof(Node)*10, sizeof(Node));

    printf("Fifth element:\n");
    printf("Location (index) of fifth node in array: %d\n", 4);
    Node* fifth_address = (Node*)(arr + 4 + sizeof(Node));
    printf("Address in memory of fifth node: %p\n", &fifth_address);
    printf("Address for fifth int: %p\n", &fifth_address->val);
    printf("Address for fifth char: %p\n", &fifth_address->c);

    
    free(arr);
    free(tmp);
    free(fifth_address);
    free_list(L1);
    return 1; 
}