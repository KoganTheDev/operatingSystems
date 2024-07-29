#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* watchMovie(void* p);
void enterRoom();
void leaveRoom();

#define peopleAllowedInOneRoom 5 // Maximum people per movie hall.
#define N 5 // Number of movie halls.
#define amountOfThreads 20 // Number of threads.

int occupiedMovieHalls = 0; // Number of occupied movie halls.
int peopleInOneMovieRoom = 0; // Number of people currently in the room.
int hallNumber = 1; // Current movie hall number.

sem_t wantToSeeMovie; // Semaphore to control entry into the movie hall.
sem_t hallNumberMutex; // Semaphore for managing hall number access.
sem_t peopleInOneMovieRoomMutex; // Semaphore for managing room occupancy.

int main(int argc, char* argv[]) {
    pthread_t threads[amountOfThreads];
    int threadID[amountOfThreads], i;
    int threadCheck;

    sem_init(&wantToSeeMovie, 0, 0); // Start with 0, as people need to wait for a room.
    sem_init(&hallNumberMutex, 0, 1);
    sem_init(&peopleInOneMovieRoomMutex, 0, 1);

    // Create thread ID numbers.
    for (i = 0; i < amountOfThreads; i++) {
        threadID[i] = i;
    }

    // Create threads.
    for (i = 0; i < amountOfThreads; i++) {
        threadCheck = pthread_create(&threads[i], NULL, &watchMovie, (void*)&threadID[i]);
        if (threadCheck != 0) {
            fprintf(stderr, "Creating thread %d has failed.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Join threads.
    for (i = 0; i < amountOfThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores.
    sem_destroy(&wantToSeeMovie);
    sem_destroy(&hallNumberMutex);
    sem_destroy(&peopleInOneMovieRoomMutex);

    return 0;
}

void* watchMovie(void* p) {
    int threadID = *(int*)p;
    printf("Person %d wants to watch movie\n", threadID);

    while (1) {
        // Try to enter a room if there is space.
        enterRoom();

        sem_wait(&wantToSeeMovie);

        sem_wait(&peopleInOneMovieRoomMutex);
        peopleInOneMovieRoom++;
        if (peopleInOneMovieRoom == peopleAllowedInOneRoom) {
            leaveRoom(); // Room is full, move to the next hall.
        }
        sem_post(&peopleInOneMovieRoomMutex);

        printf("Person %d watching movie in room %d\n", threadID, hallNumber);
        sleep(2);
        printf("Person %d END watch movie\n", threadID);
    }

    return NULL;
}

void enterRoom() {
    sem_wait(&peopleInOneMovieRoomMutex);
    if (peopleInOneMovieRoom == 0 && occupiedMovieHalls < N) {
        occupiedMovieHalls++;
        sem_post(&wantToSeeMovie);
    }
    sem_post(&peopleInOneMovieRoomMutex);
}

void leaveRoom() {
    sem_wait(&hallNumberMutex);
    hallNumber++;
    if (hallNumber > N) {
        hallNumber = 1;
    }
    peopleInOneMovieRoom = 0;
    sem_post(&hallNumberMutex);

    // Signal that two more people can enter.
    sem_post(&wantToSeeMovie);
    sem_post(&wantToSeeMovie);
}
