#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Variable to store the desired result
    int result = atoi(argv[1]); 
    
    // Variables for loop iteration and storing numbers
    int i, j, firstNumber, secondNumber;

    // Check if there are at least four arguments
    if (argc < 4) { 
        // Print error message and exit if there are insufficient arguments
        printf("2 numbers do not exist.\n");
        exit(1);
    }

    // Nested loops to compare each pair of numbers
    for (i = 2; i < argc; i++) {
        for (j = i + 1; j < argc; j++) {
            // Convert arguments to integers
            firstNumber = atoi(argv[i]);
            secondNumber = atoi(argv[j]);
            
            // Check if sum of two numbers equals the desired result
            if (firstNumber + secondNumber == result) {
                // Print the pair of numbers that satisfies the condition
                printf("2 numbers exist: %d + %d = %d\n", firstNumber, secondNumber, result);
                return 0;
            }
        }
    }
    
    // Print message if no pair of numbers satisfies the condition
    printf("2 numbers do not exist.\n");
    return 0;
}
