#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

char* findFilePath(char* filename);

void main(int argc, char* argv[]){
    char* word = argv[1];
    char* fileName = argv[2];

    // Find the path of the text file.
    char* textFilePath = findFilePath(fileName);

    



    free(textFilePath);
}


char* findFilePath(char* filename) {
    FILE* pipe;
    char command[1024];
    char* result = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));

    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    sprintf(command, "find / -name \"%s\" 2>/dev/null", filename);

    pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    if (fgets(result, MAX_PATH_LENGTH, pipe) == NULL) {
        strcpy(result, "File not found");
    } else {
        // Remove newline character if present
        result[strcspn(result, "\n")] = 0;
    }

    pclose(pipe);
    return result;
}