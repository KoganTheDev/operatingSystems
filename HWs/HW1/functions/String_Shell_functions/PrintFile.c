/*
TODO:
-> Gets one parameter - name of a file
-> Prints the file`s content.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

void main(int argc, char* argv[]){

    if (argc != 2){
        printf("The function \"PrintFile\" needs 2 parameters.\n");
        exit(1);
    }

    char* file_name = argv[1];
    char buffer[BUFFER_SIZE];

   int fd = open(file_name, O_RDONLY, 0544);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        printf("Error reading file");
        exit(1);
    }
    
  while (bytes_read > 0){
        printf("%s", buffer);

        if (bytes_read = read(fd, buffer, BUFFER_SIZE - 1) == -1){
        printf("Error reading file");
        exit(1);
        }
    }

    close(fd);
}