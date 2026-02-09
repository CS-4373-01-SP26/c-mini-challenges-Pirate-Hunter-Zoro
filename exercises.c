#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

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
        C = (2 * C * I) / (C + I);
        I = sqrt(C * I);
        n *= 2;
    }
    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print approximate values
    printf("n: %d\n", n);
    printf("C: %f\n", C);
    printf("I: %f\n", I);
    printf("\n");

    printf("Elapsed %f seconds...\n\n", time);
}

void exercise_3() {
    FILE* fp = fopen("mv.txt", "r");
    if (fp == NULL) {
        printf("ERROR reading file mv.txt...\n");
    } else {
        int rows;
        int cols;
        // First line in file contains rows and columns
        fscanf(fp, "%d %d", &rows, &cols);
        // Now we can allocate the matrix
        double* matrix = malloc(rows * cols * sizeof(double));
        // Vector length must be the number of columns
        double* vector = malloc(cols * sizeof(double));
        // Resulting product will be of length rows
        double* result = malloc(rows * sizeof(double));

        // Read in the actual matrix
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                // Ignore white space
                fscanf(fp, "%lf", &matrix[i * cols + j]);
            }
        }

        // Read in the vector length and ensure it is cols
        int vector_length;
        fscanf(fp, "%d", &vector_length);
        if (vector_length != cols) {
            printf("ERROR - invalid dimensions given with matrix of %d columns and vector of length %d", cols, vector_length);
            // Prevent memory leak :-)
            free(matrix);
            free(vector);
            free(result);
            fclose(fp);
            return;
        }

        // Read in the vector
        for (int i=0; i<vector_length; i++) {
            fscanf(fp, "%lf", &vector[i]);
        }

        // Perform multiplication
        clock_t start = clock();
        for (int r=0; r<rows; r++) {
            int dot_prod = 0;
            for (int c=0; c<cols; c++) {
                dot_prod += matrix[r*cols + c] * vector[c];
            }
            result[r] = dot_prod;
        }
        clock_t end = clock();
        double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Print resulting vector
        printf("Resulting Product:\n");
        for (int i=0; i<rows; i++) {
            printf("%f ", result[i]);
        }
        printf("\nTime Elapsed: %f seconds\n\n", elapsed_time);
 
        // Prevent memory leak :-)
        free(vector);
        free(matrix);
        free(result);
        fclose(fp);
    }
}

void exercise_4() {
    // TODO - implement this function
}

int main(int argc, char** argv) {
    exercise_1();
    exercise_2();
    exercise_3();
    exercise_4();
    
    return 0;
}