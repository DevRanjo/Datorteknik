#include <stdio.h>
#include <stdlib.h>

typedef struct Data{
    unsigned char data_buffer;  // [sign][exponent][mantissa]
} representation;


void convertFloat(representation* rep, float flt){

    // är det noll sluta direkt
    if(flt == 0.0){
        rep->data_buffer = 0;
        return;
    }


    // kolla vad det är för sign
    int sign = 0; 
    if(flt < 0){
        sign = 1; 
        flt = -flt;
    }

    // dela upp taleti heltal och decimaltal
    int whole_num = (int) flt;
    float frac = flt - whole_num;


    // gör om heltalsdel till binary
    char whole_binary[16] = {0};
    int index = 0; 

    if(whole_num == 0){
        whole_binary[index++] = 0;
    }
    else{
        while(whole_num > 0){
            whole_binary[index++] = (whole_num % 2);
            whole_num = whole_num / 2;
        }

        // vänd arrayen så det inte blir baklänges
        for(int j = 0; j < index / 2; j++){
            char temp = whole_binary[j];
            whole_binary[j] = whole_binary[index - j - 1];
            whole_binary[index_whole - j - 1] = temp;
        }
    }
    int index_whole = index;
    //convert fraction number part to binary (reached the decimal point)
    char fraction_binary[16] = {0};
    index = 0;

    while(frac > 0 && index < 16){
        frac = frac * 2;

    while(frac != 0){   //run until there is no fract left
        frac = frac * 2;        //fraction uses *2 to convert to binary (gets put in array in right order)
        
        int temp = frac;        //stores the integer (whole) part either 0 or 1
        if(temp == 1){
            fraction_binary[index++] = '1';
            frac = frac - 1;    //remove whole number to keep working with fractions
        }
        else{
            fraction_binary[index++] = '0'; 
        }
    }

    //combine both binary parts with snprintf
    char binary[32];
    snprintf(binary, sizeof(binary), "%s.%s", whole_binary, fraction_binary);


    // mantissan
    char mantissa[4];
    int m = 0;

    // ta från heltalsdelen (hoppa över första siffran)
    for(int i = 1; i < index_whole && m < 4; i++){
        mantissa[m++] = whole_binary[i];
    }

    // fyll på från decimaldelen (fraction)
    for(int i = 0; m < 4; i++){
        mantissa[m++] = fraction_binary[i];
    }

    // fyll med 0 om det behövs
    while(m < 4){
        mantissa[m++] = 0;
    }


    // Lägg in allt i data_buffer som vi gjorde i vår struct
    rep->data_buffer = 0;

    // lägg in sign (bit 7) (1 bit)
    rep->data_buffer |= (sign << 7); // (<<) flytta sign 7 bitar åt vänster
    // |= betyder att man lägger in sign i data_buffer utan att ta bort d et som redan finns i data_buffer

    // lägg in exponent (bit 6–4) (3 bits)
    rep->data_buffer |= (biased_exp << 4);

    // lägg in mantissa (bit 3–0) (4 bits)
    for(int i = 0; i < 4; i++){
        rep->data_buffer |= (mantissa[i] << (3 - i));
    }
}

void finalPrints(representation rep){ // printar från bit 7 och nedåt för att få dom i rätt ordning
    for(int i = 7; i >= 0; i--){
        printf("%d", (rep.data_buffer >> i) & 1);
    }
    printf("\n");
}

int main(){

    representation rep;   // vi skapar först en struct

    // Test med ojämnt tal
    convertFloat(&rep, 5.73);
    printf("5.73 -> ");
    finalPrints(rep);

    // Test med mindre jämnt tal
    convertFloat(&rep, 3.5);
    printf("3.5 -> ");
    finalPrints(rep);

    // Test med större tal
    convertFloat(&rep, 10.25);
    printf("10.25 -> ");
    finalPrints(rep);

    // Edge case, noll
    convertFloat(&rep, 0.0);
    printf("0.0 -> ");
    finalPrints(rep);

    return 0;
}