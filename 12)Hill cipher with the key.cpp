#include <stdio.h>
#include <string.h>
#define SIZE 2
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
int determinant(int key[SIZE][SIZE]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
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
void decrypt(char *ciphertext, int key[SIZE][SIZE], char *plaintext) {
    int det = determinant(key);
    int det_inv = mod_inverse(det, 26);
    int inv_key[SIZE][SIZE];
    inv_key[0][0] = (key[1][1] * det_inv) % 26;
    inv_key[0][1] = (-key[0][1] * det_inv) % 26;
    inv_key[1][0] = (-key[1][0] * det_inv) % 26;
    inv_key[1][1] = (key[0][0] * det_inv) % 26;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv_key[i][j] = (inv_key[i][j] + 26) % 26; 
        }
    }
    int len = strlen(ciphertext);
    int index = 0;
    for (int i = 0; i < len; i += SIZE) {
        int vector[SIZE];
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                vector[j] = ciphertext[i + j] - 'A'; 
            }
        }
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += inv_key[j][k] * vector[k];
            }
            plaintext[index++] = (sum % 26 + 26) % 26 + 'A';
        }
    }
    plaintext[index] = '\0';
}
int main() {
    int key[SIZE][SIZE] = { {9, 4}, {5, 7} };
    char plaintext[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLK";
    char ciphertext[512];
    char decryptedtext[512];
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted Plaintext: %s\n", decryptedtext);
    return 0;
}
