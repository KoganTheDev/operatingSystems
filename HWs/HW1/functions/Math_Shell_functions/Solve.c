/*
TODO: Not sure complete later

*/

double main(double a, double b, double c){
    int pid;
    double firstSolution, secondSolution;
    double numInSqaureRoot = b * b - 4 * a * c;


    if (numInSqaureRoot < 0){
        printf("No Sol!\n");
    }
    else if (numInSqaureRoot == 0){
        return ((-b) / (2* a)); // Special case when there`s only one solution.
    }
    else{
        firstSolution = ((-b) + Sqrt(numInSqaureRoot)) / (2 * a);
        secondSolution = ((-b) - Sqrt(numInSqaureRoot)) / (2 * a);

        //! Problems can and will occur from here onwards.probably need to cahnge
        pid = fork();
        // TODO: check can cause problems
        if (pid != 0){
            printf("%.0lf\n", firstSolution);
            return firstSolution;
        }
        else{
            printf("%0.lf\n", secondSolution);
            return secondSolution;
        }
}