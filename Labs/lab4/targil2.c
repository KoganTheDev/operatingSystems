#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 256

int main(int argc, char* argv[]) {
    char input[MAX_INPUT_LENGTH];

    // Check if there are any arguments passed to the program
    if (argc != 1) {
        printf("ERROR: Invalid arguments\n");
        exit(1);
    }

    while (1) {
        printf("$ "); // Print prompt
        fflush(stdout); // Flush stdout to ensure prompt is displayed

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("ERROR: Failed to read input\n");
            break; // Exit loop on input failure
        }

        input[strcspn(input, "\n")] = '\0'; // Remove newline character from input

        // Check for the termination command "q"
        if (strcmp(input, "q") == 0) {
            printf("END\n");
            break; // Exit loop on "q" command
        }

        // Trim leading and trailing spaces and extract the command
        char *command = strtok(input, " ");
        if (command == NULL) {
            continue; // If no command found, prompt again
        }

        // Execute the command
        pid_t pid = fork(); // Fork a new process
        if (pid == -1) {
            printf("ERROR: Fork failed\n");
            exit(1); // Exit if fork fails
        } else if (pid == 0) {
            // Child process
            if (execlp(command, command, NULL) == -1) { // Execute the command
                printf("ERROR: Execution failed\n"); // If execution fails, print error message
            }
            exit(1); // Exit the child process
        } else {
            // Parent process
            wait(NULL); // Wait for child process to complete
        }
    }

    return 0;
}
