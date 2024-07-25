#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// Used to store customer`s information.
typedef struct Node {
    int id;
    struct Node* next;
    struct Node* prev;
} Node;

// A manager`s structure to handle a queue.
typedef struct Queue{
    Node* head;
    Node* tail;
}Queue;

// Function prototypes
void* customerThreadFunction(void* threadIDNumber);
void* librarianThreadFunction(void* threadIDNumber);

// Linked List functions
Node* createNode(int threadID);
Queue* enqueue(Queue* queue, Node* nodeToInsert);
int dequeue(Queue* queue);


// Global variables
int N = 10; // Number of customer threads
int K = 4;  // Number of chairs in the library waiting area

// Global queues (Bidirectional LinkedLists).
Queue* entranceQueue;
Queue* couchQueue;
Queue* lookingForInformationQueue;

int placeLeftInLibrary; // Stores how much place is left in the library;

// Semaphores for synchronization
sem_t entrance;           
sem_t availableLibrarians;    
sem_t availableCouch;
sem_t customersWaitingForLibraians;              

// Queue mutex.
sem_t entranceQueueMutex;           // Mutex for handling access to the list of chairs
sem_t couchQueueMutex;             // Mutex for handling access to the list of people looking for information
sem_t lookingForInformationQueueMutex;                // Mutex for controlling print statements


