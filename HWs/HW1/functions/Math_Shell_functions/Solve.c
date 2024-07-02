#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/**
 * Summary:
 * Solves the quadratic equation ax^2 + bx + c = 0 and returns the solutions.
 *
 * Arguments:
 * @param a - (double type): Coefficient of x^2.
 * @param b - (double type): Coefficient of x.
 * @param c - (double type): Constant term.
 *
 * Returns:
 * @return - (double type): One of the solutions to the equation, or NAN if no real solutions exist.
 * 
 * Details:
 * The function calculates the discriminant (b^2 - 4ac) to determine the nature of the roots.
 * - If the discriminant is negative, it prints "No Sol!" and returns NAN.
 * - If the discriminant is zero, it returns the single root.
 * - If the discriminant is positive, it forks the process to calculate both roots, returning one from each process.
 */
double main(int argc, char* argv[]){

    if (argc != 4){
        printf("The function \"Solve\" needs 4 parameters.\n");
        exit(1);
    }
    double a = atoi(argv[1]);
    double b = atoi(argv[2]);
    double c = atoi(argv[3]);
    int pid;
    double firstSolution, secondSolution;
    double numInSqaureRoot = b * b - 4 * a * c;


    if (numInSqaureRoot < 0){
        printf("No Sol!\n");
        return NAN; // Returns NAN for no real solutions.
    }
    else if (numInSqaureRoot == 0){
        printf("%0.lf\n", (-b) / (2 * a));
        return ((-b) / (2 * a)); // Special case when there`s only one solution.
    }
    else{
        firstSolution = ((-b) + sqrt(numInSqaureRoot)) / (2 * a);
        secondSolution = ((-b) - sqrt(numInSqaureRoot)) / (2 * a);

        if ((pid = fork()) < 0){
            printf("Creating a new process if \"Solve\" has failed.\n");
            exit(1);
        }
        
        if (pid != 0){
            printf("%.0lf\n", firstSolution);
            return firstSolution;
        }
        else{
            printf("%0.lf\n", secondSolution);
            return secondSolution;
        }
    }
}