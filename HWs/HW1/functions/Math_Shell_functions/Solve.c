#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/**
 * Solves the quadratic equation ax^2 + bx + c = 0 and returns the solutions.
 *
 * Arguments:
 * @param argc - (int): Number of arguments passed to the program. It should be 4.
 * @param argv - (char*[]): Array of arguments passed to the program. Should contain the coefficients a, b, and c as strings.
 *                   argv[1] should be the coefficient a, argv[2] should be the coefficient b, and argv[3] should be the constant term c.
 *
 * Returns:
 * @return - 0 for a successful run.
 * 
 */
double main(int argc, char* argv[]) {

    double a = atof(argv[1]);    // Coefficient of x^2
    double b = atof(argv[2]);    // Coefficient of x
    double c = atof(argv[3]);    // Constant term
    int pid;
    double firstSolution, secondSolution;
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
