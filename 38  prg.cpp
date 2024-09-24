#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATRIX_SIZE 3
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE], int n) {
    int det = 0;
    int submatrix[MATRIX_SIZE][MATRIX_SIZE];
    if (n == 2) {
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x)
                    continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (matrix[0][x] * determinant(submatrix, n - 1) * (x % 2 == 0 ? 1 : -1));
    }
    return det;
}
void adjugate(int matrix[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) {
    if (MATRIX_SIZE == 1) {
        adj[0][0] = 1;
        return;
    }
    int temp[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int subi = 0;
            for (int ii = 0; ii < MATRIX_SIZE; ii++) {
                if (ii == i)
                    continue;
                int subj = 0;
                for (int jj = 0; jj < MATRIX_SIZE; jj++) {
                    if (jj == j)
                        continue;
                    temp[subi][subj] = matrix[ii][jj];
                    subj++;
                }
                subi++;
            }
            adj[j][i] = (determinant(temp, MATRIX_SIZE - 1) * ((i + j) % 2 == 0 ? 1 : -1));
        }
    }
}
int inverseMatrix(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int det = determinant(key, MATRIX_SIZE);
    det = det % mod;
    if (det < 0)
        det += mod;
    int detInv = modInverse(det, mod);
    if (detInv == -1) {
        printf("Matrix is not invertible\n");
        return 0;
    }
    int adj[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(key, adj);
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = (adj[i][j] * detInv) % mod;
            if (inverse[i][j] < 0)
                inverse[i][j] += mod;
        }
    }
    return 1;
}
void multiplyMatrixVector(int matrix[MATRIX_SIZE][MATRIX_SIZE], int vector[MATRIX_SIZE], int result[MATRIX_SIZE], int mod) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        result[i] = result[i] % mod;
    }
}
void hillCipherEncrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char plaintext[], char ciphertext[], int mod) {
    int vector[MATRIX_SIZE];
    int result[MATRIX_SIZE];
    int length = strlen(plaintext);
    for (int i = 0; i < length; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            vector[j] = plaintext[i + j] - 'A';
        }
        multiplyMatrixVector(key, vector, result, mod);
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = (result[j] + 'A');
        }
    }
    ciphertext[length] = '\0';
}
void knownPlaintextAttack(int knownPlaintext[], int knownCiphertext[], int recoveredKey[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int inversePlaintextMatrix[MATRIX_SIZE][MATRIX_SIZE];
    if (!inverseMatrix(knownPlaintext, inversePlaintextMatrix, mod)) {
        printf("Failed to recover the key. Plaintext matrix is not invertible.\n");
        return;
    }   
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            recoveredKey[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                recoveredKey[i][j] += knownCiphertext[i * MATRIX_SIZE + k] * inversePlaintextMatrix[k][j];
            }
            recoveredKey[i][j] = recoveredKey[i][j] % mod;
            if (recoveredKey[i][j] < 0) {
                recoveredKey[i][j] += mod;
            }
        }
    }
}
int main() {
    int mod = 26; 
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };
    char plaintext[] = "ACT";
    char ciphertext[100];
    printf("Plaintext: %s\n", plaintext);
    hillCipherEncrypt(key, plaintext, ciphertext, mod);
    printf("Ciphertext: %s\n", ciphertext);
    int knownPlaintext[MATRIX_SIZE][MATRIX_SIZE] = {
        {0, 2, 19},
        {0, 2, 19},
        {0, 2, 19}
    };
    int knownCiphertext[MATRIX_SIZE][MATRIX_SIZE] = {
        {12, 0, 7},
        {12, 0, 7},
        {12, 0, 7}
    };
    int recoveredKey[MATRIX_SIZE][MATRIX_SIZE];
    knownPlaintextAttack((int *)knownPlaintext, (int *)knownCiphertext, recoveredKey, mod);
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", recoveredKey[i][j]);
        }
        printf("\n");
    }
    return 0;
}
