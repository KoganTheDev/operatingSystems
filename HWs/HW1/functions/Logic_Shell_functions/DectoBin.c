#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define DIGITS_IN_INT 32

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("The function \"DectoBin\" needs 2 parameters.\n");
        exit(1);
    }

    int base10 = DIGITS_IN_INT;
    int numberAsBinary = 0;
    int noMoreLeadingZeros = 0;
    int dectoBinString[DIGITS_IN_INT] = {0};
    int i;
    int number = atoi(argv[1]);

    // Convert to an integer that represents number in its binary format
    for (i = DIGITS_IN_INT - 1; i >= 0; i--){
        if ((number % 2) == 1){
            numberAsBinary += 1 * pow(10, (double) base10);
            dectoBinString[i] = 1;
        }

        number /= 2;
        base10 -= 1;
    }


    for (i = DIGITS_IN_INT -1; i >= 0; i--){
        if (noMoreLeadingZeros){
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