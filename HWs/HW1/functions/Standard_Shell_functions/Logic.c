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

void createNewDir();
void parseUserInput(char* userInput, char* arguments[], int* argumentsIndex);

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[MAX_ARGS];
    int argumentsIndex;
    int pid, commandsForLogic;
    DIR* dir = opendir("./Commands/Logic");

    createNewDir();

    if ((commandsForLogic = open("./Commands/Logic/Logic_Commands.txt", O_RDWR | O_CREAT, 0644)) < 0) {
        printf("Opening the file for the commands of \"Logic_shell\" has failed.\n");
        exit(1);
    }

    if (!dir){
        printf("Logic_Commands.txt created in Commands/Logic.\n");
    }

    while (1) {
        printf("LogicShell > ");
        
        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL) {
            printf("fgets in \"Standard_shell\" has failed to grab input.\n");
            exit(1);
        }

        // Allocate memory for userInputForWriting
        char* userInputForWriting = (char*) malloc(sizeof(char) * (strlen(userInput) + 1));
        if (userInputForWriting == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        // Copy the user input to userInputForWriting
        strcpy(userInputForWriting, userInput);

        // Remove the new line character
        userInput[strcspn(userInput, "\n")] = 0;

        parseUserInput(userInput, arguments, &argumentsIndex);

        // Special case: the user didn`t insert input therefore allow him to try inserting once again.
        if (argumentsIndex == 0) {
            printf("No input received.\n");
            free(userInputForWriting);
            continue;
        }

        if (strcmp(arguments[0], "Cls") == 0) {
            free(userInputForWriting);
            break;
        }

        if ((pid = fork()) < 0) {
            printf("Forking has failed for the Standard_Shell.\n");
            free(userInputForWriting);
            exit(1);
        }

        // Look for the exact match function to run
        if (strcmp(arguments[0], "DectoBin") == 0) {
            if (argumentsIndex != 2 && pid != 0) {
                printf("The DectoBin command requires exactly 1 arguments.\n");
            }
            if (pid == 0 && argumentsIndex == 2) {
                execlp("./functions/Logic_Shell_functions/DectoBin", "DectoBin", arguments[1], NULL); 
            } 
        } else if (strcmp(arguments[0], "Highbit") == 0) {
            if (argumentsIndex != 2 && pid != 0) {
                printf("The Highbit command requires exactly 1 arguments.\n");
            }
            if (pid == 0 && argumentsIndex == 2) {
                execlp("./functions/Logic_Shell_functions/Highbit", "Highbit", arguments[1], NULL); 
            }
        } else if (strcmp(arguments[0], "DectoHex") == 0) {
            if (argumentsIndex != 2 && pid != 0) {
                printf("The DectoHex command requires exactly 1 argument.\n");
            }
            if (pid == 0 && argumentsIndex == 2) {
                execlp("./functions/Logic_Shell_functions/DectoHex", "DectoHex", arguments[1], NULL); 
            }
        } else if (strcmp(arguments[0], "History") == 0) {
            if (argumentsIndex != 1 && pid != 0) {
                printf("The History command requires no arguments.\n");
            }
            if (pid == 0 && argumentsIndex == 1) {
                execlp("./functions/Logic_Shell_functions/History", "History", NULL);
            }
        } else if (pid == 0){
            printf("Not Supported\n");
        }

        if (pid != 0){
            // Append a newline character to the command
            if (write(commandsForLogic, userInputForWriting, strlen(userInputForWriting)) == -1) {
                printf("Writing information to \"Logic_Commands\" has failed.\n");
                free(userInputForWriting);
                exit(1);
            }
            free(userInputForWriting);
        }

        // When no function ran using the child process.
        if (pid == 0){
            exit(0);
        }

        wait(NULL); // Waits for the child process to end
    }

    close(commandsForLogic);
    return 0;
}

void createNewDir() {
    DIR* dir = opendir("./Commands/Logic");

    if (dir) {
        closedir(dir); // Closes the file descriptor
        printf("The directory ./Commands/Logic already exists.\n");
    } else if (errno == ENOENT) { // ENOENT in this case will say that there`s no entry for this dir, therefore we`ll create it.
        if (mkdir("./Commands/Logic", 0700) == -1) {
            printf("Making the new directory has failed.\n");
            exit(1);
        } else {
            printf("Logic dir created in Commands dir.\n");
        }
    }
}

void parseUserInput(char* userInput, char* arguments[], int* argumentsIndex) {
    *argumentsIndex = 0;

    char* token = strtok(userInput, " ");

    while (token != NULL && *argumentsIndex < MAX_ARGS) {
        arguments[*argumentsIndex] = token;
        (*argumentsIndex)++;
        token = strtok(NULL, " ");
    }

    arguments[*argumentsIndex] = NULL; // Null-terminate the arguments array
}
