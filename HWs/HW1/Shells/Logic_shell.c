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
        printf("To run the \"Logic_shell\" you need to give one argument which is \"Logic\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[4];
    char* token;
    int argumentsIndex = 0;
    int commandsForLogic;
    int pid;

    if(mkdir("./Commands/Logic",0700) == -1){
        printf("Making the new directory has failed.\n");
        exit(1);
    }
    
    if ((commandsForLogic = open("./Commands/Logic/Logic_Commands", O_RDWR | O_CREAT, 0644 )) < 0){
        printf("Opening the file for the commands of \"Logic_shell\" has failed.\n");
        exit(1);
    }

    while (1){
        printf("LogicShell>");
        
        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL){
            printf("fgets in \"Logic_shell\" has failed to grab input.\n");
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
                printf("Forking has failed for the Logic_Shell.\n");
                exit(1);
        }

        // Look for the exact match function to run
        if ((strcmp(arguments[0], "Cls")) == 0){
            break;
        }
        else if ((strcmp(arguments[0], "Highbit")) == 0){
            if (pid == 0){
                execlp("./functions/Logic_Shell_functions/Highbit", arguments[1], NULL); 
            } 
        }
        else if ((strcmp(arguments[0], "DectoBin")) == 0){
            if (pid == 0){
                execlp("./functions/Logic_Shell_functions/DectoBin", arguments[1], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "DectoHex")) == 0){
            if (pid == 0){
                execlp("./functions/Logic_Shell_functions/DectoHex", arguments[1], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "History")) == 0){
            if (pid == 0){
                execlp("./functions/Logic_Shell_functions/History", NULL); 
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

        
        if ((write(commandsForLogic, arguments[0], sizeof(arguments[0]))) == -1){
            printf("Writing information to \"Logic_Commands\" has failed.\n");
            exit(1);
        }

        wait(NULL); // Waits for the child process to end
        
        // Reset the index so it will not cause an out-of-bounds error.
        argumentsIndex = 0;
    }

    close(commandsForLogic);
}