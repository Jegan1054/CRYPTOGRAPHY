#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    return plaintext ^ key;
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    return ciphertext ^ key;
}

void ecb_encrypt(uint64_t *plaintext, uint64_t *ciphertext, uint64_t num_blocks, uint64_t key) {
    for (int i = 0; i < num_blocks; i++) {
        ciphertext[i] = des_encrypt(plaintext[i], key);
    }
}

void ecb_decrypt(uint64_t *ciphertext, uint64_t *plaintext, uint64_t num_blocks, uint64_t key) {
    for (int i = 0; i < num_blocks; i++) {
        plaintext[i] = des_decrypt(ciphertext[i], key);
    }
}

void cbc_encrypt(uint64_t *plaintext, uint64_t *ciphertext, uint64_t num_blocks, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint64_t xor_block = plaintext[i] ^ prev_block;
        ciphertext[i] = des_encrypt(xor_block, key);
        prev_block = ciphertext[i];
    }
}

void cbc_decrypt(uint64_t *ciphertext, uint64_t *plaintext, uint64_t num_blocks, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint64_t decrypted_block = des_decrypt(ciphertext[i], key);
        plaintext[i] = decrypted_block ^ prev_block;
        prev_block = ciphertext[i];
    }
}

int main() {
    uint64_t plaintext[] = {0x0123456789ABCDEF, 0x23456789ABCDEF01};
    uint64_t ciphertext[2];
    uint64_t decryptedtext[2];
    uint64_t num_blocks = 2;
    
    uint64_t key = 0x133457799BBCDFF1;
    
    printf("ECB Mode:\n");
    ecb_encrypt(plaintext, ciphertext, num_blocks, key);
    printf("Ciphertext:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", ciphertext[i]);
    }
    
    ecb_decrypt(ciphertext, decryptedtext, num_blocks, key);
    printf("Decrypted text:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", decryptedtext[i]);
    }
    
    uint64_t iv = 0x0123456789ABCDEF;
    printf("\nCBC Mode:\n");
    cbc_encrypt(plaintext, ciphertext, num_blocks, key, iv);
    printf("Ciphertext:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", ciphertext[i]);
    }
    
    cbc_decrypt(ciphertext, decryptedtext, num_blocks, key, iv);
    printf("Decrypted text:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", decryptedtext[i]);
    }
    
    return 0;
}
