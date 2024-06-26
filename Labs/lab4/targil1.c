#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main(int argc, char* argv[]) {

    int i, rc, num;

    // Check if the number of command line arguments is correct
    if (argc != 3) {
        fprintf(stderr, "Please enter 3 arguments\n");  // Print error message to standard error
        exit(1);  // Exit the program
    }

    num = atoi(argv[2]);  // Convert third command-line argument to integer

    for (i = 0; i < num; i++) {
        rc = fork();  // Create a new process
        if (rc == -1) {
            fprintf(stderr, "fork error\n");  // Print error message if fork fails
            exit(1);  // Exit the program
        } else if (rc == 0) {
            // Child process
            if ((execl(argv[1], argv[1], NULL)) == -1){  // Execute the program specified by the first argument
                fprintf(stderr, "execl has failed.\n");
                exit(1);
            }
        } else {
            // Parent process
            wait(NULL);  // Wait for the child process to complete
        }
    }

    printf("END\n");  // Print "END" after all child processes have completed
}
