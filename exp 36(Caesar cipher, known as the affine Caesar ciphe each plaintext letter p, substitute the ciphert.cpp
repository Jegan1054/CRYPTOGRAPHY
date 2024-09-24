#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

char encrypt(char p, int a, int b) {
    if (p >= 'A' && p <= 'Z') {
        return (char)(((a * (p - 'A') + b) % 26) + 'A');
    }
    return p;
}

char decrypt(char c, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse for a = %d. Decryption not possible.\n", a);
        exit(1);
    }
    if (c >= 'A' && c <= 'Z') {
        return (char)(((a_inv * ((c - 'A') - b + 26)) % 26) + 'A');
    }
    return c;
}

int main() {
    int a, b;
    char plaintext[100], ciphertext[100];

    printf("Enter values for a and b (0 < a < 26, b >= 0): ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1) {
        printf("Value of 'a' must be coprime to 26 for a one-to-one mapping.\n");
        return 1;
    }

    printf("Enter plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("Ciphertext: %s\n", ciphertext);

    char decryptedtext[100];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = decrypt(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0';

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

