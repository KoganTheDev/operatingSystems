#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define K 5
#define N 10

int stk[N]; ///< Stack to store integers.
int idx = 0; ///< Index to keep track of the current position in the stack.

/**
 * @brief Pushes a number onto the stack.
 * 
 * This function waits for the semaphore `waitingToPush` to ensure there is space 
 * in the stack, pushes the provided number onto the stack if space is available,
 * and then signals `waitingToPop` to indicate that a new item is available in the stack.
 * 
 * @param num The integer number to be pushed onto the stack.
 */
void stkPush(int num);

/**
 * @brief Pops a number from the stack.
 * 
 * This function waits for the semaphore `waitingToPop` to ensure there is an item
 * in the stack, pops the number from the stack if it is not empty, and then signals
 * `waitingToPush` to indicate that space is available in the stack.
 * 
 * @return The integer number popped from the stack.
 */
int stkPop();

/**
 * @brief Thread function to perform random stack operations.
 * 
 * This function generates a random number and randomly decides whether to push 
 * or pop the number from the stack. It runs in an infinite loop, performing 
 * operations every second.
 * 
 * @param p Pointer to the thread's argument (unused).
 * @return NULL
 */
void* tFunc(void* p);

sem_t waitingToPop; ///< Semaphore to signal when an item is available in the stack.
sem_t waitingToPush; ///< Semaphore to signal when there is space in the stack.

int main(int argc, char* argv[]) {
    pthread_t tArr[K]; ///< Array of thread identifiers.
    int i, ans; ///< Index and return value for thread creation.

    // Initialize semaphores
    if (sem_init(&waitingToPop, 0, 0) != 0) {
        perror("sem_init waitingToPop");
        exit(EXIT_FAILURE);
    }
    if (sem_init(&waitingToPush, 0, N) != 0) {
        perror("sem_init waitingToPush");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (i = 0; i < K; i++) {
        ans = pthread_create(&tArr[i], NULL, tFunc, NULL);
        if (ans != 0) {
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(ans));
            exit(EXIT_FAILURE);
        }
    }

    // Let the threads run for a while
    sleep(10);

    // Clean up
    for (i = 0; i < K; i++) {
        pthread_cancel(tArr[i]);
        pthread_join(tArr[i], NULL);
    }

    sem_destroy(&waitingToPop);
    sem_destroy(&waitingToPush);

    return 0;
}

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

void stkPush(int num) {
    sem_wait(&waitingToPush);
    if (idx < N) { // Stack has space
        stk[idx] = num;
        printf("Pushed %d at index %d\n", num, idx);
        idx++;
    } else {
        printf("Stack is full, cannot push %d\n", num);
    }
    sem_post(&waitingToPop);
}

int stkPop() {
    sem_wait(&waitingToPop);
    if (idx > 0) { // Stack is not empty
        idx--;
        int num = stk[idx];
        printf("Popped %d from index %d\n", num, idx);
    } else {
        printf("Stack is empty, cannot pop\n");
    }
    sem_post(&waitingToPush);
    return 0;
}
