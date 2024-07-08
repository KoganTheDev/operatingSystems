#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int cpuID; // Global parameter.

void* f(void* p); // declaration

int main(int argc, char* argv[]){

if (argc != 2) {
	printf("ERROR; please enter 1 parameter\n");
	exit(1);
}

int i;
int N = atoi(argv[1]);
int sidori[N];
pthread_t id[N];

    // Initialize sidori array with unique values
    for (i = 0; i < N; i++) {
        sidori[i] = i;
    }

for (i = 0; i < N; i++) {
	if (pthread_create(&id[i], NULL, f, (void*)&sidori[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
}

for (i = 0; i < N; i++) {
	if (pthread_join(id[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
	}
}

return 0;
}

void* f(void* p) {
	int mynum = *((int*)p);
	struct timeval t1, t2;
	double elapsedTime;

	while (1) {
		cpuID = mynum;
		gettimeofday(&t1, NULL);
		while (mynum == cpuID) {
			gettimeofday(&t2, NULL);
		}
		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
		printf("Time slice for thread %d = %lf ms\n", cpuID, elapsedTime);
	}

	return NULL;
}


















