#include <stdio.h>
#include <stdlib.h>


int is_twos_complement() {
    int x = -1;
    unsigned char* bytes = &x;

    // In two’s complement, -1 is all bits set (0xFF in every byte)
    for (size_t i = 0; i < sizeof(int); i++) {
        if (bytes[i] != 0xFF) {
            return 0; // Not two’s complement
        }
    }
    return 1; // Two’s complement
}


int main(){

unsigned char* b_array = malloc(8);
int* address = (int*) b_array;
*address = 0x04030201;

for(int i = 0; i<4; i++){

    // 02x = skriv ut ett tal i hex, alltid med två siffror, fyll med nollor om det behövs
    printf("%2x ", b_array[i]);

}
free(b_array);
free(address);
}