#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

/**
 * @brief Main function to compute Fibonacci numbers using child processes.
 *
 * This function creates child processes using fork() to compute Fibonacci numbers
 * up to a predefined limit. Each child process computes a term in the Fibonacci
 * sequence and the parent process waits for all child processes to complete.
 *
 * @return int Returns 0 on successful execution, -1 on error.
 */
int main(){
	int c1, c2, t, i;
	c2=1;
	c1=0;
	int pid = getpid();

	for(i=1; i<N; i++){
		switch(fork()){
				case -1:
					printf("Error creating process\n");
					return -1;
				case 0:
					t=c2;
					c2=c1+c2;
					c1=t;
					break;
				default:
					i=N;
					break;
		}
	}
	wait(NULL);
	printf("%d ",c2);
	if (pid == getpid()){
	printf("\n");
	}
}
