/*
TODO:
-> Gets 3 parameters - String, word, location.
-> the function inserts the word in the given location, the thing that was there beforehand is deleted.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv[]){

    if (argc != 4){
        printf("The function \"Replace\" needs 4 parameters.");
        exit(1);
    }

    char* mainString = argv[1];
    char* mainWord = argv[2];
    int place = atoi(argv[3]);

    int stringLength = strlen(mainString);
    int wordLength = strlen(mainWord);
    int startCopying = 0;

    // Check if there are enough bits to insert the new word in its place.
    if (stringLength < place){
        printf("The location does`nt exist in the given string.\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < stringLength; i++){
        if (i == place){
            startCopying = 1;
        }
        if (startCopying && (j < wordLength)){
            mainString[i] = mainWord[j];
            j++;
        }
    }
}