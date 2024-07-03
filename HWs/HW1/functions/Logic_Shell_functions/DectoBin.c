#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define DIGITS_IN_INT 32

int main(int argc, char* argv[]){

    int base10 = DIGITS_IN_INT;
    int numberAsBinary = 0;
    int noMoreLeadingZeros = 0;
    int dectoBinString[DIGITS_IN_INT] = {0};
    int i;
    int number = atoi(argv[1]);
    int numberCopy = number;

    // Convert to an integer that represents number in its binary format
    for (i = DIGITS_IN_INT - 1; i >= 0; i--){
        if ((number % 2) == 1){
            numberAsBinary += 1 * pow(10, (double) base10);
            dectoBinString[i] = 1;
        }

        number /= 2;
        base10 -= 1;
    }


    for (i = 0; i < DIGITS_IN_INT; i++){
        if (numberCopy == 0){
            printf("0");
            break;
        }
        else if (noMoreLeadingZeros){
            printf("%d", dectoBinString[i]);
        }
        else if (dectoBinString[i] == 1){
            printf("%d", dectoBinString[i]);
            noMoreLeadingZeros = 1; 
        }
    }
    printf("\n");

    return numberAsBinary;
}