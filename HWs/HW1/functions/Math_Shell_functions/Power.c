#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double main(int argc, char* argv[]){

    if (argc != 3){
        printf("The function \"Power\" needs 3 parameters.\n");
        exit(1);
    }

    double base = atoi(argv[1]);
    double power = atoi(argv[2]);
    double result = pow(base, power);

    printf("%.0lf\n", result);
    return 0; // Represents a successful run.
}