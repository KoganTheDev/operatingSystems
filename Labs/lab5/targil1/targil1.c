#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10
#define M 30

int Mat[N][M]; // Global matrix in size N rows and M columns.

// Declaration of the functions.
void* random(void* threadPointer);
void* rowSum(void* threadPointer);

int main(int argc, char* argv[]){

	if (argc != 1){
		printf("ERROR ; please enter 1 parameter");
		exit(1);
	}

	int i, j, k;
	int sidori[N]; 
	pthread_t id[N];

	// Create N threads.
	for (i = 0; i < N ; i++){
		sidori[i]=i;
		pthread_create(&id[i], NULL, random, ((void*) &sidori[i]));
	}

	// Main will wait for all of the threads.
	for(i = 0; i < N ; i++){
		pthread_join(id[i],NULL);
	}

	printf("[");
	for(j = 0; j < N; j++){
		for(k = 0; k < M; k++){
			if (k == M - 1){
				printf("%d]", Mat[j][k]);
			}
			else{
				printf("%d, ", Mat[j][k]);
			}
		}
		printf("\n");
	}

	// Create N sums so each will be able to contain the sum of each row.
	// as well as initialize each sum counter.
	int* rowSum[N];
/*
	for (i = 0; i < N; i++){
		rowSum[i] = malloc(sizeof(int));
		*rowSum[i] = 0;
	}
*/
	// Create new N threads.
	for (i = 0; i < N ; i++){
		pthread_create(&id[i], NULL, sumRow, ((void*) &sidori[i]));
	}

	// Main will wait for all of the threads.
	for(i = 0; i < N ; i++){
		pthread_join(id[i],(void**)&rowSum[i]);
	}


	// Free all of the dinamically allocated pointers.
	for (i = 0; i < N; i++){
		free(rowSum[i]);
	}

	return 0;	
}

void* random(void* p){
	int rownum = *((int*)p);

	for(int i = 0; i < M ;i++){
		Mat[rownum][i] = rand() % 101;
	}

	return NULL;
}

void* sumRow(void* p){
	int rowNum = *((int*)p);

    int *sumSpace = (int*) malloc(sizeof(int));
	*sumSpace=0;
	for (int i = 0; i < M; i++){
		*sumSpace += Mat[rowNum][i];
	}

	printf("The sum of values in row %d is %d.\n", rowNum, *rowSum[rowNum]);
	return ((void*) sumSpace);
}

