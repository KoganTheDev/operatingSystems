#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copyWordIntoSentence(char* sentence, char* word, int location);

int main(int argc, char* argv[]) {

    char* sentence = argv[0];
    char* word = argv[1];
    int location = atoi(argv[2]);    

    copyWordIntoSentence(sentence, word, location);
    return 0; // For a successful run.
}


void copyWordIntoSentence(char* sentence, char* word, int location) {
    int sentenceLength = strlen(sentence);
    int wordLength = strlen(word);

    // Ensure the location is valid
    if (location < 0 || location > sentenceLength) {
        printf("Invalid location.\n");
        return;
    }

    // Create a new buffer to hold the new sentence
    char* newSentence = (char*)malloc(sentenceLength + wordLength + 1); // +1 for the null terminator
    if (newSentence == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Copy the part of the sentence before the location
    strncpy(newSentence, sentence, location);
    
    // Copy the word
    strcpy(newSentence + location, word);

    // Copy the part of the sentence after the location
    strcpy(newSentence + location + wordLength, sentence + location);

    // Copy the new sentence back into the original sentence buffer
    strcpy(sentence, newSentence);

    printf("%s\n", newSentence);

    // Free the allocated memory
    free(newSentence);
}