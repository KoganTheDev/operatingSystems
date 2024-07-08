#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> // for sleep

int cpuID; // Global parameter.
int time_has_passed = 0; // Global variable to keep track of elapsed time
int N; // Global variable for the number of threads
long int* counter; // Global array for counters

void* f(void* p); // Declaration

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
