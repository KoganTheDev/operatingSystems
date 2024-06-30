/*
TODO:
-> Gets one parameter
-> returns the binary value of the given decimal number.

*/

#define DIGITS_IN_INT 32

int main(int number){
    int base10 = DIGITS_IN_INT;
    int numberAsBinary = 0;

    // Convert to an integer that represents number in its binary format
    for (int i = DIGITS_IN_INT; i > 0; i--){
        if ((number % 2) == 1){
            numberAsBinary += 1 * base10;
        }

        number /= 2;
        base10 -= 1;
    }

    return numberAsBinary;
}