#include "helperFunctions.h"

// This function generates a pseudo random number between intLowerBound(inclusive) and intUppperbound(inclusive)
int randomNumberGenerator(int intLowerBound, int intUpperBound) {
    assert(intUpperBound > intLowerBound);
    int intRange = intUpperBound - intLowerBound + 1;
    return rand() % intRange + intLowerBound;
}
