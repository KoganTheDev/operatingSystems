#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct Node{
    int id;
    struct Node* next;
} Node; 

// "Main" functions for the customer and librarian thread accordingly. 
void* mainFunctionForCustomerThreads(void* threadIDNumber);
void* mainFunctionForLibrarianThreads(void* threadIDNumber);

// Linked List functions
Node* initLinkedList(int threadID);
Node* addNodeToLinkedList(Node* root, int threadId);
void removeTailFromTheLinkedList(Node** root);
int grabTailID(Node* linkedList);

int N = 10; // Number of customer threads
int K = 4;  // Number of chairs in the library waiting area

// Semaphores for synchronization
sem_t semForEnteringTheLibrary; // Controls library entry
sem_t semFreeLibrarian;         // Tracks available librarians
sem_t semFreeCustomers; // Signals availability of customers
sem_t semFreeChairToSitOn;   // Manages free chairs for waiting customers


int main(int argc,char* argv[]){

    if (argc != 1){
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

    // Initialize the numbers in the array named thread_number.
    for (i = 0; i < N + 2; i++){
        threadNumber[i] = i;
    }

    // Create N+2 threads for the customers.
    for (i = 0; i < (N + 2); i++){
        threadCheck = pthread_create(&customerThreads[i], NULL, mainFunctionForCustomerThreads, &threadNumber[i]);
        if (threadCheck){ // Creating a thread has failed.
            printf("Creating a thread for a customer has failed.\n");
            exit(1);
        }
    }

    // Create 3 threads for the librarians.
    for (i = 0; i < 3; i++){
        threadCheck = pthread_create(&librarianThreads[i], NULL, mainFunctionForLibrarianThreads, &threadNumber[i]);
        if (threadCheck){ // Creating a thread has failed.
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
}


void* mainFunctionForCustomerThreads(void* threadNumber){
    Node* customersSittingInAChair = NULL;
    Node* customersLookingForInformation = NULL;
    int threadID = *(int*)threadNumber; // Grab the id of the thread and put it in a local variable.
    int placeLeftInTheLibrary; // Stores how many people can enter the library using the semaphore.
    int availableLibrarians;
    int availableChairs;

    while(1){ 
        sem_getvalue(&semForEnteringTheLibrary, &placeLeftInTheLibrary);

        if (placeLeftInTheLibrary){
            printf("I`m Reader #%d, I got into the library.\n", (threadID + 1));
        }
        else{
            printf("I`m Reader #%d, I`m out of library.\n", (threadID + 1));
            continue;
        }
        
        // "Library entrance".
        sem_wait(&semForEnteringTheLibrary); // Keep the customers outside if there`s no more place for new customers.
        
        while(1){
            sem_getvalue(&semFreeLibrarian, &availableLibrarians);
            if (availableLibrarians > 0){
                sem_wait(&semFreeLibrarian);
                printf("I`m Reader #%d, I`m speaking with a librarian.\n", (threadID + 1));
                break;
            }
            else{
                while(1){
                    /* sit in chair or look for information. */
                    sem_getvalue(&semFreeChairToSitOn, &availableChairs);

                    if (availableChairs != 0){ // There are free chairs to sit on.
                        sem_wait(&semFreeChairToSitOn);

                        if (customersSittingInAChair == NULL){
                            customersSittingInAChair = initLinkedList(threadID);
                        }
                        else{
                            addNodeToLinkedList(customersSittingInAChair, threadID);
                        }
                        
                        // Check if there are free librarians, if so leave your chair and go speak with a librarian.
                        sem_getvalue(&semFreeLibrarian, &availableLibrarians);
                        if (availableLibrarians > 0 && (grabTailID(customersSittingInAChair) == threadID)){
                            // Grab the customer who waited for a the longest time so they can meet with the librarian.
                            removeTailFromTheLinkedList(&customersSittingInAChair);
                            
                            sem_post(&semFreeChairToSitOn);

                            break;
                        }
                    }
                    else{ // search for information.
                        if (customersLookingForInformation == NULL){
                            customersLookingForInformation = initLinkedList(threadID);
                        }
                        else{
                            addNodeToLinkedList(customersLookingForInformation, threadID);
                        }

                        printf("I`m reader #%d, I`m reading a book.\n", (threadID + 1));
                        
                        while(1){
                            if (grabTailID(customersLookingForInformation) == threadID){
                                sem_wait(&semFreeChairToSitOn); //! check the other location of semFreeChairs
                                removeTailFromTheLinkedList(&customersLookingForInformation);
                                break;
                            }
                        }
                    }
                }
            }
        }

        sem_post(&semFreeCustomers);
        sem_post(&semForEnteringTheLibrary); // Customer left the library so there`s one more room for someone to enter.
        printf("I`m Reader #%d, I`ve finished.\n", (threadID + 1));
        
    }
}

void* mainFunctionForLibrarianThreads(void* threadNumber){
    int threadID = *(int*) threadNumber;

    while(1){
        sem_wait(&semFreeCustomers);
        printf("I`m Librarian #%d, I`m working now.\n", (threadID + 1));
        sem_post(&semFreeLibrarian);
    }
}

Node* initLinkedList(int threadID){
    Node* root = (Node*) malloc(sizeof(Node));

    root->next = NULL;
    root->id = threadID;

    return root;
}

Node* addNodeToLinkedList(Node* root, int threadId){
    Node* newRoot = (Node*) malloc (sizeof(Node));
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

int grabTailID(Node* linkedList){
    Node* root = linkedList;

    while (root->next != NULL){
        root = root->next;
    }

    return root->id;
}