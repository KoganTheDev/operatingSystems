#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
    
//TODO: Insert code to that`ll allow me to run a linked list.    
typedef struct Node{
    

} Node; 

int isLibraryFull(int customersInLibrary);
// "Main" functions for the customer and librarian thread accordingly. 
void* mainFunctionForCustomerThreads(void* threadIDNumber);
void* mainFunctionForLibrarianThreads(void* threadIDNumber);
// Customer`s functions.
void* enterTheLibrary(void* argument); //TODO: change the name of the argument in all of the functions down here.
void* lookForInformation(void* argument);
void* seatInChairAndRead(void* argument);
void* callTheLibrarian(void* argument);
// Librarian`s functions.
void* helpCustomer(void* argument);
void* librarianSleep(void* argument);

int N = 10;

//TODo: insert semaphors here. sem for sitting in chair, sem for managing librarian&customer support.


int main(int argc,char* argv[]){

    if (argc != 1){
        printf("The program receives no parameters but its name.\n");
        exit(1);
    }

    pthread_t customerThreads[N + 2], librarianThreads[3];
    int threadCheck, i, threadNumber[N + 2];
    
    // Initialiaze the numbers in the array named thread_number.
    for (i = 0; i < N + 2; i++){
        threadNumber[i] = i;
    }

    // Create N+2 threads for the customers.
    for (i = 0; i < (N + 2); i++){
        threadCheck = pthread_create(&customerThreads[i], NULL, mainFunctionForCustomerThreads, &threadNumber[i]);
        if (threadCheck){ // Creating a thread has failed.
            printf("Creating a thread for a customer has failed.\n");
        }
    }

    // Create 3 threads for the librarians.
    for (i = 0; i < 3; i++){
        threadCheck = pthread_create(&librarianThreads[i], NULL, mainFunctionForLibrarianThreads, threadNumber[i]); //TODO: insert the call correctly here.
        if (threadCheck){ // Creating a thread has failed.
            printf("Creating a thread for a librarian has failed.\n");
        }
    }
}


void* mainFunctionForCustomerThreads(void* thread_number){

}

void* mainFunctionForLibrarianThreads(void* thread_number){


}







int isLibraryFull(int customersInLibrary){
    if (customersInLibrary == N){
        return 1;
    }
    return 0;
}

void printThreadNameAndNumber(int threadIDNumber, char* threadName){
    printf("I`m %s #%d, ", threadName, threadIDNumber);
}