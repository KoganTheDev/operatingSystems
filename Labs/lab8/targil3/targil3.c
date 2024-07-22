#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* A(void* );
void* B(void* );
void* C(void* );

sem_t semAToB, semBToC, semCToA;


int main (int argc, char* argv[]){

    if (argc != 1){
        printf("The program receives no parameters but its name.\n");
    }

    pthread_t threadA, threadB, threadC;

    // Initialize the semaphors.
    if ((sem_init(&semAToB, 0, 0)) == -1){
        printf("Creating the semaphore AToB has failed.\n");
        exit(1);
    }
    if ((sem_init(&semBToC, 0, 0)) == -1){
        printf("Creating the semaphore BToC has failed.\n");
        exit(1);
    }
    if ((sem_init(&semCToA, 0, 2)) == -1){
        printf("Creating the semaphore CToA has failed.\n");
        exit(1);
    }


    // Create the thread and start running the function for each of the threads.
    if (pthread_create(&threadA, NULL, A, NULL) != 0){
        printf("Creating thread 'A' has failed.\n");
        exit(1);
    }
    if (pthread_create(&threadB, NULL, B, NULL) != 0){
        printf("Creating thread 'B' has failed.\n");
        exit(1);
    }
     if (pthread_create(&threadC, NULL, C, NULL) != 0){
        printf("Creating thread 'C' has failed.\n");
        exit(1);
    }

    sleep(5);

    // Destroy the semaphores before exit.
    sem_destroy(&semAToB);
    sem_destroy(&semBToC);
    sem_destroy(&semCToA);

    // Eliminate the threads.
    pthread_cancel(threadA);
    pthread_cancel(threadB);
    pthread_cancel(threadC);
}

void* A(void* ){
    while(1){
        sem_wait(&semCToA);
        printf("A\n");
        sem_post(&semAToB);
    }
}

void* B(void* ){
    while(1){
        sem_wait(&semAToB);
        sem_wait(&semAToB);
        printf("B\n");
        sem_post(&semBToC);
    }
}

void* C(void* ){
    while(1){
        sem_wait(&semBToC);
        printf("C\n");
        sem_post(&semCToA);
        sem_post(&semCToA);
    }
}