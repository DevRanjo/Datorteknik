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
    char whole_binary[16] = {0};
    int index = 0; 

    if(whole_num == 0){
        whole_binary[index++] = '0';        
    }
    else{
        while(whole_num > 0){
            whole_binary[index++] = (whole_num % 2);  //add each (remainder as) binary number to the array
            whole_num = (int) whole_num / 2;           //use next even number
        }
        //after going to the end number -> reverse to get the right binary order
        int last_index = index - 1;  //last index

        for(int j=0; j < last_index/2; j++){            //go through half iterations to switch elements correctly in the array
            char temp = whole_binary[j];                
            whole_binary[j] = whole_binary[last_index - j]; //switch later elements with prior order in array
            whole_binary[last_index - j] = temp;            
        }
    }

    //convert fraction number part to binary

    char fraction_binary[16] = {0};
    int index = 0; 


    //combine both binary parts with snprintf

    //find exponent

    //extract mantissa
    //typ ta 1 minus på de fyra första byten ^^

    //combine everything sign + exponent + mantissa

}


int main(){
    representation* rep = malloc(8);


    return 1; 
}

