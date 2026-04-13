#include <stdio.h>
#include <stdlib.h>

int main(){

unsigned char *b_array = malloc(8);
int *ip_address = (int*) b_array;
*ip_address = 0x04030201;

for(int i = 0; i<4; i++){

    // 02x = skriv ut ett tal i hex, alltid med två siffror, fyll med nollor om det behövs
    printf("%02x ",b_array[i]);

}
free(b_array);

}