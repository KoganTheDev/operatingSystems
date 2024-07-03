#include <stdio.h>
#include <stdlib.h>

/**
 * Summary:
 * Counts the number of set bits (1s) in the binary representation of an integer.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 2.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the integer number as a string.
 *                   argv[1] should be the number whose bits are to be counted.
 *
 * Returns:
 * @return - (int): The count of set bits in the binary representation.
 *
 * Details:
 * The function iterates through each bit of the input number, checking if it's set (1).
 * It uses bitwise operations to shift and count set bits until the number is zero.
 */
int main(int argc, char* argv[]){
    int number = atoi(argv[1]);
    int count = 0;

    // Iterate through each bit of the number
    while (number) {
        count += number & 1; // Check if the current lsb is 1 or 0. 
        number >>= 1; // Consume the lsb.
    }
    printf("%d\n", count);

    return count;
}