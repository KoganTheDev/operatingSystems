#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define SIZE_OF_INPUT 256
#define MAX_ARGS 5

// Function declarations
void createNewDir();
void parseUserInput(char* userInput, char* arguments[], int* argumentsIndex);

/**
 * @brief Main function for the Standard Shell program.
 *
 * @details
 * - Ensures correct usage with one argument.
 * - Creates the necessary directory if not already present.
 * - Processes user commands, forks child processes to execute specific commands, and handles errors.
 * - Supports built-in commands like exit, Math, Logic, and String.
 * - Executes regular shell commands with varying numbers of arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Exit status of the program.
 */
int main(int argc, char* argv[]) {

    if (argc != 1) {
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[MAX_ARGS];
    int argumentsIndex;
    int pid;

    // Ensure the directory ./Commands exists
    createNewDir();

    // Main command processing loop
    while (1) {
        printf("StandardShell > ");

        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL) {
            printf("fgets in \"Standard_shell\" has failed to grab input.\n");
            exit(1);
        }

        // Remove the new line character
        userInput[strcspn(userInput, "\n")] = 0;

        // Parse user input into arguments array
        parseUserInput(userInput, arguments, &argumentsIndex);

        // Special case: the user didn't insert input therefore allow him to try inserting once again.
        if (argumentsIndex == 0) {
            printf("No input received.\n");
            continue;
        }

        // Fork a child process to execute the command.
        if ((pid = fork()) < 0) {
            printf("Forking has failed for the Standard_Shell.\n");
            exit(1);
        }

        // Look for the exact match function to run
        if ((strcmp(arguments[0], "exit")) == 0) {
            if (pid == 0) {
                execlp("./functions/Standard_Shell_functions/exit", "exit", NULL);
            } else { // Parent's clause
                break;
            }
        } else if ((strcmp(arguments[0], "Math")) == 0) {
            if (pid == 0) {
                execlp("./functions/Standard_Shell_functions/Math", "Math", NULL);
            }
        } else if ((strcmp(arguments[0], "Logic")) == 0) {
            if (pid == 0) {
                execlp("./functions/Standard_Shell_functions/Logic", "Logic", NULL);
            }
        } else if ((strcmp(arguments[0], "String")) == 0) {
            if (pid == 0) {
                execlp("./functions/Standard_Shell_functions/String", "String", NULL);
            }
        } else {
            // Try executing a regular shell function.
            if (pid == 0) {
                arguments[argumentsIndex] = NULL; // Null-terminate the arguments array
                execvp(arguments[0], arguments);
                printf("Not Supported\n"); // Print "Not Supported" if execvp fails
                exit(1);
            }
        }

        // Exit the child process if a function was executed
        if (pid == 0) {
            exit(0);
        }

        wait(NULL); // Waits for the child process to end
    }
    wait(NULL); // Wait for exit to end.
    return 0;
}

/**
 * @brief Creates a new directory ./Commands if it does not exist.
 *
 * @details
 * Uses opendir to check if the directory ./Commands exists. If not, creates it with read, write, and execute permissions for the owner only.
 * Prints appropriate messages for success or failure in creating the directory.
 *
 * @param None.
 * @return None.
 */
void createNewDir() {
    DIR* dir = opendir("./Commands");

    if (dir) {
        closedir(dir); // Closes the file descriptor
        printf("The directory ./Commands already exists.\n");
    } else if (errno == ENOENT) { // ENOENT in this case will say that there's no entry for this dir, therefore we'll create it.
        if (mkdir("./Commands", 0700) == -1) {
            printf("Making the new directory has failed.\n");
            exit(1);
        } else {
            printf("Commands dir created.\n");
        }
    }
}

/**
 * @brief Parses user input into command arguments.
 *
 * @details
 * Tokenizes the user input based on spaces and stores them in the arguments array. Null-terminates the array.
 *
 * @param userInput The input string entered by the user.
 * @param arguments Array to store parsed arguments.
 * @param argumentsIndex Pointer to the index of arguments array.
 * @return None.
 */
void parseUserInput(char* userInput, char *arguments[], int* argumentsIndex) {
    *argumentsIndex = 0;

    char* token = strtok(userInput, " ");

    while (token != NULL && *argumentsIndex < MAX_ARGS - 1) {
        arguments[*argumentsIndex] = token;
        (*argumentsIndex)++;
        token = strtok(NULL, " ");
    }

    arguments[*argumentsIndex] = NULL; // Null-terminate the arguments array
}
