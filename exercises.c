#include <stdio.h>
#include <math.h>
#include <time.h>

void exercise_1() {
    // Read and print name
    char name[100];
    printf("Enter a name:\n");
    // NOTE - do not enter in the address &name; name is already an address
    scanf("%s", name);

    printf("Hello, %s!\n\n", name);
}

void exercise_2() {
    // Approximations of pi
    int n=4;
    double C=4.0; // Circumscribed semi perimeter
    double I=2*sqrt(2); // Inscribed semi perimeter

    clock_t start = clock();
    while (n < 100) {
        printf("n: %d\n", n);
        printf("C: %f\n", C);
        printf("I: %f\n", I);
        printf("\n");
        C = (2 * C * I) / (C + I);
        I = sqrt(C * I);
        n *= 2;
    }
    // One final print for last values
    printf("n: %d\n", n);
    printf("C: %f\n", C);
    printf("I: %f\n", I);
    printf("\n");

    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed %f seconds...\n\n", time);
}

void exercise_3() {
    // TODO
}

int main(int argc, char** argv) {
    exercise_1();
    exercise_2();
    exercise_3();
    
    return 0;
}