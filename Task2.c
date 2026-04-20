#include <stdio.h>

void int_out(int input){

    printf("%x", input);
    return; 
}

int main(){
    int test = 1010;
    int_out(test);
    
    return 1; 
}