#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void exercise_1() {
    // Read and print name
    char name[100];
    printf("Enter a name:\n");
    // NOTE - do not enter in the address &name; name is already an address
    scanf("%s", name);
    getchar();

    printf("Hello, %s!\n\n", name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void exercise_4(){
    // TODO - implement this function
    int ITERATIONS = 10000000;
    volatile double result; // Because otherwise the compiler is smart enough to realize we are not using the result and will skip the code
    
    // Time division
    clock_t start = clock();
    for (int i=0; i<ITERATIONS; i++) {
        result = i / 1.0001;
    }
    clock_t end = clock();
    double total_operation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Division Time for %d Operations: %f seconds\n", ITERATIONS, total_operation_time);

    // Time multiplication
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        result = i * 1.0001;
    }
    end = clock();
    total_operation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Multiplication Time for %d Operations: %f seconds\n", ITERATIONS, total_operation_time);

    // Time square root
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        result = sqrt(i);
    }
    end = clock();
    total_operation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Square Root Time for %d Operations: %f seconds\n", ITERATIONS, total_operation_time);

    // Time sine
    start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        result = sin(i);
    }
    end = clock();
    total_operation_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Division Time for %d Operations: %f seconds\n\n", ITERATIONS, total_operation_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void exercise_5() {
    int N = 128;
    volatile double v;
    clock_t start;
    clock_t end;
    double total_time;
    while (N < 1024) {
        // Static array
        double static_array[N][N];

        // Static array row major test
        start = clock();
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                v = static_array[i][j];
            }
        }
        end = clock();
        total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Static Array Size %d by %d Row Major Time: %f Seconds\n", N, N, total_time);

        // Static array column major test
        start = clock();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                v = static_array[j][i];
            }
        }
        end = clock();
        total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Static Array Size %d by %d Column Major Time: %f Seconds\n", N, N, total_time);

        // Dynamic Array
        double* dynamic_array = malloc(N*N*sizeof(double));

        // Dynamic array row major test
        start = clock();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                v = dynamic_array[i*N+j];
            }
        }
        end = clock();
        total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Dynamic Array Size %d by %d Row Major Time: %f Seconds\n", N, N, total_time);

        // Dynamic array column major test
        start = clock();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                v = dynamic_array[j * N + i];
            }
        }
        end = clock();
        total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Dynamic Array Size %d by %d Column Major Time: %f Seconds\n\n", N, N, total_time);

        free(dynamic_array);
        N *= 2;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Helper function for exercise 6
void helper_exercise_6(char* c) {
    // Find the end of the string
    char* start = c;
    char* end = start;
    while (*end != '\0' && *end != '\n') {
        end++; // Pointer arithmetic
    }
    // Go back one from the terminating character if the input was not empty
    if (end > start) {
        end--;
    }
    // Now we reverse the string
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Transformer "Wrapper" Function
void wrapper_exercise_6(char* s, void (*reverser_function_pointer)(char*)) {
    // Print original string
    printf("Original String: %s\n", s);
    reverser_function_pointer(s);
    printf("Reverse String: %s\n\n", s);
}

void exercise_6() {
    int max_length = 100;
    char* s = malloc(sizeof(char)*max_length);
    printf("Enter a string to be reversed:\n");
    if (fgets(s, max_length, stdin) != NULL)
    {
        wrapper_exercise_6(s, helper_exercise_6);
    }
    else
    {
        printf("Error reading input or EOF reached.\n");
    }

    free(s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    exercise_1();
    printf("\n=============================================================\n");
    exercise_2();
    printf("\n=============================================================\n");
    exercise_3();
    printf("\n=============================================================\n");
    exercise_4();
    printf("\n=============================================================\n");
    exercise_5();
    printf("\n=============================================================\n");
    exercise_6();

    return 0;
}