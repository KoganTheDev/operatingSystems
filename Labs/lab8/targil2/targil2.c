#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

/**
 * @brief Semaphore to control access to the shared resource (item count).
 * 
 * This semaphore is used to ensure synchronization between Machine A and Machine AA.
 * Machine A produces items and increments the semaphore, while Machine AA consumes 
 * items by decrementing the semaphore.
 */
sem_t semaphoreItem;

/**
 * @brief Function executed by Machine A thread.
 * 
 * This function simulates Machine A producing an item every 2 seconds. It prints 
 * a message indicating an item was produced and then signals the semaphore to 
 * indicate that an item is available.
 * 
 * @param arg A pointer to any arguments. Not used in this function.
 * @return NULL This function does not return a value.
 */
void* machineA(void* arg) {
    while (1) {
        sleep(2); // Produce an item every 2 seconds

        printf("Produced A\n");

        // Release the semaphore if there are items available
        sem_post(&semaphoreItem);
    }
    return NULL;
}

/**
 * @brief Function executed by Machine AA thread.
 * 
 * This function simulates Machine AA collecting items. It waits for two items to be 
 * available (decrements the semaphore twice) and then prints a message indicating 
 * that items have been collected.
 * 
 * @param arg A pointer to any arguments. Not used in this function.
 * @return NULL This function does not return a value.
 */
void* machineAA(void* arg) {
    while (1) {
        // Wait for two items to be available
        sem_wait(&semaphoreItem);
        sem_wait(&semaphoreItem);

        printf("Collected AA\n");
    }

    return NULL;
}

int main() {
    pthread_t threadA, threadAA;

    // Initialize semaphore with value 0 (no items available initially)
    sem_init(&semaphoreItem, 0, 0);
    
    // Create threads for Machine A and Machine AA
    pthread_create(&threadA, NULL, machineA, NULL);
    pthread_create(&threadAA, NULL, machineAA, NULL);
      
    // Let the machines run for 20 seconds
    sleep(20);

    // Clean up semaphore and terminate threads
    sem_destroy(&semaphoreItem);
    pthread_cancel(threadA);
    pthread_cancel(threadAA);

    return 0;
}
