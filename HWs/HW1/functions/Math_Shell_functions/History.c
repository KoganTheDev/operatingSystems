#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

/**
 * Summary:
 * Reads and displays all commands run by the user in Math_Shell.
 *
 * Details:
 * Opens a file containing the history of commands and outputs each command to the terminal.
 * If opening or reading the file fails, the program exits with an error message.
 *
 * Arguments:
 * None.
 *
 * Returns:
 * 0 - to indicate a successful run.
 */
int main() {
    int historyFile;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];

    // Open the history file for reading
    historyFile = open("./Commands/Math/Math_Commands.txt", O_RDONLY);
    if (historyFile < 0) {
        perror("Opening the file history for reading has failed");
        exit(EXIT_FAILURE);
    }

    // Read from the history file and output to the terminal
    while ((bytesRead = read(historyFile, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Writing to the terminal has failed");
            close(historyFile);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) {
        perror("Reading from the history file has failed");
        close(historyFile);
        exit(EXIT_FAILURE);
    }

    close(historyFile);
    return 0;
}
