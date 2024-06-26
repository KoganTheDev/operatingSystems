#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void createBinaryTree(int depth, int currentDepth);

int main(int argc, char* argv[]) {
    // Check if there are any arguments passed to the program
    if (argc != 2) {
        fprintf(stderr, "ERROR: Invalid arguments\n");
        exit(1);
    }

    int depth = atoi(argv[1]);

    // Validate the input depth
    if (depth <= 0) {
        fprintf(stderr, "ERROR: Depth must be a positive integer\n");
        exit(1);
    }

    pid_t rootPID = getpid();
    printf("Parent PID: %d\n", rootPID);

    // Start creating the binary tree recursively
    createBinaryTree(depth, 1);

    return 0;
}

void createBinaryTree(int depth, int currentDepth) {
    if (currentDepth > depth) {
        return;
    }

    pid_t leftChild, rightChild;

    // Create left child process
    leftChild = fork();
    if (leftChild == -1) {
        fprintf(stderr, "ERROR: Fork failed\n");
        exit(1);
    } else if (leftChild == 0) {
        printf("Left child: Process PID: %d, Parent PID: %d\n", getpid(), getppid());
        createBinaryTree(depth, currentDepth + 1);
        exit(0);
    }

    // Create right child process
    rightChild = fork();
    if (rightChild == -1) {
        fprintf(stderr, "ERROR: Fork failed\n");
        exit(1);
    } else if (rightChild == 0) {
        printf("Right child: Process PID: %d, Parent PID: %d\n", getpid(), getppid());
        createBinaryTree(depth, currentDepth + 1);
        exit(0);
    }

    // Parent process waits for both children to complete
    wait(NULL);
    wait(NULL);
}
