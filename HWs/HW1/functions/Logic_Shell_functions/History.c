#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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
int main() {
    int historyFile, bytesRead;
    char buffer[BUFFER_SIZE];
    int i = 1;
    int bufferIndex = 0;

    if ((historyFile = open("./Commands/Logic/Logic_Commands.txt", O_RDONLY)) < 0) {
        printf("Opening the file history for reading has failed.\n");
        exit(1);
    } 

    // Read from the history file and print to the terminal.
    while ((bytesRead = read(historyFile, buffer + bufferIndex, BUFFER_SIZE - bufferIndex - 1)) > 0) {
        buffer[bytesRead + bufferIndex] = '\0'; // Null-terminate the buffer
        bufferIndex = 0;

        char *line = buffer;
        char *newline;

        while ((newline = strchr(line, '\n')) != NULL) {
            *newline = '\0';
            printf("\t%d. %s\n", i++, line);
            line = newline + 1;
        }

        // If there's leftover data in the buffer, move it to the beginning
        bufferIndex = strlen(line);
        memmove(buffer, line, bufferIndex);
    }

    // Handle any remaining data in the buffer
    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';
        printf("\t%d. %s\n", i++, buffer);
    }

    if (bytesRead == -1) {
        printf("Reading from the history file has failed.\n");
        close(historyFile);
        exit(1);
    }

    close(historyFile);
    return 0;
}
