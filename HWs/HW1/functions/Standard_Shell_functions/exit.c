#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void emptyDirectory();

/**
 * Summary:
 * Main function entry point.
 *
 * Details:
 * This function demonstrates process forking to execute a child process that runs the "Goodbye" function.
 * It also calls emptyDirectory() to remove specific files and directories related to commands.
 * Finally, it removes the "./Commands" directory after waiting for the child process to complete.
 *
 * Arguments:
 * None.
 *
 * Returns:
 * None.
 */
void main(){
    int pid;
    
    // Fork a child process
    if ((pid = fork()) < 0){
        printf("Forking in the function \"exit\" has failed.");
        exit(1);
    }
    if (pid == 0){
        // Child process executes "Goodbye" function
        execlp("./functions/Standard_Shell_functions/Goodbye", "Goodbye", NULL);
    }
    else{
        // Parent process
        emptyDirectory(); // Clean up command directories
        rmdir("./Commands"); // Remove main Commands directory
        printf("Commands dir removed.\n");
        wait(NULL); // Wait for child process to finish
    }
}

/**
 * Summary:
 * Empties specific directories related to command storage.
 *
 * Details:
 * This function removes three command files and their respective directories:
 * - "./Commands/Math/Math_Commands.txt"
 * - "./Commands/Logic/Logic_Commands.txt"
 * - "./Commands/String/String_Commands.txt"
 *
 * It also removes the directories:
 * - "./Commands/Math"
 * - "./Commands/String"
 * - "./Commands/Logic"
 *
 * Arguments:
 * None.
 *
 * Returns:
 * None.
 */
void emptyDirectory(){
    char* filename = "./Commands/Math/Math_Commands.txt";
    char* filename2 = "./Commands/Logic/Logic_Commands.txt";
    char* filename3 = "./Commands/String/String_Commands.txt";

    char* mathDir = "./Commands/Math";
    char* stringDir = "./Commands/String";
    char* logicDir = "./Commands/Logic";

    // Remove specific files
    remove(filename);
    remove(filename2);
    remove(filename3);

    // Remove specific directories
    rmdir(mathDir);
    rmdir(stringDir);
    rmdir(logicDir);
}