#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Calculates the square root of a given number and prints it.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 2.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the number for which square root is to be calculated as a string.
 *                   argv[1] should be the number for which square root is to be calculated.
 *
 * Returns:
 * @return - (int): 0 if successful.
 * 
 * Details:
 * The function checks if the given number is negative. If it is, it prints "Math Error!" and exits.
 * Otherwise, it calculates and prints the square root of the given number.
 */
int main(int argc, char* argv[]) {
    double number = atof(argv[1]); // The number for which square root is to be calculated

    if (number < 0) {
        printf("Math Error!\n");
        exit(1);
    }

    printf("%.0lf\n", sqrt(number));
    return 0; // Represents a successful run
}
