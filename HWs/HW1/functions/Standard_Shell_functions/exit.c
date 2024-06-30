/*
TODO: 
-> gets No Parameters.
-> Calls the function Goodbye.c
-> Deletes the directory Commands
-> Closes Standard_Shell and goes back to Shell.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
    int pid;
    
    if ((pid = fork()) < 0){
        printf("Forking in the function \"exit\" has failed.");
        exit(1);
    }
    if (pid == 0){
        execlp("./functions/Standard_Shell_functions/Goodbye", NULL);
    }
    else{
        rmdir("./Commands");
    }
}