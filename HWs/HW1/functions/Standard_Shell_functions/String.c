/*
TODO: 
-> gets No Parameters.
-> Runs String_Shell
-> Creates new directory called "String" in "Commands"
-> Creates a new file called "String_Commands" in the path Commands/String

this func Saves the commands given from the user for String_Shell

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SIZE_OF_INPUT 256

void main(int argc, char* argv[]){

    if (argc != 1){
        printf("To run the \"String_shell\" you need to give one argument which is \"String\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[4];
    char* token;
    int argumentsIndex = 0;
    int commandsForString;
    int pid;

    
    if(mkdir("./Commands/String",0700) == -1){
        printf("Making the new directory has failed.\n");
        exit(1);
    }
    
    if ((commandsForString = open("./Commands/String/String_Commands", O_RDWR | O_CREAT, 0644 )) < 0){
        printf("Opening the file for the commands of \"String_shell\" has failed.\n");
        exit(1);
    }

    while (1){
        printf("StringShell>");
        
        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL){
            printf("fgets in \"String_shell\" has failed to grab input.\n");
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
                printf("Forking has failed for the String_Shell.\n");
                exit(1);
        }

        // Look for the exact match function to run
        if ((strcmp(arguments[0], "Cls")) == 0){
            break;
        }
        else if ((strcmp(arguments[0], "Find")) == 0){
            if (pid == 0){
                execlp("./functions/String_Shell_functions/Find", arguments[1], arguments[2], NULL); 
            } 
        }
        else if ((strcmp(arguments[0], "Replace")) == 0){
            if (pid == 0){
                execlp("./functions/String_Shell_functions/Replace", arguments[1], arguments[2], arguments[3], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "PrintFile")) == 0){
            if (pid == 0){
                execlp("./functions/String_Shell_functions/PrintFile", arguments[1], NULL); 
            }
        }
        else if ((strcmp(arguments[0], "History")) == 0){
            if (pid == 0){
                execlp("./functions/String_Shell_functions/History", NULL); 
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

        
        if ((write(commandsForString, arguments[0], sizeof(arguments[0]))) == -1){
            printf("Writing information to \"String_Commands\" has failed.\n");
            exit(1);
        }

        wait(NULL); // Waits for the child process to end
        
        // Reset the index so it will not cause an out-of-bounds error.
        argumentsIndex = 0;
    }

    close(commandsForString);
}