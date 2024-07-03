#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/**
 * Summary:
 * Solves the quadratic equation ax^2 + bx + c = 0 and returns the solutions.
 *
 * Details:
 * Converts the provided coefficients a, b, and c from string arguments to double,
 * computes the discriminant, and finds the roots of the equation based on the value of the discriminant.
 * If the discriminant is negative, prints "No Sol!" indicating no real solutions.
 * If the discriminant is zero, prints the single solution.
 * If the discriminant is positive, forks a new process to print both solutions.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 4.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the coefficients a, b, and c as strings.
 *                   argv[1] should be the coefficient a, argv[2] should be the coefficient b, and argv[3] should be the constant term c.
 *
 * Returns:
 * @return - (int): Returns 0 to indicate successful execution. Prints the solutions to the standard output.
 */
double main(int argc, char* argv[]) {
    int pid;
    double firstSolution, secondSolution;

    double a = atof(argv[1]);    // Coefficient of x^2
    double b = atof(argv[2]);    // Coefficient of x
    double c = atof(argv[3]);    // Constant term
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        printf("No Sol!\n");
        return 0;
    }
    else if (discriminant == 0) {
        firstSolution = (-b) / (2 * a);
        printf("%.0lf\n", firstSolution);
        return 0; // Represents a successful run
    }
    else {
        firstSolution = (-b + sqrt(discriminant)) / (2 * a);
        secondSolution = (-b - sqrt(discriminant)) / (2 * a);

        if ((pid = fork()) < 0) {
            printf("Creating a new process in \"Solve\" has failed.\n");
            exit(1);
        }

        if (pid != 0) {
            printf("%.0lf\n", firstSolution);
            return 0; // Represents a successful run
        }
        else {
            printf("%.0lf\n", secondSolution);
            return 0; // Represents a successful run
        }
    }
}
