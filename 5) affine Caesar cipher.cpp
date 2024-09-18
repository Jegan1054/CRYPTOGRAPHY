#include <stdio.h>
#include <stdbool.h>
bool areCoprime(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return (a == 1);
}
void encryptAffineCipher(char message[], int a, int b) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        char character = message[i];
        if (character >= 'a' && character <= 'z') {
            character = (a * (character - 'a') + b) % 26 + 'a';
        } else if (character >= 'A' && character <= 'Z') {
            character = (a * (character - 'A') + b) % 26 + 'A';
        }
        message[i] = character;
    }
}
void decryptAffineCipher(char message[], int a, int b) {
    int i;
    int a_inv = -1;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }
    if (a_inv == -1) {
        printf("No modular inverse for a = %d\n", a);
        return;
    }
    
    for (i = 0; message[i] != '\0'; i++) {
        char character = message[i];
        if (character >= 'a' && character <= 'z') {
            character = (a_inv * ((character - 'a') - b + 26)) % 26 + 'a';
        } else if (character >= 'A' && character <= 'Z') {
            character = (a_inv * ((character - 'A') - b + 26)) % 26 + 'A';
        }
        message[i] = character;
    }
}

int main() {
    char message[100];
    int a, b;
    
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    
    printf("Enter the key a: ");
    scanf("%d", &a);
    
    printf("Enter the key b: ");
    scanf("%d", &b);
    
    if (!areCoprime(a, 26)) {
        printf("The key a = %d is not valid. It must be coprime with 26.\n", a);
        return 1;
    }
    
    encryptAffineCipher(message, a, b);
    printf("Encrypted message: %s\n", message);
    
    decryptAffineCipher(message, a, b);
    printf("Decrypted message: %s\n", message);
    
    return 0;
}