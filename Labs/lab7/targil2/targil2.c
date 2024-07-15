#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @brief Thread function to calculate the sum of divisors of a given number.
 *
 * This function calculates the sum of proper divisors of a given number
 * and returns the result.
 *
 * @param p Pointer to the number whose divisors sum is to be calculated.
 * @return void* Pointer to the sum of divisors.
 */
void* f(void* p); // declaration

/**
 * @brief Main function to check if two numbers are amicable using threads.
 *
 * This function takes two integers as command-line arguments, creates two
 * threads to calculate the sum of their divisors, and checks if the numbers
 * are amicable.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 on successful execution, 1 on error.
 */
int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("ERROR; please enter 2 parameters\n");
        exit(1);
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);

    int *sum1, *sum2;
    pthread_t t1, t2;

    pthread_create(&t1, NULL, f, (void*)&M);
    pthread_create(&t2, NULL, f, (void*)&N);

    pthread_join(t1, (void**)&sum1);
    pthread_join(t2, (void**)&sum2);

    if (*sum1 == N && *sum2 == M) {
        printf("Amicable Numbers\n");
    } else {
        printf("Not Amicable Numbers\n");
    }

    free(sum1);
    free(sum2);

    return 0;
}

/**
 * @brief Thread function to calculate the sum of divisors of a given number.
 *
 * This function calculates the sum of proper divisors of a given number
 * and returns the result.
 *
 * @param p Pointer to the number whose divisors sum is to be calculated.
 * @return void* Pointer to the sum of divisors.
 */
void* f(void* p) {
    int* sum = (int*) malloc(sizeof(int));
    if (sum == NULL) {
        printf("Allocating memory for sum has failed.\n");
        exit(1);
    }

    *sum = 0;  // Initialize the sum value to 0
    int num = *((int*) p);
    int i = 1;

    while (i < num) {
        if (num % i == 0) {
            *sum += i;
        }
        i++;
    }

    return (void*) sum;
}
