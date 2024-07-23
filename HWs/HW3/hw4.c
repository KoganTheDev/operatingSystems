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
sem_t semCustomerOutside;

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
    sem_init(&semFreeCustomers, 0 , 0);
    sem_init(&semFreeChairToSitOn, 0, K); 
    sem_init(&semCustomerOutside, 0, N - 2);

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

    return 0;
}

void* mainFunctionForCustomerThreads(void* threadNumber) {
    Node* customersSittingInAChair = NULL;
    Node* customersLookingForInformation = NULL;
    Node* outsideLinkedList = NULL;
    int threadID = *(int*)threadNumber;
    int placeLeftInTheLibrary;
    int availableLibrarians;
    int availableChairs;
    int customerWaitingOutside;

    while (1) {
        sem_getvalue(&semForEnteringTheLibrary, &placeLeftInTheLibrary);

        if (placeLeftInTheLibrary == 0) { // create a queue for managing threads
            if (outsideLinkedList == NULL){
                outsideLinkedList = initLinkedList(threadID);
            }
            else{
                outsideLinkedList = addNodeToLinkedList(outsideLinkedList ,threadID);
            }
            printf("I'm Reader #%d, I'm out of library.\n", (threadID + 1));
            sem_wait(&semCustomerOutside);
            // As soon as someone gets through.
            customerWaitingOutside = grabTailID(outsideLinkedList);
            removeTailFromTheLinkedList(&outsideLinkedList);
        }

        

        sem_wait(&semForEnteringTheLibrary);
        printf("I'm Reader #%d, I got into the library.\n", (threadID + 1));

        while (1) {
            sem_getvalue(&semFreeLibrarian, &availableLibrarians);
            if (availableLibrarians > 0) {
                sem_wait(&semFreeLibrarian);
                printf("I'm Reader #%d, I'm speaking with a librarian.\n", (threadID + 1));
                sem_post(&semFreeCustomers);
                sem_post(&semForEnteringTheLibrary);
                printf("I'm Reader #%d, I've finished.\n", (threadID + 1));
                break;
            }

            sem_getvalue(&semFreeChairToSitOn, &availableChairs);
            if (availableChairs > 0) {
                sem_wait(&semFreeChairToSitOn);

                if (customersSittingInAChair == NULL) {
                    customersSittingInAChair = initLinkedList(threadID);
                } else {
                    customersSittingInAChair = addNodeToLinkedList(customersSittingInAChair, threadID);
                }

                if (grabTailID(customersSittingInAChair) == threadID) {
                    sem_wait(&semFreeLibrarian);
                    removeTailFromTheLinkedList(&customersSittingInAChair);
                    sem_post(&semFreeChairToSitOn);
                    printf("I'm Reader #%d, I'm speaking with a librarian.\n", (threadID + 1));
                    sem_post(&semFreeCustomers);
                    sem_post(&semForEnteringTheLibrary);
                    sem_post(&semCustomerOutside);
                    printf("I'm Reader #%d, I've finished.\n", (threadID + 1));
                    break;
                }
            } else {
                if (customersLookingForInformation == NULL) {
                    customersLookingForInformation = initLinkedList(threadID);
                } else {
                    customersLookingForInformation = addNodeToLinkedList(customersLookingForInformation, threadID);
                }

                printf("I'm Reader #%d, I'm reading a book.\n", (threadID + 1));

                while (1) {
                    sem_getvalue(&semFreeChairToSitOn, &availableChairs);
                    if (availableChairs > 0 && grabTailID(customersLookingForInformation) == threadID) {
                        removeTailFromTheLinkedList(&customersLookingForInformation);
                        sem_post(&semFreeChairToSitOn);
                        break;
                    }
                }
            }
        }
    }

    return NULL;
}

void* mainFunctionForLibrarianThreads(void* threadNumber) {
    int threadID = *(int*)threadNumber;

    while (1) {
        sem_wait(&semFreeCustomers);
        printf("I'm Librarian #%d, I'm working now.\n", (threadID + 1));
        //sleep(1);
        sem_post(&semFreeLibrarian);
    }

    return NULL;
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

    if (currentNode == NULL) {
        return;
    }

    while (currentNode->next != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    free(currentNode);

    if (previousNode != NULL) {
        previousNode->next = NULL;
    } else {
        *root = NULL;
    }
}

int grabTailID(Node* linkedList) {
    Node* root = linkedList;
    while (root && root->next != NULL) {
        root = root->next;
    }
    return root->id;
}
