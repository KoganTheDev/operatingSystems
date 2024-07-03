#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void main(int argc, char* argv[]){
    char* word = argv[1];
    char* fileName = argv[2];

    char* pathToFile = strcat("./", fileName);

    int fd = open(pathToFile, O_RDONLY, 0544);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }
    

    



    
}