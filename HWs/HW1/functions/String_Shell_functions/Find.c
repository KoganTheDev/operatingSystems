/*
TODO:
-> gets two parameters, fileName and a Sentence.
-> Looks for the Sentence in the file.
-> If the sentence was found  return "WIN.\n"

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//! TODO: Complete later
void main(int argc, char* argv[]){

    if (argc != 3){
        printf("The function \"Find\" needs 3 arguments.\n");
        exit(1);
    }

    char* sentenceToFind = argv[2];
    int sentenceLength = strlen(sentenceToFind);
    char* lineRead[sentenceLength];
    int textFile;
    int bytesRead;

    //! need to use opendir\Readdir to locate the file.
    if ((textFile = open(argv[1], O_RDONLY, 0)) == -1){
        printf("Opening the file for \"Find\" has failed.\n");
        exit(1);
    }

    if ((lineRead))



    close(textFile);
}