#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int firstFile, secondFile, newTextFile, charCounterFirstFile, charCountSecondFile;
    int i = 0,j = 0;
    char bufferFirstFile[256], bufferSecondFile[256];

    if (argc != 3){
        printf("The function must get 3 arguments.\n");
        exit(1);
    }

    // Open both of the files.
    firstFile = open(argv[1], O_RDONLY, 0);
    if (firstFile < 0){
        printf("First file has failed to open.\n");
        exit(1);
    } 
    secondFile = open(argv[2], O_RDONLY, 0);
    if (secondFile < 0){
        printf("Second file has failed to open.\n");
        exit(1);
    } 

    // Looks for a difference
    while ((charCounterFirstFile = read(firstFile, bufferFirstFile, 256)) > 0 && (charCountSecondFile = read(secondFile, bufferSecondFile, 256)) > 0){
        while (i < charCounterFirstFile && j < charCountSecondFile){
            if (bufferFirstFile[i] != bufferSecondFile[j]){
                printf("Different files");
                newTextFile = open("compare.txt", O_WRONLY | O_CREAT, 0644);
                if (newTextFile < 0){
                    printf("The new Text file has failed to open.\n");
                    exit(1);
                }

                // Move the file pointers backwards
                lseek(firstFile, 0, SEEK_SET);
                lseek(secondFile, 0, SEEK_SET);

                // Read each file until the end and write it in the new text file.
                while ((charCounterFirstFile = read(firstFile, bufferFirstFile, 256)) > 0){
                    write(newTextFile, bufferFirstFile, 256);

                }
                while ((charCountSecondFile = read(secondFile, bufferSecondFile, 256)) > 0){
                    write(newTextFile, bufferSecondFile, 256);
                }

                close(newTextFile);
                return 0;
            }

            i++;
            j++;
        }
        i = 0;
        j = 0;
    }
    
    // Close all of the file handlers.
    close(firstFile);
    close(secondFile);
    printf("Identical files\n");

    return 0;
}