#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20

int array[N]; // Global array of size N.
pthread_t id[2]; // Global thread IDs.

// Declaration of the functions.
void* searchFromTheRight(void* threadPointer);
void* searchFromTheLeft(void* threadPointer);
int splitArraySize(int arraySize);

int main(int argc, char* argv[]) {

    if (argc != 1) {
        printf("ERROR ; please enter 1 parameter\n");
        exit(1);
    }

    int i, userInput;
    int* foundFromRight;
    int* foundFromLeft;

    for (i = 0; i < N; i++) {
        array[i] = rand() % 101;
    }

    // Temporary array print
    for (i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Please enter a number between 0 to 100: ");
    scanf("%d", &userInput);

    while (!(0 <= userInput && userInput <= 100)) {
        printf("Invalid number\n");
        printf("Please enter a number between 0 to 100: ");
        scanf("%d", &userInput);
    }

    pthread_create(&id[0], NULL, searchFromTheRight, &userInput);
    pthread_create(&id[1], NULL, searchFromTheLeft, &userInput);

    pthread_join(id[0], (void**)&foundFromRight);
    pthread_join(id[1], (void**)&foundFromLeft);

    if (*foundFromRight || *foundFromLeft) {
        printf("The number %d exists in the array.\n", userInput);
    } else {
        printf("The number %d does not exist in the array.\n", userInput);
    }

    // Free allocated memory
    free(foundFromRight);
    free(foundFromLeft);

    return 0;
}

int splitArraySize(int arraySize) {
    if ((arraySize % 2) == 0) {
        return arraySize / 2;
    } else {
        return ((arraySize + 1) / 2);
    }
}

void* searchFromTheRight(void* threadPointer) {
    int userInput = *((int*)threadPointer);
    int limit = splitArraySize(N);
    int* isUserInputFound = malloc(sizeof(int));
    *isUserInputFound = 0;

    for (int i = 0; i < limit; i++) {
        if (array[i] == userInput) {
            *isUserInputFound = 1;
            pthread_cancel(id[1]);
            break;
        }
    }

    return (void*)isUserInputFound;
}

void* searchFromTheLeft(void* threadPointer) {
    int userInput = *((int*)threadPointer);
    int limit = splitArraySize(N);
    int* isUserInputFound = malloc(sizeof(int));
    *isUserInputFound = 0;

    for (int i = limit; i < N; i++) {
        if (array[i] == userInput) {
            *isUserInputFound = 1;
            pthread_cancel(id[0]);
            break;
        }
    }

    return (void*)isUserInputFound;
}
