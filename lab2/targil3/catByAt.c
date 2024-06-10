#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    char* mainString = argv[1];
    char* slicedElement;
    int i;

    if (argc == 1){ // Meaning only the function call was inserted as input.
        printf("The function needs more arguments to start running.");
        exit(1);
    }

    // Changes all the lower case letters to upper case.
    for (i=0;i<strlen(mainString);i++){
        if (mainString[i] >= 'a' && mainString[i] <= 'z'){
            mainString[i] -= 32;
        }
    }

    slicedElement = strtok(mainString,"_");
    while(slicedElement != NULL){
        printf("%s\n", (slicedElement));
        slicedElement = strtok(NULL,"_");
    }
    
    return 0;
}