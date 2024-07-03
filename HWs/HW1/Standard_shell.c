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
#include <dirent.h>
#include <errno.h>

#define SIZE_OF_INPUT 256
#define MAX_ARGS 4

void createNewDir();
void parseUserInput(char* userInput, char* arguments[], int* argumentsIndex);

void main(int argc, char* argv[]){

    if (argc != 1){
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char userInput[SIZE_OF_INPUT];
    char* arguments[MAX_ARGS];
    int argumentsIndex;
    int pid;

    createNewDir();
    
    while (1){
        printf("StandardShell > ");
        
        // Grab input from the user until you get a '\n' character.
        if ((fgets(userInput, SIZE_OF_INPUT, stdin)) == NULL){
            printf("fgets in \"Standard_shell\" has failed to grab input.\n");
            exit(1);
        }

        // Remove the new line character
        userInput[strcspn(userInput, "\n")] = 0;

        parseUserInput(userInput, arguments, &argumentsIndex);

        // Special case: the user didn`t insert input therefore allow him to try inserting once again.
        if (argumentsIndex == 0){
            printf("No input received.\n");
            continue;
        }

        if ((pid = fork()) < 0){
                printf("Forking has failed for the Standard_Shell.\n");
                exit(1);
        }

        // Look for the exact match function to run
        if ((strcmp(arguments[0], "exit")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/exit", "exit", NULL);
            }
            else{ // Parent`s clause
                break;
            }
        }
        else if ((strcmp(arguments[0], "Math")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/Math", "Math", NULL); 
            } 
        }
        else if ((strcmp(arguments[0], "Logic")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/Logic", "Logic", NULL); 
            }
        }
        else if ((strcmp(arguments[0], "String")) == 0){
            if (pid == 0){
                execlp("./functions/Standard_Shell_functions/String", "String", NULL); 
            }
        }
        else{
            // Try executing a regular shell function.
            if (pid == 0){
                if (argumentsIndex == 1){
                    execlp(arguments[0], arguments[0], NULL); 
                }
                else if (argumentsIndex == 2){
                    execlp(arguments[0], arguments[0], arguments[1], NULL); 
                }
                else if (argumentsIndex == 3){
                    execlp(arguments[0], arguments[0], arguments[1], arguments[2], NULL); 
                }
                else{
                    execlp(arguments[0], arguments[0], arguments[1], arguments[2], arguments[3], NULL);
                }
                printf("Not Supported\n");
            }
        }

        // When the child process didn`t enter any functions.
        if (pid == 0){
            exit(0);
        }
        
        wait(NULL); // Waits for the child process to end
    }
    wait(NULL); // Wait for exit to end.
}


void createNewDir(){
    DIR* dir = opendir("./Commands");

    if (dir){
        closedir(dir); // Closes the file descriptor
        printf("The directory ./Commands already exists.\n");
    }
    else if (errno == ENOENT){ // ENOENT in this case will say that there`s no entry for this dir, therefore we`ll create it.
        if(mkdir("./Commands",0700) == -1){
            printf("Making the new directory has failed.\n");
            exit(1);
        }
        else{
        printf("Commands dir created.\n");
        }
    }
}

void parseUserInput(char* userInput, char *arguments[], int* argumentsIndex){
    *argumentsIndex = 0;

    char* token = strtok(userInput, " ");

    arguments[*argumentsIndex] = token;
    (*argumentsIndex)++;

    while (token != NULL && *argumentsIndex < MAX_ARGS){
        arguments[*argumentsIndex] = token;
        token = strtok(NULL, " ");
        (*argumentsIndex)++;
    }
}
