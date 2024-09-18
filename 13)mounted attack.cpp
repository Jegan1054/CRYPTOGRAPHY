#include <stdio.h>
#include <string.h>
#define SIZE 2
int determinant(int key[SIZE][SIZE]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void derive_key(int plaintext[SIZE][SIZE], int ciphertext[SIZE][SIZE], int key[SIZE][SIZE]) {
    int det = determinant(plaintext);
    int det_inv = mod_inverse(det, 26);
    key[0][0] = (det_inv * plaintext[1][1]) % 26;
    key[0][1] = (-det_inv * plaintext[0][1]) % 26;
    key[1][0] = (-det_inv * plaintext[1][0]) % 26;
    key[1][1] = (det_inv * plaintext[0][0]) % 26;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            key[i][j] = (key[i][j] + 26) % 26;
        }
    }
}
void encrypt(char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;
    for (int i = 0; i < len; i += SIZE) {
        int vector[SIZE];
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                vector[j] = plaintext[i + j] - 'A';
            }
        }
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += key[j][k] * vector[k];
            }
            ciphertext[index++] = (sum % 26) + 'A';
        }
    }
    ciphertext[index] = '\0'; 
}
int main() {
    char known_plaintext[] = "MEET";
    char known_ciphertext[] = "OQUR"; 

    int plaintext[SIZE][SIZE] = {
        { known_plaintext[0] - 'A', known_plaintext[1] - 'A' },
        { known_plaintext[2] - 'A', known_plaintext[3] - 'A' }
    };
    int ciphertext[SIZE][SIZE] = {
        { known_ciphertext[0] - 'A', known_ciphertext[1] - 'A' },
        { known_ciphertext[2] - 'A', known_ciphertext[3] - 'A' }
    };
    int key[SIZE][SIZE];
    derive_key(plaintext, ciphertext, key);
    printf("Derived Key Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);
    char test_plaintext[] = "MEET";
    char test_ciphertext[512];
    encrypt(test_plaintext, key, test_ciphertext);
    printf("Ciphertext from derived key: %s\n", test_ciphertext);
    return 0;
}
