#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

/**
 * Summary:
 * Reads and displays all commands run by the user in Logic_Shell.
 *
 * Details:
 * Opens a file containing the history of commands and outputs each command to the terminal.
 * If opening or reading the file fails, the program exits with an error message.
 *
 * Arguments:
 * None.
 *
 * Returns:
 * None.
 */
void main(){
    int historyFile, bytesRead;
    char buffer[BUFFER_SIZE];

    if ((historyFile = open("./Commands/Logic/Logic_Commands.txt", O_RDONLY, 0)) < 0){
        printf("Opening the file history for reading has failed.\n");
        exit(1);
    } 

    // Read from the history file and put in inside the terminal.
    if ((bytesRead = read(historyFile, buffer, BUFFER_SIZE)) == -1){
        printf("Reading from the history file has failed.\n");
        exit(1);
    }

    while (bytesRead > 0){
        printf("%s", buffer);

        if (bytesRead = read(historyFile, buffer, BUFFER_SIZE) == -1){
        printf("Reading from the history file has failed.\n");
        exit(1);
        }
    }

    close(historyFile);
}