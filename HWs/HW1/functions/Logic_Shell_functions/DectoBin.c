#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DIGITS_IN_INT 32

/**
 * Summary:
 * Converts a given decimal number to its binary representation and prints the result.
 *
 * Details:
 * This program takes a decimal number as input and converts it to its binary representation.
 * It prints the binary representation of the number, removing any leading zeros.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 2.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the decimal number as a string.
 *                   argv[1] should be the decimal number to convert.
 *
 * Returns:
 * @return - (int): The binary representation of the number in integer format.
 */
int main(int argc, char* argv[]){

    int base10 = DIGITS_IN_INT;
    int numberAsBinary = 0, noMoreLeadingZeros = 0;
    int dectoBinString[DIGITS_IN_INT] = {0};
    int number = atoi(argv[1]);
    int numberCopy = number;
    int i;

    // Convert to an integer that represents number in its binary format
    for (i = DIGITS_IN_INT - 1; i >= 0; i--){
        if ((number % 2) == 1){
            numberAsBinary += 1 * pow(10, (double) base10);
            dectoBinString[i] = 1;
        }

        number /= 2;
        base10 -= 1;
    }

    // Print the binary representation, removing leading zeros
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