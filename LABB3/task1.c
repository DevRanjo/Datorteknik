#include <stdio.h>
#include <stdlib.h>


/* two_d_alloc: This function should return a pointer to a char. This function allocate
memory in order to store the matrix N ∗ M. The size of each element is given by a
parameter to the function (see example above).*/

char* two_d_alloc(int N, int M, int byte_size){
    
    char* ptr = malloc(N * M * byte_size); 
    
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
    return;
}

/*two d store: This function store a value into the corresponding row and column of the
array.*/

void two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, int value, int total_columns){
        //we added total columns to make it easier to calculate since we interpret the exercise 
        //to have one pointer and not double pointer 2d array
        ptr = ptr + byte_size * (row_indx * total_columns + col_indx);
        //go to correct index = row * total_columns + col
        *(int*) ptr = value; 

    return; 
}

/*two d fetch: This return the value stored at the corresponding column and row of the
array*/
int two_d_fetch(char* ptr, int row_indx, int col_indx, int byte_size, int total_columns){
    ptr = ptr + byte_size * (row_indx * total_columns + col_indx);

    int stored_value = *(int*)ptr; 
    return stored_value; 
}

//COLUMN MAJOR TASK 2.2
void column_two_d_store(char* ptr, int row_indx, int col_indx, int byte_size, int value, int total_rows){
    
        ptr = ptr + byte_size * (col_indx * total_rows + row_indx);
        *(int*) ptr = value; 

    return; 
}

int column_two_d_fetch(char* ptr, int row_indx, int col_indx, int byte_size, int total_rows){
    ptr = ptr + byte_size * (col_indx * total_rows + col_indx);

    int stored_value = *(int*)ptr; 
    return stored_value; 
}

/*Implement a memory dump program which can read through a character array and prints
out each word in hexadecimal notation. Separate words in groups of four words per line,
where each word is represented by 8 hexadecimal numbers. 

Print the memory address of the
first byte on every line. Test your memory dump on the character array you implemented
in Task 1. Add four more columns to your output and interpret every byte as an ASCII
character. If the byte does not contain a valid character, print a dot instead.*/

void mem_dump(char* arr, int byte_size){
    

    for(int i=0; i<16; i++){
    printf("\nmemory address line %d: %p\n", i+1, arr);
        for(int j=0; j<4; j++){
            printf("%x", *arr);
        } 
    arr = arr + 4*byte_size; 
    printf("\t");
    }

    

    //snprintf(, sizeof(char), "%s.%s", total_string, added);


    /*for(int j=0; j<; j++){
        arr = arr + byte_size *
        printf("%x", *arr);
}*/
    //arr = arr + byte_size * (col_indx * total_rows + col_indx);
}


int main(){
    char* d, *p, *t; 
    int y, z;
    d=two_d_alloc(2,3,sizeof(int));


    two_d_store(d,0,0,sizeof(int),1, 3);
    two_d_store(d,0,1,sizeof(int),2, 3);
    two_d_store(d,0,2,sizeof(int),3, 3);
    two_d_store(d,1,0,sizeof(int),4, 3);
    two_d_store(d,1,1,sizeof(int),5, 3);
    two_d_store(d,1,2,sizeof(int),6, 3);
   
    for(int i=0; i<2; i++){
        for(int j=0; j < 3; j++){
            printf("%d\t", d[sizeof(int) * (i * 3 + j)]);
        }
        printf("\n");
    }
    
    y=two_d_fetch(d,0,1,sizeof(int), 3) + two_d_fetch(d,1,1,sizeof(int), 3);
    printf("y = %d\n", y);



    //TASK 2.2
    p=two_d_alloc(2,3,sizeof(int));

    column_two_d_store(p,0,0,sizeof(int),3, 2);
    column_two_d_store(p,0,1,sizeof(int),5, 2);
    column_two_d_store(p,0,2,sizeof(int),34, 2);
    column_two_d_store(p,1,0,sizeof(int),61, 2);
    column_two_d_store(p,1,1,sizeof(int),5, 2);
    column_two_d_store(p,1,2,sizeof(int),6, 2);

    printf("\nTask 2.2:\n");
    for(int i=0; i<2; i++){
        for(int j=0; j < 3; j++){
            printf("%d\t", p[sizeof(int) * (j * 2 + i)]);
        }
        printf("\n");
    }
   
    z = column_two_d_fetch(p,0,1,sizeof(int), 3) + column_two_d_fetch(p,1,1,sizeof(int), 3);
    printf("z = %d", z);

    //TASK 2 MEMORY DUMP

    printf("\nMemory dump:\n");
    mem_dump(d, sizeof(int));

    
    two_d_dealloc(p);
    two_d_dealloc(d);
    return 1; 
}