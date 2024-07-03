#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void printFileContent(const char* file_name);

/**
 * Summary:
 * Main function entry point.
 *
 * Details:
 * Takes a filename as a command-line argument and calls printFileContent() to print its content.
 *
 * Arguments:
 * @param argc - (int): Number of command-line arguments.
 * @param argv - (char*[]): Array of command-line argument strings.
 *
 * Returns:
 * @return - (int): Exit status of the program. Returns 0 for successful execution.
 */
int main(int argc, char* argv[]) {
    char* file_name = argv[1];

    // Print the content of the specified file
    printFileContent(file_name);
    printf("\n");

    return 0; // For a successful run.
}

/**
 * Summary:
 * Prints the content of a file to the standard output.
 *
 * Details:
 * Opens the specified file for reading, reads its content in chunks, and prints each chunk to the standard output.
 * Handles errors related to file opening, reading, and closing using perror to print error messages.
 *
 * Arguments:
 * @param file_name - (const char*): Name of the file to be read and printed.
 *
 * Returns:
 * None.
 */
void printFileContent(const char* file_name) {
    char buffer[BUFFER_SIZE];

    // Open the file for reading
    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    ssize_t bytes_read;

    // Read and print the file content in chunks
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer after reading
        printf("%s", buffer);
    }

    // Check for read error
    if (bytes_read == -1) {
        perror("Error reading file");
        exit(1);
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(1);
    }
}