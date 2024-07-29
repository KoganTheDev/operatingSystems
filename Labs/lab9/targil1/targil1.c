/**
 * @file stack_operations.c
 * @brief Implements a stack with thread-safe push and pop operations using semaphores and mutexes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define K 5
#define N 10

int stk[N];
int idx = 0;

// Declaration
void stkPush(int num);
int stkPop();
void* tFunc(void* p);

sem_t waitingToPop;
sem_t waitingToPush;
sem_t idxMutex;

int main(int argc, char* argv[]) {
    pthread_t tArr[K];
    int i, ans[K];

    // Initialize semaphores
    if (sem_init(&waitingToPop, 0, 0) != 0) {
        perror("sem_init waitingToPop\n");
        exit(EXIT_FAILURE);
    }
    if (sem_init(&waitingToPush, 0, N) != 0) {
        perror("sem_init waitingToPush\n");
        exit(EXIT_FAILURE);
    }
    if (sem_init(&idxMutex, 0, 1) != 0) {
        perror("sem_init idxMutex\n");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (i = 0; i < K; i++) {
        ans[i] = pthread_create(&tArr[i], NULL, tFunc, NULL);
        if (ans[i] != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Let the threads run for a while
    sleep(10);

    return 0;
}

/**
 * @brief Thread function where each thread performs random stack operations.
 * 
 * This function generates a random number and either pushes or pops it from the stack
 * based on a random decision. It performs the operation every second.
 * 
 * @param p Pointer to the thread's argument (unused).
 * @return NULL
 */
void* tFunc(void* p) {
    int num;
    while (1) {
        num = rand() % 100;
        if (rand() % 2) {
            stkPush(num);
        } else {
            stkPop();
        }
        sleep(1);
    }
}

/**
 * @brief Pushes a number onto the stack.
 * 
 * Waits for space to be available in the stack, acquires the mutex for safe index 
 * updates, pushes the number if there is space, and signals that a new item is 
 * available in the stack.
 * 
 * @param num The integer number to be pushed onto the stack.
 */
void stkPush(int num) {
    sem_wait(&waitingToPush);
    sem_wait(&idxMutex);
    if (idx < N) { // Stack has space
        stk[idx] = num;
        printf("Pushed %d at index %d\n", num, idx);
        idx++;
    } else {
        printf("Stack is full, cannot push %d\n", num);
    }
    sem_post(&idxMutex);
    sem_post(&waitingToPop);
}

/**
 * @brief Pops a number from the stack.
 * 
 * Waits for an item to be available in the stack, acquires the mutex for safe index 
 * updates, pops the number if the stack is not empty, and signals that space is 
 * available in the stack.
 * 
 * @return The integer number popped from the stack.
 */
int stkPop() {
    sem_wait(&waitingToPop);
    sem_wait(&idxMutex);
    if (idx > 0) { // Stack is not empty
        idx--;
        int num = stk[idx];
        printf("Popped %d from index %d\n", num, idx);
    } else {
        printf("Stack is empty, cannot pop\n");
    }
    sem_post(&idxMutex);
    sem_post(&waitingToPush);
    return 0;
}
