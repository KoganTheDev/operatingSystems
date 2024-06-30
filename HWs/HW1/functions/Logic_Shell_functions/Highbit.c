/*
TODO:
Gets one parameter  (int)
returns: how many bits are 1 in the given number.

** int contains 32-bits
*/

#include <stdio.h>

int main(int number) {
    int count = 0;

    while (number) {
        count += number & 1; // Check if the current lsb is 1 or 0. 
        number >>= 1; // Consume the lsb.
    }

    return count;
}