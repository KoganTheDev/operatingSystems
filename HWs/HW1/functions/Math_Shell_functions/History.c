/*
TODO:
gets no parameters
Shows all of the commands the user ran using Math_Shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE = 256


void main(){
    int historyFile, bytesRead;
    char[256] buffer;

    if ((historyFile = open(./Commands/Math, O_RDONLY, 0)) < 0){
        printf("Opening the file history for reading has failed.\n");
        exit(1);
    } 

    // Read from the history file and put in inside the terminal.
    if (bytesRead = read(historyFile, buffer, BUFFER_SIZE) == -1){
        printf("Reading from the history file has failed.\n");
        exit(1);
    }

    // TODO: Can cause problems.
    while (bytesRead > 0){
        printf("%s", buffer);

        if (bytesRead = read(historyFile, buffer, BUFFER_SIZE) == -1){
        printf("Reading from the history file has failed.\n");
        exit(1);
        }
    }

    close(historyFile);
}