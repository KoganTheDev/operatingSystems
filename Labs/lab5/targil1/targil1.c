#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10
#define M 30

int Mat[N][M]; // Global matrix in size N rows and M columns.

// Declaration of the functions.
void* fillRandom(void* threadPointer);
void* sumRow(void* threadPointer);

int main(int argc, char* argv[]){

	if (argc != 1){
		printf("ERROR ; please enter 1 parameter");
		exit(1);
	}

	int i, j, k;
	int sidori[N]; 
	pthread_t id[N];
	int result = 0;

	// Create N threads.
	for (i = 0; i < N ; i++){
		sidori[i]=i;
		pthread_create(&id[i], NULL, fillRandom, ((void*) &sidori[i]));
	}

	// Main will wait for all of the threads.
	for (i = 0; i < N; i++) {
    pthread_join(id[i], NULL);
}

	printf("[\n");
	for (j = 0; j < N; j++) {
		printf(" [");
		for (k = 0; k < M; k++) {
			printf("%3d", Mat[j][k]);
			if (k < M - 1) {
				printf(", ");
			}
		}
		printf("]");
		if (j < N - 1) {
			printf(",");
		}
		printf("\n");
	}
	printf("]\n\n");


	// Create N sums so each of them will be able to contain the sum of each row.
	// as well as initialize each sum counter.
	int* rowSum[N];
	*rowSum[i] = 0;

	// Create new N threads.
	for (i = 0; i < N ; i++){
		pthread_create(&id[i], NULL, sumRow, ((void*) &sidori[i]));
	}

	// Main will wait for all of the threads.
	for(i = 0; i < N ; i++){
		pthread_join(id[i],(void**)&rowSum[i]);
	}

	// Sum all of the results from the threads.
	for (i = 0; i < N; i++){
		result += *rowSum[i];
	}

+	printf("The sum of values in the matrix %d.\n", result);


	// Free all of the dinamically allocated pointers.
	for (i = 0; i < N; i++){
		free(rowSum[i]);
	}

	return 0;	
}

void* fillRandom(void* p){
	int rownum = *((int*)p);

	for(int i = 0; i < M ;i++){
		Mat[rownum][i] = rand() % 101;
	}
}

void* sumRow(void* p){
	int rowNum = *((int*)p);

    int *sumSpace = (int*) malloc(sizeof(int));
	if (sumSpace == NULL){
		printf("Error in allocating memory for \"sumSpace\".\n");
		exit(1);
	}

	*sumSpace = 0;
	for (int i = 0; i < M; i++){
		*sumSpace += Mat[rowNum][i];
	}

	return ((void*) sumSpace);
}

