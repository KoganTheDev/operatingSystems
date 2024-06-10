#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int result = atoi(argv[1]); 
    int i,j, firstNumber, secondNumber;

    if (argc < 4){ // Meaning there are less than 2 numbers given as arguments to compare with.
        printf("2 numbers do not exist.\n");
        exit(1);
    }

    for (i=2;i<argc;i++){
        for (j=i+1;j<argc;j++){
            firstNumber = atoi(argv[i]);
            secondNumber = atoi(argv[j]);
            if (firstNumber + secondNumber == result ){
                printf("2 numbers exist: %d + %d = %d",firstNumber, secondNumber, result);
                return 0;
            }
        }
    }
    printf("2 numbers do not exist.\n");
    return 0;
}