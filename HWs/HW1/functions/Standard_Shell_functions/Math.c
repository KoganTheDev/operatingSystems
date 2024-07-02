/*
TODO: 
-> gets No Parameters.
-> Runs Math_Shell
-> Creates new directory called "Math" in "Commands"
-> Creates a new file called "Math_Commands" in the path Commands/Math

this func Saves the commands given from the user for Math_Shell

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SIZE_OF_INPUT 256
#define MAX_ARGS 4

void main(int argc, char* argv[]){

    if (argc != 1){
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[MAX_ARGS];
    char* token;
    int argumentsIndex = 0;
    int commandsForMath;
    int pid;

    if(mkdir("./Commands/Math",0700) == -1){
        printf("Making the new directory has failed.\n");
        exit(1);
    }
    
    if ((commandsForMath = open("./Commands/Math/Math_Commands", O_RDWR | O_CREAT, 0644 )) < 0){
        printf("Opening the file for the commands of \"Math_shell\" has failed.\n");
        exit(1);
    }

    while (1){
        printf("MathShell>");
        
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
        if ((strcmp(arguments[0], "Cls")) == 0){
            break;
        }
        else if ((strcmp(arguments[0], "Power")) == 0){
            if (pid == 0){
                execlp("./functions/Math_Shell_functions/Power", arguments[1], arguments[2], NULL); 
            } 
        }
        else if ((strcmp(arguments[0], "Solve")) == 0){
            if (pid == 0){
                execlp("./functions/Math_Shell_functions/Solve", arguments[1], arguments[2], arguments[3], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "Sqrt")) == 0){
            if (pid == 0){
                execlp("./functions/Math_Shell_functions/Sqrt", arguments[1], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "History")) == 0){
            if (pid == 0){
                execlp("./functions/Math_Shell_functions/History", NULL); 
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

        
        if ((write(commandsForMath, arguments[0], sizeof(arguments[0]))) == -1){
            printf("Writing information to \"Math_Commands\" has failed.\n");
            exit(1);
        }

        wait(NULL); // Waits for the child process to end
        
        // Reset the index so it will not cause an out-of-bounds error.
        argumentsIndex = 0;
    }

    close(commandsForMath);
}