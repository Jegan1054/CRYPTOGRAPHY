#include <stdio.h>
#include <string.h>

void CBC_MAC(unsigned char *key, unsigned char *message, unsigned char *mac) {
}

void xor_blocks(unsigned char *out, unsigned char *a, unsigned char *b) {
    for (int i = 0; i < 16; i++) {  
        out[i] = a[i] ^ b[i];
    }
}

int main() {
    unsigned char key[16];          
    unsigned char X[16];            
    unsigned char mac[16];          
    unsigned char X_xor_T[16];      
    unsigned char two_block_message[32]; 
    printf("Key: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", key[i]);
    }
    printf("\nMessage X: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", X[i]);
    }
    printf("\n");
    CBC_MAC(key, X, mac);
    printf("CBC-MAC T: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");

    xor_blocks(X_xor_T, X, mac);
    printf("X ? T: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", X_xor_T[i]);
    }
    printf("\n");

    memcpy(two_block_message, X, 16);
    memcpy(two_block_message + 16, X_xor_T, 16);

    CBC_MAC(key, two_block_message, mac);
    printf("CBC-MAC for X || (X ? T): ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");
    return 0;
}

