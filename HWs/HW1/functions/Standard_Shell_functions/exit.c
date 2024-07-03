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
#include <fcntl.h>
#include <sys/wait.h>

void emptyDirectory();

void main(){
    int pid;
    
    if ((pid = fork()) < 0){
        printf("Forking in the function \"exit\" has failed.");
        exit(1);
    }
    if (pid == 0){
        execlp("./functions/Standard_Shell_functions/Goodbye", "Goodbye", NULL);
    }
    else{
        emptyDirectory();
        rmdir("./Commands");
        printf("Commands dir removed.\n");
        wait(NULL);
    }
}

void emptyDirectory(){
    char* filename = "./Commands/Math/Math_Commands.txt";
    char* filename2 = "./Commands/Logic/Logic_Commands.txt";
    char* filename3 = "./Commands/String/String_Commands.txt";

    char* mathDir = "./Commands/Math";
    char* stringDir = "./Commands/String";
    char* logicDir = "./Commands/Logic";

    remove(filename);
    remove(filename2);
    remove(filename3);

    rmdir(mathDir);
    rmdir(stringDir);
    rmdir(logicDir);
}