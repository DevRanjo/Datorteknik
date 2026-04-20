#include <stdio.h>

char int_out(int input){
    char buff[12] = "";

    int load = snprintf(buff, sizeof(buff), "%x", input);
    if(load >= buff){
        printf("Overload of buffer");
        return buff; 
    }
    return buff; 
}

//______im the main func>

char assembly_call();

int main(){
    char result = assembly_call();
    printf("\nResult: \n", result);
    return 1; 
}