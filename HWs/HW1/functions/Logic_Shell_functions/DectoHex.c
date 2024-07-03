/*
TODO:
-> Gets one parameter
-> returns the Hexadecimal value of the given decimal number.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Summary:
 * Converts a given decimal number to its hexadecimal representation and prints the result.
 *
 * Details:
 * This program takes a decimal number as input and converts it to its hexadecimal representation.
 * It prints the hexadecimal representation of the number.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 2.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the decimal number as a string.
 *                   argv[1] should be the decimal number to convert.
 *
 * Returns:
 * @return - (int): 0 to indicate a successful run.
 */
int main(int argc, char* argv[]){
    int number = atoi(argv[1]);

    printf("%X\n", number); // Prints in hexa format.

    return 0; // When the function succeeds.
}