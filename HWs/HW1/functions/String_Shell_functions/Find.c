#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> // Include errno for error handling

#define MAX_LINE_LENGTH 256

void searchWordInFile(const char* word, const char* fileName);

/**
 * Summary:
 * Main function entry point.
 *
 * Details:
 * Retrieves the file name and word to search from command-line arguments.
 * Calls searchWordInFile() function to perform the search operation.
 *
 * Arguments:
 * @param argc - (int): Number of command-line arguments.
 * @param argv - (char*[]): Array of command-line argument strings.
 *
 * Returns:
 * @return - (int): Exit status of the program.
 */
int main(int argc, char* argv[]) {
    char* fileName = argv[1];
    char* word = argv[2];

    searchWordInFile(word, fileName);

    return 0;
}

/**
 * Summary:
 * Searches for a word in a specified file.
 *
 * Details:
 * Opens the file specified by fileName and searches for the occurrence of the word.
 * Prints "WIN" if the word is found in any line of the file; otherwise, prints "Try Again".
 * Handles errors related to file opening, reading, and closing using perror() and exits on failure.
 *
 * Arguments:
 * @param word - (const char*): The word to search for in the file.
 * @param fileName - (const char*): The name of the file to search in.
 *
 * Returns:
 * None.
 */
void searchWordInFile(const char* word, const char* fileName) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    ssize_t bytes_read;
    int found = 0;

    while ((bytes_read = read(fd, line, MAX_LINE_LENGTH - 1)) > 0) {
        // Null-terminate the line
        line[bytes_read] = '\0';

        // Search for the word in the line
        if (strstr(line, word) != NULL) {
            printf("WIN\n");
            found = 1;
            break; // Exit the loop if the word is found
        }
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd); // Close file descriptor before returning
        exit(1);
    }

    close(fd); // Close file descriptor at the end of usage

    // If the word is not found, indicate it
    if (!found) {
        printf("Try Again\n");
    }
}
