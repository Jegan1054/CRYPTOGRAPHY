#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void generateRandomKey(int key[], int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}

void encrypt(char plaintext[], char ciphertext[], int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i]) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

void printKey(int key[], int length) {
    printf("Key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
}

int main() {
    char plaintext[256], ciphertext[256];
    int key[256];
    
    srand(time(NULL));
    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }
    
    len = strlen(plaintext);
    generateRandomKey(key, len);
    encrypt(plaintext, ciphertext, key, len);
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printKey(key, len);
    
    return 0;
}

