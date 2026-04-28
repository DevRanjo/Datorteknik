#include <stdio.h>
#include <stdlib.h>


/* two_d_alloc: This function should return a pointer to a char. This function allocate
memory in order to store the matrix N ∗ M. The size of each element is given by a
parameter to the function (see example above).*/

char* two_d_alloc(int N, int M, int byte_size){
    
    char* ptr = calloc(N * M * byte_size, 0); 
    //allocate memory and initialize the elements to 0 by using calloc instead
    if(ptr==NULL){
        printf("Allocation failed\n");
        return NULL;
    }
    return ptr;
}

/*two_d_dealloc: This function deallocate the memory once the programmer doesn’t need
anymore the array.*/

void two_d_dealloc(char* ptr){
    free(ptr);
}
/*two d store: This function store a value into the corresponding row and column of the
array.*/

void two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, int value, int total_columns){
        //we added total columns to make it easier to calculate since we interpret the exercise 
        //to have one pointer and not double pointer 2d array
        char* ptr = ptr + (row_indx * total_columns + col_indx);
        //go to correct index = row * total_columns + col

        //typecast the value to the right unknown data type
        if(byte_size == sizeof(char)){
            *ptr = value;     //inserting the value at the memory address
        }
        if(byte_size == sizeof(int)){
            *(int*) ptr = value; 
        }
        if(byte_size == sizeof(float)){
            *(float*) ptr = value;
        }
        if(byte_size == sizeof(double)){
            *(double*) ptr = value; 
        }

    return; 
}

/*two d fetch: This return the value stored at the corresponding column and row of the
array*/
void* two_d_fetch(char* ptr, int row_indx, int col_indx, int byte_size, int total_columns){
    char stored_value;
    char* ptr = ptr + (row_indx * total_columns + col_indx);

    if(byte_size == sizeof(char)){
            stored_value = *ptr;
        }
    if(byte_size == sizeof(int)){
            stored_value = *(int*)ptr; 
        }
    if(byte_size == sizeof(float)){
            stored_value = *(float*)ptr;
        }
    if(byte_size == sizeof(double)){
        stored_value = *(double*)ptr; 
        }

    return stored_value; 
}

int main(){
    char* d;
    int y;
    d=two_d_alloc(20,50,sizeof(int));
    
    two_d_store(d,12,42,sizeof(int),4, 50);
    two_d_store(d,10,15,sizeof(int),3, 50);
    
    //y=two_d_fetch(d,12,42,sizeof(int), 50) + two_d_fetch(d,10,15,sizeof(int), 50);
    //....
    /*two_d_dealloc(d);*/
    
    return 1; 
}