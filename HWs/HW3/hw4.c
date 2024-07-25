#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// Global variables
#define N 10 // Number of customer threads
#define K 4  // Number of chairs in the library waiting area

/**
 * @brief Node structure to store customer information.
 */
typedef struct Node
{
    int id;            // Unique identifier for the customer.
    struct Node *next; // Pointer to the next node in the list.
    struct Node *prev; // Pointer to the previous node in the list.
} Node;

/**
 * @brief Queue structure for managing a list of nodes.
 */
typedef struct Queue
{
    Node *head; // Pointer to the head node of the queue.
    Node *tail; // Pointer to the tail node of the queue.
} Queue;

/**
 * @brief Function prototypes.
 */
void *customerThreadFunction(void *threadIDNumber);
void *librarianThreadFunction(void *threadIDNumber);

/**
 * @brief Creates a new node with a given thread ID.
 * @param threadID The unique identifier for the node.
 * @return A pointer to the newly created node.
 */
Node *createNode(int threadID);

/**
 * @brief Adds a node to the end of a queue.
 * @param queue The queue to which the node will be added.
 * @param nodeToInsert The node to be added to the queue.
 * @return The updated queue with the new node added.
 */
Queue *enqueue(Queue *queue, Node *nodeToInsert);

/**
 * @brief Removes a node from the end of a queue.
 * @param queue The queue from which the node will be removed.
 * @return The thread ID of the removed node, or -1 if the queue was empty.
 */

int dequeue(Queue *queue);

// Semaphores for synchronization
sem_t entrance;                     // Semaphore to manage the number of customers allowed in the library.
sem_t availableLibrarians;          // Semaphore to manage the availability of librarians.
sem_t availableCouch;               // Semaphore to manage the availability of couches.
sem_t customersWaitingForLibraians; // Semaphore to manage the number of customers waiting for librarians.

// Queue mutex.
sem_t entranceQueueMutex;              // Mutex for handling access to the list of chairs
sem_t couchQueueMutex;                 // Mutex for handling access to the list of people looking for information
sem_t lookingForInformationQueueMutex; // Mutex for controlling print statements

// Global queues (Bidirectional LinkedLists).
Queue *entranceQueue;              // Queue for managing customers waiting to enter the library.
Queue *couchQueue;                 // Queue for managing customers waiting for a couch.
Queue *lookingForInformationQueue; // Queue for managing customers looking for information.

