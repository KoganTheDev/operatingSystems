#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

/**
 * @brief Function to be executed by a thread to print messages.
 *
 * This function prints messages from a thread (Thread A) and waits for a semaphore signal 
 * from another thread (Thread B) before printing. It signals the other thread when it's done.
 *
 * @param str A pointer to a string to be printed. This should be a message specific to Thread A.
 * @return NULL This function does not return a value.
 */
void* create_message (void* str );

/** Semaphore for synchronization between threads.
 * 
 * @var semaphoreThreadA
 * @brief Semaphore used to synchronize the printing of messages by Thread A and Thread B.
 * Initialized to 0 at the start, it is signaled by Thread A when it completes printing.
 */
sem_t semaphoreThreadA;

/** Semaphore for synchronization between threads.
 * 
 * @var semaphoreThreadB
 * @brief Semaphore used to control the flow of messages between Thread A and Thread B.
 * Initialized to 1 at the start, it is signaled by Thread B when it completes printing.
 */
sem_t semaphoreThreadB;

int main (){
    pthread_t  thread;
    
    // Initialize semaphores
    if (sem_init(&semaphoreThreadA, 0, 0) != 0) {
        perror("sem_init semaphoreThreadA");
        exit(1);
    }
    if (sem_init(&semaphoreThreadB, 0, 1) != 0) {
        perror("sem_init semaphoreThreadB");
        exit(1);
    }
    
    int i = 0;
    pthread_create (&thread, NULL, create_message, (void*)"Thread A" );
    for ( i = 0; i < 10; i++ ){
        sem_wait(&semaphoreThreadA);
        printf ( "The message #%d was printed. Thread B \n\n", i+1 );
        sem_post(&semaphoreThreadB);
    }
    pthread_join(thread, NULL);

    // Destroy semaphores
    sem_destroy(&semaphoreThreadA);
    sem_destroy(&semaphoreThreadB);
}

void* create_message ( void* str ){
    int i = 0;
    for ( i = 0; i < 10; i++ ){
        sem_wait(&semaphoreThreadB);
        printf ( "I've wrote a message #%d. %s\n", i+1, (char*) str );
        sem_post(&semaphoreThreadA);
    }

}
