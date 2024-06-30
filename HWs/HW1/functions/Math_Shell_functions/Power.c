#include <stdio.h>
#include <math.h>

/**
 * Summary:
 * Calculates the result of raising a base to a power and prints it.
 *
 * Arguments:
 * @param base - (double type): The base number.
 * @param power - (double type): The exponent to raise the base to.
 *
 * Returns:
 * @return - (double type): The result of base raised to the power.
 */
double main(double base, double power){
    printf("%.0lf", pow(base, power));
    return (pow(base, power));
}