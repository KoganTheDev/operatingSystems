#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    int mainFile, encryptedFile, bytesRead;
    int bufferSize =  atoi(argv[2]);
    char* StrToInsert = argv[3];
    char* buffer[bufferSize];

    if (argc != 4){
        printf("The function must get 4 arguments.\n");
        exit(1);
    }

    if ((mainFile = open(argv[1], O_RDONLY, 0)) < 0){
        printf("Opening the main file for reading has failed.\n");
        exit(1);
    }

    if (mkdir("./encrypted",0700) == -1){
        printf("Making the new directory has failed\n");
        exit(1);
    }

    if ((encryptedFile = open("./encrypted/a.txt", O_RDWR | O_CREAT, 0644)) < 0){
        printf("Opening the new a.txt file in the directory \"encrypted\" has failed.\n");
        exit(1);
    }
    
    while ((bytesRead = read(mainFile, buffer, bufferSize)) > 0){
        write(encryptedFile, buffer, bytesRead);
        if (bytesRead == bufferSize){
            write(encryptedFile,argv[3], strlen(argv[3]));
        }
    }
    
    close(mainFile);
    close(encryptedFile);

    return 0;
}