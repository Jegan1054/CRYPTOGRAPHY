#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int textLength = strlen(plaintext);
    int keyLength = strlen(key);
    int i, j;
    for (i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]);
    }
    for (i = 0, j = 0; i < textLength; i++) {
        char currentChar = plaintext[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            int shift = key[j % keyLength] - 'A';
            ciphertext[i] = ((currentChar - base + shift) % 26) + base;           
            j++; 
        } else {
            ciphertext[i] = currentChar;
        }
    }
    ciphertext[i] = '\0'; 
}
void decrypt(char ciphertext[], char key[], char decryptedtext[]) {
    int textLength = strlen(ciphertext);
    int keyLength = strlen(key);
    int i, j;
    for (i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]);
    }
    for (i = 0, j = 0; i < textLength; i++) {
        char currentChar = ciphertext[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            int shift = key[j % keyLength] - 'A';
            decryptedtext[i] = ((currentChar - base - shift + 26) % 26) + base;
            j++; 
        } else {
            decryptedtext[i] = currentChar;
        }
    }
    decryptedtext[i] = '\0'; 
}
int main() {
    char plaintext[MAX], key[MAX], ciphertext[MAX], decryptedtext[MAX];
    printf("Enter the plaintext: ");
    fgets(plaintext, MAX, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = '\0'; 
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}

