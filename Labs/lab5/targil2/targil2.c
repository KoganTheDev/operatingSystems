#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Declaration of the functions
void* increment(void* pThread); 
void* printCounter(void* pThread);

unsigned long int counter = 0;  // Global counter

int main(int argc, char* argv[]){

if (argc != 1){
		printf("ERROR ; please enter 1 parameter");
		exit(1);
	}

int i;
pthread_t id[2];
int sidori[2] = {0, 1}; 

pthread_create(&id[0], NULL, increment, ((void*) &sidori[0]));
pthread_create(&id[1], NULL, printCounter, ((void*) &sidori[1]));

pthread_join(id[0], NULL);
pthread_join(id[1], NULL);

return 0;
}




void* increment(void* pThread){
    while(1){
        counter++;
    }  

    return NULL;
}

void* printCounter(void* pThread){
    while (1){
        printf("%lu\n", counter);
        usleep(100000);
    }

    return NULL;
}