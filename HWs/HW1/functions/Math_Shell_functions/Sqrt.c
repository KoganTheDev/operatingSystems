#include <stdio.h>
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
double main(double number){
    printf("%.0lf", sqrt(number));
    return (sqrt(number));
}