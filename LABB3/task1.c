#include <stdio.h>
#include <stdlib.h>
#include "func_task1.h"

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
            printf("%d\t", (int)d[sizeof(int) * (i * 3 + j)]);
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
   
    z = column_two_d_fetch(p,0,1,sizeof(int), 2) + column_two_d_fetch(p,1,1,sizeof(int), 2);
    printf("z = %d", z);

    //TASK 2 MEMORY DUMP

    t=two_d_alloc(3,5,sizeof(int));

    two_d_store(t,0,0,sizeof(int),82, 5);
    two_d_store(t,0,1,sizeof(int),65, 5);
    two_d_store(t,0,2,sizeof(int),78, 5);
    two_d_store(t,0,3,sizeof(int),73, 5);
    two_d_store(t,0,4,sizeof(int),65, 5);

    two_d_store(t,1,0,sizeof(int),77, 5);
    two_d_store(t,1,1,sizeof(int),65, 5);
    two_d_store(t,1,2,sizeof(int),76, 5);
    two_d_store(t,1,3,sizeof(int),73, 5);
    two_d_store(t,1,4,sizeof(int),78, 5);

    two_d_store(t,2,0,sizeof(int),4, 5);
    two_d_store(t,2,1,sizeof(int),5, 5);
    two_d_store(t,2,2,sizeof(int),6, 5);
    two_d_store(t,2,3,sizeof(int),4, 5);
    two_d_store(t,2,4,sizeof(int),5, 5);
    
    printf("\nMemory dump:\n");
    mem_dump(t, sizeof(int)*3*5, sizeof(int));

    
    two_d_dealloc(p);
    two_d_dealloc(d);
    two_d_dealloc(t);
    return 1; 
}