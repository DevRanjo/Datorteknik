#include <stdio.h>


/* two_d_alloc: This function should return a pointer to a char. This function allocate
memory in order to store the matrix N ∗ M. The size of each element is given by a
parameter to the function (see example above).*/

char* two_d_alloc(int N, int M, int byte_size){

}

/*two_d_dealloc: This function deallocate the memory once the programmer doesn’t need
anymore the array.*/

void two_d_dealloc(){}

/*two d store: This function store a value into the corresponding row and column of the
array.*/

void two_d_store(){}

/*two d fetch: This return the value stored at the corresponding column and row of the
array*/
int two_d_fetch(){}

int main(){
    char* d;
    int y;
    d=two_d_alloc(20,50,sizeof(int));
    
    two_d_store(d,12,42,sizeof(int),4);
    two_d_store(d,10,15,sizeof(int),3);
    y=two_d_fetch(d,12,42,sizeof(int))+two_d_fetch(d,10,15,sizeof(int));
    //....
    two_d_dealloc(d);
    
    return 1; 
}