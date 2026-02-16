#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate a matrix
int** allocateMatrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
    }
    return mat;
}

// Function to free a matrix
void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

// Function to print a matrix
void printMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

// Traditional matrix multiplication
void traditionalMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

// Strassen utility functions
void add(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen matrix multiplication
void strassenMultiply(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);
    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    int** M1 = allocateMatrix(k);
    int** M2 = allocateMatrix(k);
    int** M3 = allocateMatrix(k);
    int** M4 = allocateMatrix(k);
    int** M5 = allocateMatrix(k);
    int** M6 = allocateMatrix(k);
    int** M7 = allocateMatrix(k);

    int** temp1 = allocateMatrix(k);
    int** temp2 = allocateMatrix(k);

    add(A11, A22, temp1, k);
    add(B11, B22, temp2, k);
    strassenMultiply(temp1, temp2, M1, k);

    add(A21, A22, temp1, k);
    strassenMultiply(temp1, B11, M2, k);

    subtract(B12, B22, temp2, k);
    strassenMultiply(A11, temp2, M3, k);

    subtract(B21, B11, temp2, k);
    strassenMultiply(A22, temp2, M4, k);

    add(A11, A12, temp1, k);
    strassenMultiply(temp1, B22, M5, k);

    subtract(A21, A11, temp1, k);
    add(B11, B12, temp2, k);
    strassenMultiply(temp1, temp2, M6, k);

    subtract(A12, A22, temp1, k);
    add(B21, B22, temp2, k);
    strassenMultiply(temp1, temp2, M7, k);

    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);

    add(M1, M4, temp1, k);
    subtract(temp1, M5, temp2, k);
    add(temp2, M7, C11, k);

    add(M3, M5, C12, k);
    add(M2, M4, C21, k);

    subtract(M1, M2, temp1, k);
    add(temp1, M3, temp2, k);
    add(temp2, M6, C22, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k); freeMatrix(A12, k);
    freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k);
    freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(M1, k); freeMatrix(M2, k);
    freeMatrix(M3, k); freeMatrix(M4, k);
    freeMatrix(M5, k); freeMatrix(M6, k);
    freeMatrix(M7, k);
    freeMatrix(temp1, k); freeMatrix(temp2, k);
    freeMatrix(C11, k); freeMatrix(C12, k);
    freeMatrix(C21, k); freeMatrix(C22, k);
}

int main() {
    int n;
    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C1 = allocateMatrix(n);
    int** C2 = allocateMatrix(n);

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    clock_t start, end;

    start = clock();
    traditionalMultiply(A, B, C1, n);
    end = clock();
    double timeTraditional = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    strassenMultiply(A, B, C2, n);
    end = clock();
    double timeStrassen = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nResult using Traditional Multiplication:\n");
    printMatrix(C1, n);

    printf("\nResult using Strassen Multiplication:\n");
    printMatrix(C2, n);

    printf("\nTime Taken (Traditional): %f seconds\n", timeTraditional);
    printf("Time Taken (Strassen): %f seconds\n", timeStrassen);

    freeMatrix(A, n); freeMatrix(B, n);
    freeMatrix(C1, n); freeMatrix(C2, n);

    return 0;
}
