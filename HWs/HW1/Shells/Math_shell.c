//TODO: insert code with documentation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void main(int argc, char* argv){

    if (argc != 1){
        printf("To run the \"Math_shell\" you need to give one argument which is \"Math\".\n");
        exit(1);
    }

    char* arguments[3];
    //! 4 arguments because of solve a b c :) :`) ok???!!!!!

    while (1){
        printf("MathShell>");
        scanf("%s %s %s", arguments[0], arguments[1], arguments[2]);

        //! complete later!!!!!!!!!!!!
        
        if ((strcmp(argument[0], "Sqrt")) == 0){
            exec(sqrt)
        }



    }
}