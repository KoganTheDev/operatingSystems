/*
TODO:
-> Gets one parameter
-> returns the Hexadecimal value of the given decimal number.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    int number = atoi(argv[1]);

    printf("%X", number); // Prints in hexa format.

    return 0; // When the function succeeds.
}