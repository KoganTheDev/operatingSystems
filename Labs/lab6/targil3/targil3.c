#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

int iterations = 5;

void* f(void* p); // Declaration

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("ERROR; no parameters are needed\n");
        exit(1);
    }

    int i;
    int sidori1[3] = {0, 1, 2};
    int sidori2[3] = {0, 1, 2};
    pthread_t id1[3]; // for child number 1
    pthread_t id2[3]; // for child number 2
    pid_t pid1, pid2;

    // First fork
    pid1 = fork();

    if (pid1 < 0) { // Error occurred
        perror("fork");
        exit(1);
    } else if (pid1 == 0) { // First child process     
        // Create threads
        for (i = 0; i < 3; i++) {
            if (pthread_create(&id1[i], NULL, f, (void*)&sidori1[i]) != 0) {
                perror("pthread_create");
                exit(1);
            }
            printf("Creating thread %d in process %d\n", i, getpid());
        } 
        // Join threads
        for (i = 0; i < 3; i++) {
            if (pthread_join(id1[i], NULL) != 0) {
                perror("pthread_join");
                exit(1);
            }
        }
        printf("Child process %d exited with status 0\n", getpid());
        exit(0);
    } else { 
        pid2 = fork();

        if (pid2 < 0) { // Error occurred
            perror("fork");
            exit(1);
        } else if (pid2 == 0) { // Second child process
            for (i = 0; i < 3; i++) {
                if (pthread_create(&id2[i], NULL, f, (void*)&sidori2[i]) != 0) {
                  perror("pthread_create");
                   exit(1);
                }
                printf("Creating thread %d in process %d\n", i, getpid()); 
            }
            // Join threads
            for (i = 0; i < 3; i++) {
                if (pthread_join(id2[i], NULL) != 0) {
                    perror("pthread_join");
                    exit(1);
                }
            }
            printf("Child process %d exited with status 0\n", getpid());
            exit(0);
        } else { // Parent process
            wait(NULL);
            wait(NULL);
        }
    }   

    return 0;
}

void* f(void* p) {
    int mynum = *((int*)p);
    struct timeval t1, t2;
    double elapsedTime;
    pid_t pid = getpid();

    for (int i = 0; i < iterations; i++) {
        gettimeofday(&t1, NULL);
        printf("Thread %d in process %d is running iteration %d (Start time: %ld us)\n", mynum, pid, i, t1.tv_usec);
        usleep(1000); // Sleep for 1 millisecond
 	    gettimeofday(&t2, NULL);

	    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
        printf("Thread %d in process %d is running iteration %d (End time: %ld us, Elapsed time: %lf us)\n", mynum, pid, i, t2.tv_usec, elapsedTime);
    }
	printf("Thread %d in process %d has finished\n", mynum, pid);  

    return NULL;
}