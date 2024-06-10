#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    char* mainString = strupr(argv[1]);
    char* slicedElement;

    if (argc == 1){ // Meaning only the function call was inserted as input.
        printf("The function needs more arguments to start running.");
        exit(1);
    }

    slicedElement = strtok(mainString,"_");
    while(slicedElement != NULL){
        printf("%s", slicedElement);
        slicedElement = strtok(NULL,"_");
    }

    free(mainString);
    return 0;
}