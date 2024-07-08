#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> // for sleep

// Global Variables
int cpuID; // Global parameter representing the current CPU ID.
int time_has_passed = 0; // Global variable to keep track of elapsed time.
int N; // Global variable for the number of threads.
long int* counter; // Global array for counters.

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
 * It initializes an array of thread identifiers, an array of unique values for each thread, and an array for counters.
 * It then creates the specified number of threads plus one extra for managing counter printing, and waits for each to complete.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR; please enter 1 parameter\n");
        exit(1);
    }

    int i;
    N = atoi(argv[1]);
    int* sidori = malloc((N + 1) * sizeof(int));
    pthread_t* id = malloc((N + 1) * sizeof(pthread_t));
    counter = malloc(N * sizeof(long int));

    if (sidori == NULL || id == NULL || counter == NULL) {
        perror("malloc");
        exit(1);
    }

    // Initialize the counter array.
    for (i = 0; i < N; i++) {
        counter[i] = 0;
    }

    // Initialize sidori array with unique values.
    for (i = 0; i < N + 1; i++) {
        sidori[i] = i;
    }

    // Create threads
    for (i = 0; i < N + 1; i++) {
        if (pthread_create(&id[i], NULL, f, (void*)&sidori[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Join threads
    for (i = 0; i < N + 1; i++) {
        if (pthread_join(id[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    free(sidori);
    free(id);
    free(counter);

    return 0;
}

/**
 * @brief Function executed by each thread to increment counters and print them.
 * 
 * @param p Pointer to the unique integer identifier for the thread.
 * @return void* Always returns NULL.
 * 
 * This function differentiates between the extra thread (id == N) and the rest.
 * The extra thread prints the counter values every 2 seconds and stops after 20 seconds.
 * Other threads increment their respective counters as long as the time has not passed 20 seconds.
 */
void* f(void* p) {
    int current_id = *((int*)p);

    if (current_id == N) {
        while (time_has_passed < 20) {
            for (int i = 0; i < N; i++) {
                printf("Counter %d = %li\n", i, counter[i]);
            }
            sleep(2);
            time_has_passed += 2;
        }
    } else {
        while (time_has_passed < 20) {
            counter[current_id]++;
        }
    }

    return NULL;
}
