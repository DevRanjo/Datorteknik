#include <stdio.h>
#include <stdlib.h>


// funktion för att kolla om det sparas genom two's complement i minnet
int if_twos_complement(){

    int x = -1;

    // kolla hur x ser ut i minnet.
    unsigned char *p = (unsigned char*)&x; 

    for(int i = 0; i<sizeof(int); i++){
    // 02x = skriv ut ett tal i hex, alltid med två siffror, fyll med nollor om det behövs.
    printf("%02x ",p[i]);
    }

    // om det börjar med FF så är det two's complement.
    if (p[0] == 0xFF) {
        return 1;} 
    else {
        return 0;
    }

}



int main(){

// array med 8 bytes.
unsigned char *b_array = malloc(8);
// gör det till en integer pointer som ska ha ip addressen från uppgiften.
int *address = (int*) b_array;
*address = 0x04030201;

// printar ut arrayen och kollar sedan om det är little/big endian.
for(int i = 0; i<sizeof(int); i++){
    printf("%02x ",b_array[i]);
}

if(b_array[0] == 01){
    printf("\nIt's little endian (small to big)\n");
}
else{
    printf("\nIt's big endian (big to small)\n");
}

// kallar på funktionen som kollar om det är two's complement, är det return 1 så är det den
if(if_twos_complement() == 1){
    printf("\nNegative numbers are stored through two's complement");
}
// Annars sparas det genom sign magnitude.
else{
    printf("\nNegative numbers are stored through sign magnitude");

}




free(b_array);

}