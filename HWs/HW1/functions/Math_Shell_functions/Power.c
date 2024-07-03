#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Calculates the power of a base number raised to a given exponent and prints the result.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 3.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the base and power as strings.
 *                   argv[1] should be the base number, and argv[2] should be the exponent.
 *
 * Returns:
 * @return - (double): The result of base raised to the power, printed to the standard output.
 *                    Returns 0 to indicate successful execution.
 */
double main(int argc, char* argv[]) {
    double base = atof(argv[1]);    // Convert the first argument to double (base)
    double power = atof(argv[2]);   // Convert the second argument to double (power)
    double result = pow(base, power);   // Calculate base^power

    printf("%.0lf\n", result);  // Print the result rounded to 0 decimal places
    return 0; // Represents a successful run.
}
