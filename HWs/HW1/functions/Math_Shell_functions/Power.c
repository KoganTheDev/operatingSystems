#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Summary:
 * Calculates the power of a base number raised to a given exponent and prints the result.
 *
 * Details:
 * Converts the provided base and exponent from string arguments to double, 
 * computes the power using the math library's pow function, 
 * and prints the result rounded to zero decimal places.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 3.
 * @param argv - (char*[]): Array of arguments passed to the program. 
 *                   Should contain the base and power as strings.
 *                   argv[1] should be the base number, and argv[2] should be the exponent.
 *
 * Returns:
 * @return - (int): Returns 0 to indicate successful execution.
 *                  Prints the result of base raised to the power.
 */
double main(int argc, char* argv[]) {
    double base = atof(argv[1]);    // Convert the first argument to double (base)
    double power = atof(argv[2]);   // Convert the second argument to double (power)
    double result = pow(base, power);   // Calculate base^power

    printf("%.0lf\n", result);  // Print the result rounded to 0 decimal places
    return 0; // Represents a successful run.
}
