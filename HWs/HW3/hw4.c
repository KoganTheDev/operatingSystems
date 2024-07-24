#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct Node {
    int id;
    struct Node* next;
} Node; 

// Function prototypes
void* mainFunctionForCustomerThreads(void* threadIDNumber);
void* mainFunctionForLibrarianThreads(void* threadIDNumber);

// Linked List functions
Node* initLinkedList(int threadID);
Node* addNodeToLinkedList(Node* root, int threadId);
void removeTailFromTheLinkedList(Node** root);
int grabTailID(Node* linkedList);

// Global variables
int N = 10; // Number of customer threads
int K = 4;  // Number of chairs in the library waiting area

// Semaphores for synchronization
sem_t semForEnteringTheLibrary; // Controls library entry
sem_t semFreeLibrarian;         // Tracks available librarians
sem_t semFreeCustomers;         // Signals availability of customers
sem_t semFreeChairToSitOn;      // Manages free chairs for waiting customers
sem_t semCustomerOutside;       // Manages customers waiting outside
sem_t mutexChairsList;          // Mutex for handling access to the list of chairs
sem_t mutexLookingForInformationList; // Mutex for handling access to the list of people looking for information
sem_t mutexOutOfLibrary;        // Mutex for controlling "out of library" print

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("The program receives no parameters but its name.\n");
        exit(1);
    }

    pthread_t customerThreads[N + 2], librarianThreads[3];
    int threadCheck, i, threadNumber[N + 2];
    
    // Initialize the semaphores.
    sem_init(&semForEnteringTheLibrary, 0, N);
    sem_init(&semFreeLibrarian, 0, 3); // Initially there are 3 free librarians
    sem_init(&semFreeCustomers, 0, 0);
    sem_init(&semFreeChairToSitOn, 0, K); 
    sem_init(&semCustomerOutside, 0, N);
    sem_init(&mutexChairsList, 0, 1);
    sem_init(&mutexLookingForInformationList, 0, 1);
    sem_init(&mutexOutOfLibrary, 0, 1); // Initialize mutex for "out of library" print

    // Initialize the numbers in the array named thread_number.
    for (i = 0; i < N + 2; i++) {
        threadNumber[i] = i;
    }

    // Create N+2 threads for the customers.
    for (i = 0; i < (N + 2); i++) {
        threadCheck = pthread_create(&customerThreads[i], NULL, mainFunctionForCustomerThreads, &threadNumber[i]);
        if (threadCheck) { // Creating a thread has failed.
            printf("Creating a thread for a customer has failed.\n");
            exit(1);
        }
    }

    // Create 3 threads for the librarians.
    for (i = 0; i < 3; i++) {
        threadCheck = pthread_create(&librarianThreads[i], NULL, mainFunctionForLibrarianThreads, &threadNumber[i]);
        if (threadCheck) { // Creating a thread has failed.
            printf("Creating a thread for a librarian has failed.\n");
            exit(1);
        }
    }

    // Join the threads
    for (i = 0; i < 3; i++) {
        pthread_join(librarianThreads[i], NULL);
    }
    for (i = 0; i < (N + 2); i++) {
        pthread_join(customerThreads[i], NULL);
    }

    // Destroy the semaphores.
    sem_destroy(&semForEnteringTheLibrary);
    sem_destroy(&semFreeLibrarian);
    sem_destroy(&semFreeCustomers);
    sem_destroy(&semFreeChairToSitOn);
    sem_destroy(&semCustomerOutside);
    sem_destroy(&mutexChairsList);
    sem_destroy(&mutexLookingForInformationList);
    sem_destroy(&mutexOutOfLibrary);

    return 0;
}

