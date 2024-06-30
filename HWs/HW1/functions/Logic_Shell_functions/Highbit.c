#include <stdio.h>
#include <stdlib.h>

/**
 * Summary:
 * Counts the number of set bits (1s) in the binary representation of an integer.
 *
 * Arguments:
 * @param number - (int type): The number whose bits are to be counted.
 *
 * Returns:
 * @return - (int type): The count of set bits in the binary representation.
 *
 * Details:
 * The function iterates through each bit of the input number, checking if it's set (1).
 * It uses bitwise operations to shift and count set bits until the number is zero.
 */
int main(int argc, char* argv[]){

    if (argc != 2){
        printf("The function \"Highbit\" must get 2 parameters.\n");
        exit(1);
    }

    int number = atoi(argv[1]);

    int count = 0;

    while (number) {
        count += number & 1; // Check if the current lsb is 1 or 0. 
        number >>= 1; // Consume the lsb.
    }

    print("%d\n", count);
    return count;
}