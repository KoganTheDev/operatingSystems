/*
TODO:
-> Gets one parameter
-> returns the Hexadecimal value of the given decimal number.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("The function \"DectoHex\" must get 2 parameters.\n");
        exit(1);
    }

    int number = atoi(argv[1]);

    printf("%X", number); // Prints in hexa format.

    return ;
}