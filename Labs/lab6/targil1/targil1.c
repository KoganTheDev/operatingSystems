#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Global Variables
int cpuID; // Global parameter representing the current CPU ID.

// Function Declarations
void* f(void* p);

/**
 * @brief The main function that initializes threads and waits for them to complete.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 0 on successful completion.
 * 
 * This function expects exactly one command-line argument, which is the number of threads to create.
 * It initializes an array of thread identifiers and an array of unique values for each thread.
 * It then creates the specified number of threads and waits for each to complete.
 */
int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("ERROR; please enter 1 parameter\n");
        exit(1);
    }

    int i;
    int N = atoi(argv[1]);
    int sidori[N];
    pthread_t id[N];

    // Initialize sidori array with unique values.
    for (i = 0; i < N; i++) {
        sidori[i] = i;
    }

    // Create threads.
    for (i = 0; i < N; i++) {
        if (pthread_create(&id[i], NULL, f, (void*)&sidori[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Join threads.
    for (i = 0; i < N; i++) {
        if (pthread_join(id[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return 0;
}

/**
 * @brief Function executed by each thread to measure and print time slices.
 * 
 * @param p Pointer to the unique integer identifier for the thread.
 * @return void* Always returns NULL.
 * 
 * This function repeatedly sets the global cpuID to the thread's identifier,
 * measures the elapsed time while the thread maintains control, and prints the elapsed time.
 */
void* f(void* p) {
    int mynum = *((int*)p);
    struct timeval t1, t2;
    double elapsedTime;

    while (1) {
        cpuID = mynum;
        gettimeofday(&t1, NULL);
        while (mynum == cpuID) {
            gettimeofday(&t2, NULL);
        }
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
        printf("Time slice for thread %d = %lf ms\n", cpuID, elapsedTime);
    }

    return NULL;
}