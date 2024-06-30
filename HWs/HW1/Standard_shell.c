//TODO: insert code specifically main with documentation
// Will support any Linux command on regular shell that can handle up to 3
// parameters.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SIZE_OF_INPUT 256

void main(int argc, char* argv[]){

    if (argc != 1){
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[4];
    char* token;
    int argumentsIndex = 0;
    int commandsForMath;
    int pid;

    if(mkdir("./Commands",0700) == -1){
        printf("Making the new directory has failed.\n");
        exit(1);
    }
    

    while (1){
        printf("StandardShell>");
        
        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL){
            printf("fgets in \"Math_shell\" has failed to grab input.\n");
            exit(1);
        }

        // Split the input into token and put each one of them in the array of arguments.
        token = (userInput, " ");
        arguments[argumentsIndex] = token;
        argumentsIndex++;

        while (token != NULL){
            token = strtok(NULL, " ");
            arguments[argumentsIndex] = token;
            argumentsIndex++;
        }

        if ((pid = fork()) < 0){
                printf("Forking has failed for the Math_Shell.\n");
                exit(1);
        }

        // Look for the exact match function to run
        if ((strcmp(arguments[0], "exit")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/exit", NULL);
            }
        }
        else if ((strcmp(arguments[0], "Math")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/Math", NULL); 
            } 
        }
        else if ((strcmp(arguments[0], "Logic")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/Logic", NULL); 
            }
        }
        else if ((strcmp(arguments[0], "String")) == 0){
            if (pid == 0){
                execlp("./functions/String_Shell_functions/String", NULL); 
            }
        }
        else{
            // Try executing a regular shell function.
            if (pid == 0){
                if (argumentsIndex == 1){
                    execlp(arguments[0], NULL); 
                }
                else if (argumentsIndex == 2){
                    execlp(arguments[0], arguments[1], NULL); 
                }
                else if (argumentsIndex == 3){
                    execlp(arguments[0], arguments[1], arguments[2], NULL); 
                }
                else{
                    execlp(arguments[0], arguments[1], arguments[2], arguments[3], NULL);
                }
                execlp(arguments[0], arguments[1], arguments[2], NULL); 
                printf("Not Supported\n");
            }
        }

        wait(NULL); // Waits for the child process to end
        
        // Reset the index so it will not cause an out-of-bounds error.
        argumentsIndex = 0;
    }
}