int placeLeftInLibrary; // Stores how much place is left in the library;

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("The program receives no parameters but its name.\n");
        exit(1);
    }

    pthread_t customerThreads[N + 2], librarianThreads[3];
    int threadCheck, i, threadNumber[N + 2];

    // Initialize the semaphores.
    sem_init(&entrance, 0, N);                     // Library can hold N customers
    sem_init(&availableLibrarians, 0, 3);          // Initially there are 3 free librarians
    sem_init(&customersWaitingForLibraians, 0, 0); // mutually locks with available librarians.
    sem_init(&availableCouch, 0, K);               // Stores the amount the couches people can sit on.
    // The next mutex are used to allow secure access to each one of the queue.
    sem_init(&entranceQueueMutex, 0, 1);
    sem_init(&couchQueueMutex, 0, 1);
    sem_init(&lookingForInformationQueueMutex, 0, 1);

    // Initialize Queue for the customer function.
    entranceQueue = (Queue *)malloc(sizeof(Queue));
    if (entranceQueue == NULL)
    {
        printf("Memory allocation has failed when trying to allocate memory for \"&entranceQueue\".\n");
        exit(EXIT_FAILURE);
    }
    couchQueue = (Queue *)malloc(sizeof(Queue));
    if (couchQueue == NULL)
    {
        printf("Memory allocation has failed when trying to allocate memory for \"&couchQueue\".\n");
        exit(EXIT_FAILURE);
    }
    lookingForInformationQueue = (Queue *)malloc(sizeof(Queue));
    if (lookingForInformationQueue == NULL)
    {
        printf("Memory allocation has failed when trying to allocate memory for \"&lookingForInformationQueue\".\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the numbers in the array named threadNumber.
    for (i = 0; i < N + 2; i++)
    {
        threadNumber[i] = i;
    }

    // Create N+2 threads for the customers.
    for (i = 0; i < (N + 2); i++)
    {
        threadCheck = pthread_create(&customerThreads[i], NULL, customerThreadFunction, (void *)&threadNumber[i]);
        if (threadCheck)
        { // Creating a thread has failed.
            printf("Creating a thread for a customer has failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Create 3 threads for the librarians.
    for (i = 0; i < 3; i++)
    {
        threadCheck = pthread_create(&librarianThreads[i], NULL, librarianThreadFunction, (void *)&threadNumber[i]);
        if (threadCheck)
        { // Creating a thread has failed.
            printf("Creating a thread for a librarian has failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Join the threads
    for (i = 0; i < 3; i++)
    {
        pthread_join(librarianThreads[i], NULL);
    }
    for (i = 0; i < (N + 2); i++)
    {
        pthread_join(customerThreads[i], NULL);
    }

    // Destroy the semaphores.
    sem_destroy(&entrance);                        // Library can hold N customers.
    sem_destroy(&availableLibrarians);             // Initially there are 3 free librarians.
    sem_destroy(&availableCouch);                  // Mutex to manage customers waiting for librarians.
    sem_destroy(&customersWaitingForLibraians);    // Number of available couches.
    sem_destroy(&entranceQueueMutex);              // Mutex for entrance queue access.
    sem_destroy(&couchQueueMutex);                 // Mutex for couch queue access
    sem_destroy(&lookingForInformationQueueMutex); // Mutex for information queue access.

    free(entranceQueue);
    free(couchQueue);
    free(lookingForInformationQueue);

    return 0;
}

void *customerThreadFunction(void *threadIDNumber)
{
    // Create the node of the thread.
    Node *threadNode = createNode(*(int *)threadIDNumber + 1);
    while (1)
    {
        sem_wait(&entranceQueueMutex); // Allow access to the &entrance queue.
        enqueue(entranceQueue, threadNode);
        sem_getvalue(&entrance, &placeLeftInLibrary); // Check how much room is left in thte library.
        if (placeLeftInLibrary == 0)
        { // Meaning there`s no more toom to enter.
            printf("I'm Reader #%d, I'm out of library\n", threadNode->id);
        }
        sem_post(&entranceQueueMutex); // Allow another thread to access the queue.
        while (entranceQueue->tail->id != threadNode->id)
        {
        }
        sem_wait(&entrance);           // Update the amount of customers who entered the library.
        sem_wait(&entranceQueueMutex); // Allow access to the &entrance to the library queue.
        dequeue(entranceQueue);        // dequeue the tail of the list.
        sem_post(&entranceQueueMutex); // Allow another thread to access the &entrance queue.
        sem_wait(&couchQueueMutex);    // Allow access to the couch queue.
        enqueue(couchQueue, threadNode);
        sem_post(&couchQueueMutex); // Allow another thread to access the couch queue.
        printf("I'm Reader #%d, I got into the library\n", threadNode->id);
        while (couchQueue->tail->id != threadNode->id)
        {
        }
        sem_wait(&availableCouch);                  // Update the amount of couches available to customers.
        sem_wait(&couchQueueMutex);                 // Allow access to the couch queue.
        dequeue(couchQueue);                        // Emit the tail from the couch queue.
        sem_post(&couchQueueMutex);                 // Reallow access to the couch queue.
        sem_wait(&lookingForInformationQueueMutex); // Start looking for information.
        enqueue(lookingForInformationQueue, threadNode);
        sem_post(&lookingForInformationQueueMutex); // Reallow access to the queue.
        printf("I'm Reader #%d, I'm reading a book\n", threadNode->id);
        while (lookingForInformationQueue->tail->id != threadNode->id)
        {
        }
        sem_wait(&availableLibrarians);             // Update the amount of available librarians.
        sem_wait(&lookingForInformationQueueMutex); // Allow access to the queue of people lookign for information.
        dequeue(lookingForInformationQueue);
        sem_post(&lookingForInformationQueueMutex); // Reallow access.
        sem_post(&availableCouch);
        sem_post(&customersWaitingForLibraians);
        printf("I'm Reader #%d, I'm speaking with a librarian\n", threadNode->id);
        printf("I'm Reader #%d, I've finished\n", threadNode->id);

        sem_post(&entrance); // Exit the library.
    }

    return NULL;
}

void *librarianThreadFunction(void *threadIDNumber)
{
    int threadID = *(int *)threadIDNumber;

    while (1)
    {
        sem_wait(&customersWaitingForLibraians); // Help a customer.
        printf("I'm Librarian #%d, I'm working now.\n", threadID + 1);
        sleep(8);                       // Simulate time spent helping the customer.
        sem_post(&availableLibrarians); // Indicate librarian is available.
    }

    return NULL;
}

Node *createNode(int threadID)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    { // memory allocation error check.
        printf("Memory allocation has failed when trying to allocate memory for \"createNode\".\n");
        exit(EXIT_FAILURE);
    }

    node->id = threadID;

    node->next = NULL;
    node->prev = NULL;
    return node;
}

Queue *enqueue(Queue *queue, Node *nodeToInsert)
{
    // If the queue is empty, add the first customer to come and return the queue.
    if (queue->head == NULL)
    { // meaning the queue is empty.
        queue->head = nodeToInsert;
        queue->tail = nodeToInsert;

        return queue;
    }

    // Otherwise add the new customer to the head.
    queue->head->prev = nodeToInsert; // put the new node before the "head" node.
    nodeToInsert->next = queue->head; // put the next pointer of the new head to what was beforehand the head of the queue.
    queue->head = nodeToInsert;       // Update the head of the queue to be the new node that was inserted.

    return queue;
}

int dequeue(Queue *queue)
{
    Node *node = queue->tail;

    // If the queue is empty, -1 can indicate that since the threadIDs start from zero onwards.
    if (node == NULL)
    {
        return -1;
    }

    int threadID = node->id;

    // Special case: The queue has only one node, therefore update the head and tail to be null.
    if (node->prev == NULL)
    {
        queue->tail = NULL;
        queue->head = NULL;
        return threadID;
    }

    // Update the queue.
    queue->tail = node->prev;
    queue->tail->next == NULL;

    return threadID;
}
