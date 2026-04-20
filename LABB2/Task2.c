#include <stdio.h>

void int_out(int input){
    char buff[12] = {0};

    int load = snprintf(buff, sizeof(buff), "%x", input);
    if(load >= buff){
        printf("Overload of buffer");
        return; 
    }
    return; 
}

int main(){
    int test = 1010;
    int_out(test);  
    return 1; 
}