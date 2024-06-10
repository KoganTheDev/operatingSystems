#include <stdio.h>
#include <stdlib.h>

int main(int argc, int argv[]){
    int result = argv[0];
    int i,j;

    if (argc < 3){ // Meaning there`s less than 2 numbers given as arguments to compare with.
        printf("2 numbers do not exist.\n");
        exit(1);
    }

    for (i=0;i<argc;i++){
        for (j=i+1;j<argc;j++){
            if (argv[i] + argv[j] == result ){
                // TODO: coninute here and check the condition it might cause a out of bounds error.
            }
        }
    }


    return 0;
}