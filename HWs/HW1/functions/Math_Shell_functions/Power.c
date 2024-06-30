#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
double main(int argc, char* argv[]){

    if (argc != 3){
        printf("The function \"Power\" needs 3 parameters.\n");
        exit(1);
    }

    double base = atoi(argv[1]);
    double power = atoi(argv[2]);

    printf("%.0lf", pow(base, power));
    return (pow(base, power));
}