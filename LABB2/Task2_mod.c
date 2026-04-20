#include <stdio.h>

char int_out(int input){
    char buff[12] = {0};

    int load = snprintf(buff, sizeof(buff), "%x", input);
    if(load >= buff){
        printf("Overload of buffer");
        return buff; 
    }
    return buff; 
}

//______

char assembly_call();

int main(){
    int result = assembly_call();
    printf("\nResult: \n", result);
    return 1; 
}