void* mainFunctionForCustomerThreads(void* threadNumber) {
    Node* customersSittingInAChair = NULL;
    Node* customersLookingForInformation = NULL;
    int threadID = *(int*)threadNumber;
    int placeLeftInTheLibrary;
    int availableLibrarians;
    int availableChairs;

    while (1) { 
        sem_getvalue(&semForEnteringTheLibrary, &placeLeftInTheLibrary);

        if (placeLeftInTheLibrary == 0) {
            // Wait for a spot to become available and try again
            sem_wait(&semCustomerOutside);
            sem_post(&semCustomerOutside);
            printf("I'm Reader #%d, I'm out of library.\n", (threadID + 1));
        }
        
        // Enter the library
        sem_wait(&semForEnteringTheLibrary);
        printf("I'm Reader #%d, I got into the library.\n", (threadID + 1));

        while (1) {
            sem_getvalue(&semFreeLibrarian, &availableLibrarians);
            if (availableLibrarians > 0) {
                sem_wait(&semFreeLibrarian);
                printf("I'm Reader #%d, I'm speaking with a librarian.\n", (threadID + 1));
                sem_post(&semFreeCustomers);
                sem_post(&semForEnteringTheLibrary); // Allow others to enter the library
                break;
            } else {
                sem_getvalue(&semFreeChairToSitOn, &availableChairs);
                if (availableChairs > 0) {
                    sem_wait(&semFreeChairToSitOn);

                    // Add this customer to the chair list
                    sem_wait(&mutexChairsList);
                    customersSittingInAChair = addNodeToLinkedList(customersSittingInAChair, threadID);
                    sem_post(&mutexChairsList);

                    // Check if this customer is the last one in the chair list
                    if (grabTailID(customersSittingInAChair) == threadID) {
                        printf("I'm Reader #%d, I'm reading a book.\n", (threadID + 1));
                        // sleep(2); // Simulate time spent reading
                        sem_wait(&mutexChairsList);
                        removeTailFromTheLinkedList(&customersSittingInAChair);
                        sem_post(&mutexChairsList);
                        sem_post(&semFreeChairToSitOn);
                        break;
                    }
                } else {
                    // Add this customer to the list of people looking for information
                    sem_wait(&mutexLookingForInformationList);
                    customersLookingForInformation = addNodeToLinkedList(customersLookingForInformation, threadID);
                    sem_post(&mutexLookingForInformationList);

                    // Wait until a chair becomes available
                    while (1) {
                        sem_getvalue(&semFreeChairToSitOn, &availableChairs);
                        if (availableChairs > 0) {
                            if (grabTailID(customersLookingForInformation) == threadID) {
                                sem_wait(&mutexLookingForInformationList);
                                removeTailFromTheLinkedList(&customersLookingForInformation);
                                sem_post(&mutexLookingForInformationList);
                                break;
                            }
                        }
                    }
                }
            }
        }

        sem_post(&semForEnteringTheLibrary);
        printf("I'm Reader #%d, I've finished.\n", (threadID + 1));
    }

    return NULL;
}

void* mainFunctionForLibrarianThreads(void* threadNumber) {
    int threadID = *(int*)threadNumber;

    while (1) {
        sem_wait(&semFreeCustomers);
        printf("I'm Librarian #%d, I'm working now.\n", (threadID + 1));
        sleep(1);
        sem_post(&semFreeLibrarian);
    }
}

Node* initLinkedList(int threadID) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->next = NULL;
    root->id = threadID;
    return root;
}

Node* addNodeToLinkedList(Node* root, int threadId) {
    Node* newRoot = (Node*)malloc(sizeof(Node));
    newRoot->id = threadId;
    newRoot->next = root;
    return newRoot;
}

void removeTailFromTheLinkedList(Node** root) {
    Node* currentNode = *root;
    Node* previousNode = NULL;
    if (currentNode == NULL) return;

    while (currentNode->next != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (previousNode == NULL) {
        free(*root);
        *root = NULL;
    } else {
        free(currentNode);
        previousNode->next = NULL;
    }
}

int grabTailID(Node* linkedList) {
    Node* currentNode = linkedList;
    if (currentNode == NULL) return -1;

    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    return currentNode->id;
}
