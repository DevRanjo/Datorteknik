#include <stdio.h>

typedef struct Data{
    unsigned char data_buffer;      //[sign]=1[exponent]=3[mantissa]=4
    //void convertFloat() make it like a member function 
}representation;



void convertFloat(representation* rep, float flt){
    //check the sign 
    int sign = 0; 
    if(flt<0){
        sign = 1; 
        flt = -flt; //convert to pos if its neg
    }

    int whole_num = (int) flt;              //the whole number part of the float number
    float frac = flt - whole_num;           //the fraction part of the float number

    //convert whole number part to binary 

    //convert fraction number part to binary

    //combine both binary parts

    //find exponent

    //extract mantissa

    //convert mantissa string to binary 

    //combine everything sign + exponent + mantissa

    int* exponent = malloc(3);
    float* mantissa = malloc(4);

    *exponent = 0; 

    while(flt != 1){
        flt/2;
        ++exponent; 
        mantissa = flt; 
    }
    *mantissa = flt - 2^((float*)exponent);
}


int main(){
    representation* number_representation = malloc(8);


    return 1; 
}