int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("The program receives no parameters but its name.\n");
        exit(1);
    }

    pthread_t customerThreads[N + 2], librarianThreads[3];
    int threadCheck, i, threadNumber[N + 2];

    // Initialize the semaphores.
    sem_init(&entrance, 0, N);  // Library can hold N customers
    sem_init(&availableLibrarians, 0, 3); // Initially there are 3 free librarians
    sem_init(&customersWaitingForLibraians, 0, 0); // mutually locks with available librarians.
    sem_init(&availableCouch, 0, K); // Stores the amount the couches people can sit on.
    // The next mutex are used to allow secure access to each one of the queue.
    sem_init(&entranceQueueMutex, 0, 1); 
    sem_init(&couchQueueMutex, 0, 1);
    sem_init(&lookingForInformationQueueMutex, 0, 1);


     // Initialize Queue for the customer function.
    entranceQueue = (Queue*)malloc(sizeof(Queue));
    if(entranceQueue == NULL){
        printf("Memory allocation has failed when trying to allocate memory for \"&entranceQueue\".\n");
        exit(EXIT_FAILURE);
    }
    couchQueue = (Queue*)malloc(sizeof(Queue));
    if(couchQueue == NULL){
        printf("Memory allocation has failed when trying to allocate memory for \"&couchQueue\".\n");
        exit(EXIT_FAILURE);
    }
    lookingForInformationQueue = (Queue*)malloc(sizeof(Queue));
    if(lookingForInformationQueue == NULL){
        printf("Memory allocation has failed when trying to allocate memory for \"&lookingForInformationQueue\".\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the numbers in the array named threadNumber.
    for (i = 0; i < N + 2; i++) {
        threadNumber[i] = i;
    }

    // Create N+2 threads for the customers.
    for (i = 0; i < (N + 2); i++) {
        threadCheck = pthread_create(&customerThreads[i], NULL, customerThreadFunction, (void*)&threadNumber[i]);
        if (threadCheck) { // Creating a thread has failed.
            printf("Creating a thread for a customer has failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Create 3 threads for the librarians.
    for (i = 0; i < 3; i++) {
        threadCheck = pthread_create(&librarianThreads[i], NULL, librarianThreadFunction, (void*)&threadNumber[i]);
        if (threadCheck) { // Creating a thread has failed.
            printf("Creating a thread for a librarian has failed.\n");
            exit(EXIT_FAILURE);
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
    sem_destroy(&entrance);
    sem_destroy(&availableLibrarians);
    sem_destroy(&availableCouch);
    sem_destroy(&customersWaitingForLibraians);
    sem_destroy(&entranceQueueMutex);
    sem_destroy(&couchQueueMutex);
    sem_destroy(&lookingForInformationQueueMutex);

    free(entranceQueue);
    free(couchQueue);
    free(lookingForInformationQueue);

    return 0;
}

void* customerThreadFunction(void* threadIDNumber) {
    // Create the node of the thread.
    Node* threadNode = createNode(*(int*)threadIDNumber + 1);
    while (1) {
            sem_wait(&entranceQueueMutex); // Allow access to the &entrance queue.
            enqueue(entranceQueue, threadNode);
            sem_getvalue(&entrance, &placeLeftInLibrary); // Check how much room is left in thte library.
            if (placeLeftInLibrary == 0){ // Meaning there`s no more toom to enter.
                printf("I'm Reader #%d, I'm out of library\n", threadNode->id);
            }
            sem_post(&entranceQueueMutex); // Allow another thread to access the queue.
            sleep(1);

            while (entranceQueue->tail->id != threadNode->id){}
                sem_wait(&entrance); // Update the amount of customers who entered the library.
                sem_wait(&entranceQueueMutex); // Allow access to the &entrance to the library queue.
                dequeue(entranceQueue); // dequeue the tail of the list.
                sem_post(&entranceQueueMutex); // Allow another thread to access the &entrance queue.
                sem_wait(&couchQueueMutex); // Allow access to the couch queue.
                enqueue(couchQueue, threadNode);
                sem_post(&couchQueueMutex); // Allow another thread to access the couch queue.
                printf("I'm Reader #%d, I got into the library\n", threadNode->id);
                sleep(1);
            while(couchQueue->tail->id != threadNode->id){}
                sem_wait(&availableCouch); // Update the amount of couches available to customers.
                sem_wait(&couchQueueMutex); // Allow access to the couch queue.
                dequeue(couchQueue); // Emit the tail from the couch queue.
                sem_post(&couchQueueMutex); // Reallow access to the couch queue.
                sem_wait(&lookingForInformationQueueMutex); // Start looking for information.
                enqueue(lookingForInformationQueue, threadNode);
                sem_post(&lookingForInformationQueueMutex); // Reallow access to the queue.
                printf("I'm Reader #%d, I'm reading a book\n", threadNode->id);
                sleep(1);
            while(lookingForInformationQueue->tail->id != threadNode->id){}
                sem_wait(&availableLibrarians);  // Update the amount of available librarians.
                sem_wait(&lookingForInformationQueueMutex); // Allow access to the queue of people lookign for information.
                dequeue(lookingForInformationQueue);
                sem_post(&lookingForInformationQueueMutex); // Reallow access.
                sem_post(&availableCouch);
                sem_post(&customersWaitingForLibraians);
                printf("I'm Reader #%d, I'm speaking with a librarian\n", threadNode->id);
                sleep(1);
                printf("I'm Reader #%d, I've finished\n", threadNode->id);
                sleep(1);
                sem_post(&entrance); // Exit the library.
            }
            
    return NULL;
}

void* librarianThreadFunction(void* threadIDNumber) {
    int threadID = *(int*)threadIDNumber;

    while (1) {
        sem_wait(&customersWaitingForLibraians); // Help a customer.
        printf("I'm Librarian #%d, I'm working now.\n", threadID + 1);
        sleep(1);
        sem_post(&availableLibrarians); // Note the librarian finished working with the customer.
    }

    return NULL;
}

Node* createNode(int threadID) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL){ // memory allocation error check.
        printf("Memory allocation has failed when trying to allocate memory for \"createNode\".\n");
        exit(EXIT_FAILURE);
    }

    node->id = threadID;

    node->next = NULL;
    node->prev = NULL;
    return node;
}

Queue* enqueue(Queue* queue, Node* nodeToInsert){
    // If the queue is empty, add the first customer to come and return the queue.
    if (queue->head == NULL){ // meaning the queue is empty.
        queue->head = nodeToInsert;
        queue->tail = nodeToInsert;

        return queue;
    }

    // Otherwise add the new customer to the head.
    queue->head->prev = nodeToInsert; // put the new node before the "head" node.
    nodeToInsert->next = queue->head; // put the next pointer of the new head to what was beforehand the head of the queue.
    queue->head = nodeToInsert; // Update the head of the queue to be the new node that was inserted.

    return queue;
}


int dequeue(Queue* queue){
    Node* node = queue->tail;

    // If the queue is empty, -1 can indicate that since the threadIDs start from zero onwards.
    if (node == NULL){
        return -1;
    }

    int threadID = node->id;
    
    // Special case: The queue has only one node, therefore update the head and tail to be null.
    if (node->prev == NULL){
        queue->tail = NULL;
        queue->head = NULL;
        return threadID;
    }

    // Update the queue.
    queue->tail = node->prev;
    queue->tail->next == NULL;

    return threadID;
}
