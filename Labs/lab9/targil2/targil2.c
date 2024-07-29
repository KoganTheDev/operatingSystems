#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* watchMovie(void* p);
void isTheaterFull();
void isRoomFull();

#define peopleAllowedInOneRoom 5 // Represents how many people can enter into a movie hall at once.
#define N 5 // Represents the movie halls.
#define amountOfThreads 20 // Represents the amount of threads.

int occupiedMovieHalls = 0;
int peopleInOneMovieRoom = 0;
int hallNumber = 1;

sem_t wantToSeeMovie;
sem_t hallNumberMutex;
sem_t peopleInOneMovieRoomMutex;

int main(int argc, char* argv[]){
    pthread_t threads[amountOfThreads];
    int threadID[amountOfThreads], i;
    int threadCheck;

    sem_init(&wantToSeeMovie, 0, 2);
    sem_init(&hallNumberMutex, 0, 1);
    sem_init(&peopleInOneMovieRoomMutex, 0, 1);

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

    // join the threads and end the main thread.
    for (i = 0; i < amountOfThreads; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&wantToSeeMovie); 
    sem_destroy(&hallNumberMutex);
    sem_destroy(&peopleInOneMovieRoomMutex);

    return 0;
}


void* watchMovie(void* p){
    int threadID = *(int*) p;
    printf("Person %d wants to watch movie\n", threadID);

    while (1){
        
        // try to enter - only when there`s an empty room and 2 poeple, allow entrance.
        if (peopleInOneMovieRoom < 2){
            sem_wait(&peopleInOneMovieRoomMutex);
            peopleInOneMovieRoom++;
            sem_post(&peopleInOneMovieRoomMutex);
        }
        else{
            continue;
        }
        
        sem_wait(&wantToSeeMovie);

        sem_wait(&peopleInOneMovieRoomMutex);
        peopleInOneMovieRoom++;

        isTheaterFull(); // If the theater is full try to get into the first room.
        isRoomFull();

        sem_post(&peopleInOneMovieRoomMutex);

        printf("Person %d watch movie in room %d\n", threadID, hallNumber);
        sleep(2);
        printf("Person %d END watch movie\n", threadID);

    }
}

void isTheaterFull(){
    // Room is full and there`s no more place in the last room.
    if (hallNumber == N && (peopleInOneMovieRoom == peopleAllowedInOneRoom)){
        sem_wait(&hallNumberMutex);
        hallNumber = 1;
        peopleInOneMovieRoom = 0;
        sem_post(&hallNumberMutex);
    }

    return NULL;
}

void isRoomFull(){
    if (peopleInOneMovieRoom == peopleAllowedInOneRoom){
        peopleInOneMovieRoom = 0;
        hallNumber++;

        // Make 2 people wait, so they can get inside together.
        sem_post(&wantToSeeMovie);
        sem_post(&wantToSeeMovie);
    }
}