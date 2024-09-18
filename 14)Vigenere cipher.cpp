#include <stdio.h>
#include <string.h>
#define MAX_LEN 100
void encrypt(char *plaintext, int *key, int key_length, char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[index % key_length];
            ciphertext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            index++;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[len] = '\0';
}
void derive_key(char *ciphertext, char *plaintext, int *key, int key_length) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z' && plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            key[i % key_length] = (ciphertext[i] - plaintext[i] + 26) % 26; // Ensure positive values
        }
    }
}
int main() {
    char plaintext[] = "SENDMOREMONEY"; 
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; 
    char ciphertext[MAX_LEN];
    encrypt(plaintext, key, sizeof(key) / sizeof(key[0]), ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    char desired_plaintext[] = "CASHNOTNEEDED";
    int derived_key[13]; 
    derive_key(ciphertext, desired_plaintext, derived_key, sizeof(derived_key) / sizeof(derived_key[0]));
    printf("Derived Key Stream: ");
    for (int i = 0; i < sizeof(derived_key) / sizeof(derived_key[0]); i++) {
        printf("%d ", derived_key[i]);
    }
    printf("\n");
    return 0;
}
