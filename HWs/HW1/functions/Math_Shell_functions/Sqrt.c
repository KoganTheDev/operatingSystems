#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Summary:
 * Calculates the square root of a given number and prints it.
 *
 * Arguments:
 * @param number - (double type): The number for which to calculate the square root.
 *
 * Returns:
 * @return - (double type): The square root of the given number.
 */
double main(int argc, char* argv[]){

    if (argc != 2){
        printf("The function \"Sqrt\" needs 2 parameters.\n");
        exit(1);
    }

    double number = atoi(argv[1]);

    if (number < 0){
        printf("Math Error!\n");
        exit(1);
    }

    printf("%.0lf", sqrt(number));
    return (sqrt(number));
}