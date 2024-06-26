#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Declare variables
    char* mainString = argv[1];  // Store the input string
    char* slicedElement;          // Store the elements after splitting
    int i;                        // Loop variable

    // Check if there are no arguments (excluding the program name)
    if (argc == 1) {
        // Print error message and exit if no arguments are provided
        printf("The function needs more arguments to start running.");
        exit(1);
    }

    // Convert all lowercase letters to uppercase in the input string
    for (i = 0; i < strlen(mainString); i++) {
        if (mainString[i] >= 'a' && mainString[i] <= 'z') {
            mainString[i] -= 32;  // ASCII conversion to uppercase
        }
    }

    // Tokenize the modified string based on underscore delimiter
    slicedElement = strtok(mainString, "_");
    while (slicedElement != NULL) {
        // Print each tokenized element
        printf("%s\n", slicedElement);
        // Move to the next token
        slicedElement = strtok(NULL, "_");
    }
    
    return 0;
}
