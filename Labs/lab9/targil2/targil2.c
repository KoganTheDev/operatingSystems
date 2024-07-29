/**
 * @file movie_theater.c
 * @brief Simulates a movie theater with multiple rooms and concurrent threads
 *        representing people watching movies. Uses semaphores for synchronization.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/**
 * @brief Thread function to simulate a person watching a movie.
 * 
 * @param p Pointer to the thread ID.
 * @return Pointer to the result (NULL in this case).
 */
void* watchMovie(void* p);

/**
 * @brief Checks if the theater is full and resets room occupancy if necessary.
 */
void isTheaterFull();

/**
 * @brief Checks if the current movie room is full and moves to the next room if necessary.
 */
void isRoomFull();

/**
 * @brief Maximum number of people allowed in one movie room at once.
 */
#define peopleAllowedInOneRoom 5

/**
 * @brief Number of movie halls available.
 */
#define N 5

/**
 * @brief Total number of threads (people) in the simulation.
 */
#define amountOfThreads 20

/**
 * @brief Global variable tracking the number of occupied movie halls.
 */
int occupiedMovieHalls = 0;

/**
 * @brief Global variable tracking the number of people currently in one movie room.
 *        Initialized to -1 to handle initial conditions.
 */
int peopleInOneMovieRoom = -1;

/**
 * @brief Global variable representing the current movie hall number.
 *        Starts with 1.
 */
int hallNumber = 1;

/**
 * @brief Global flag indicating the number of people waiting to enter the movie theater.
 */
int entranceFlag = 0;

/**
 * @brief Semaphore to control access to the movie theater.
 */
sem_t wantToSeeMovie;

/**
 * @brief Semaphore to protect access to the hallNumber variable.
 */
sem_t hallNumberMutex;

/**
 * @brief Semaphore to protect access to the peopleInOneMovieRoom variable.
 */
sem_t peopleInOneMovieRoomMutex;

/**
 * @brief Semaphore to protect access to the entranceFlag variable.
 */
sem_t entranceFlagMutex;

/**
 * @brief Main function to initialize semaphores, create threads, and manage their execution.
 * 
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit status (0 on success).
 */
int main(int argc, char* argv[]){
    pthread_t threads[amountOfThreads];
    int threadID[amountOfThreads], i;
    int threadCheck;

    // Initialize semaphores
    sem_init(&wantToSeeMovie, 0, 0);
    sem_init(&hallNumberMutex, 0, 1);
    sem_init(&peopleInOneMovieRoomMutex, 0, 1);
    sem_init(&entranceFlagMutex, 0, 1);

    // Create id number for each thread.
    for (i = 0; i < amountOfThreads; i++){
        threadID[i] = i;
    }

    // Create the threads and send them to the functions.
    for (i = 0; i < amountOfThreads; i++){
        threadCheck = pthread_create(&threads[i], NULL, &watchMovie, (void*) &threadID[i]);
        if (threadCheck != 0){
            printf("Creating thread %d has failed.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Join the threads and end the main thread.
    for (i = 0; i < amountOfThreads; i++){
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&wantToSeeMovie); 
    sem_destroy(&hallNumberMutex);
    sem_destroy(&peopleInOneMovieRoomMutex);
    sem_destroy(&entranceFlagMutex);

    return 0;
}

/**
 * @brief Thread function where each thread simulates a person watching a movie.
 *        Controls the entrance to the movie theater and manages room occupancy.
 * 
 * @param p Pointer to the thread ID.
 * @return Pointer to the result (NULL in this case).
 */
void* watchMovie(void* p){
    int threadID = *(int*) p;
    printf("Person %d wants to watch movie\n", threadID);

    while (1){
        sem_wait(&entranceFlagMutex);
        // Try to enter - only when there's an empty room and 1 person, allow entrance.
        if (entranceFlag == 1){
            // Allow 5 threads to enter the movie theater.
            sem_post(&wantToSeeMovie);
            sem_post(&wantToSeeMovie);
            sem_post(&wantToSeeMovie);
            sem_post(&wantToSeeMovie);
            sem_post(&wantToSeeMovie);
        }
        if (entranceFlag < 1){
            entranceFlag++;
        }
        sem_post(&entranceFlagMutex);

        sem_wait(&wantToSeeMovie);

        sem_wait(&peopleInOneMovieRoomMutex);
        
        peopleInOneMovieRoom++; 

        isTheaterFull(); // If the theater is full, try to get into the first room.
        isRoomFull();   // If the room is full, move onwards to the next empty room.

        printf("Person %d watch movie in room %d\n", threadID, hallNumber);
        sem_post(&peopleInOneMovieRoomMutex);

        sleep(2);
        printf("Person %d END watch movie\n", threadID);
    }
}

/**
 * @brief Checks if the entire theater is full and resets the movie hall if necessary.
 */
void isTheaterFull(){
    // Room is full and there's no more place in the last room.
    if (hallNumber == N && (peopleInOneMovieRoom == peopleAllowedInOneRoom)){
        sem_wait(&hallNumberMutex);
        hallNumber = 1;
        peopleInOneMovieRoom = 0;
        sem_post(&hallNumberMutex);
        sem_wait(&entranceFlagMutex);
        entranceFlag = 0;
        sem_post(&entranceFlagMutex);
    }
}

/**
 * @brief Checks if the current movie room is full and moves to the next room if necessary.
 */
void isRoomFull(){
    if (peopleInOneMovieRoom == peopleAllowedInOneRoom){
        peopleInOneMovieRoom = 0;
        hallNumber++;
        sem_wait(&entranceFlagMutex);
        entranceFlag = 0;
        sem_post(&entranceFlagMutex);
    }
}
