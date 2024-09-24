#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK_SIZE 8 
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    return plaintext ^ key;
}
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    return ciphertext ^ key;
}
void pad_block(uint8_t *block, size_t size) {
    block[size] = 0x80; 
    for (size_t i = size + 1; i < BLOCK_SIZE; i++) {
        block[i] = 0x00; 
    }
}
void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t num_blocks, uint64_t key) {
    for (size_t i = 0; i < num_blocks; i++) {
        uint64_t block = *((uint64_t *) &plaintext[i * BLOCK_SIZE]);
        uint64_t encrypted_block = des_encrypt(block, key);
        *((uint64_t *) &ciphertext[i * BLOCK_SIZE]) = encrypted_block;
    }
}
void ecb_decrypt(uint8_t *ciphertext, uint8_t *plaintext, size_t num_blocks, uint64_t key) {
    for (size_t i = 0; i < num_blocks; i++) {
        uint64_t block = *((uint64_t *) &ciphertext[i * BLOCK_SIZE]);
        uint64_t decrypted_block = des_decrypt(block, key);
        *((uint64_t *) &plaintext[i * BLOCK_SIZE]) = decrypted_block;
    }
}
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t num_blocks, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (size_t i = 0; i < num_blocks; i++) {
        uint64_t block = *((uint64_t *) &plaintext[i * BLOCK_SIZE]);
        uint64_t xor_block = block ^ prev_block;
        uint64_t encrypted_block = des_encrypt(xor_block, key);
        *((uint64_t *) &ciphertext[i * BLOCK_SIZE]) = encrypted_block;
        prev_block = encrypted_block;
    }
}
void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, size_t num_blocks, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (size_t i = 0; i < num_blocks; i++) {
        uint64_t block = *((uint64_t *) &ciphertext[i * BLOCK_SIZE]);
        uint64_t decrypted_block = des_decrypt(block, key);
        decrypted_block ^= prev_block;
        *((uint64_t *) &plaintext[i * BLOCK_SIZE]) = decrypted_block;
        prev_block = block;
    }
}
void cfb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t num_segments, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (size_t i = 0; i < num_segments; i++) {
        uint64_t encrypted_block = des_encrypt(prev_block, key);
        uint8_t plaintext_segment = plaintext[i];
        uint8_t ciphertext_segment = ((uint8_t *) &encrypted_block)[0] ^ plaintext_segment;
        ciphertext[i] = ciphertext_segment;
        prev_block = (prev_block << 8) | ciphertext_segment;
    }
}
void cfb_decrypt(uint8_t *ciphertext, uint8_t *plaintext, size_t num_segments, uint64_t key, uint64_t iv) {
    uint64_t prev_block = iv;
    for (size_t i = 0; i < num_segments; i++) {
        uint64_t encrypted_block = des_encrypt(prev_block, key);
        uint8_t ciphertext_segment = ciphertext[i];
        uint8_t plaintext_segment = ((uint8_t *) &encrypted_block)[0] ^ ciphertext_segment;
        plaintext[i] = plaintext_segment;
        prev_block = (prev_block << 8) | ciphertext_segment;
    }
}
int main() {
    uint8_t plaintext[] = "HelloWorld123456"; 
    uint8_t ciphertext[16];
    uint8_t decryptedtext[16];
    size_t num_blocks = 2;
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t iv = 0x0123456789ABCDEF;
    pad_block(plaintext + BLOCK_SIZE, 8);  
    printf("ECB Mode:\n");
    ecb_encrypt(plaintext, ciphertext, num_blocks, key);
    ecb_decrypt(ciphertext, decryptedtext, num_blocks, key);
    printf("Decrypted ECB: %s\n", decryptedtext);
    printf("\nCBC Mode:\n");
    cbc_encrypt(plaintext, ciphertext, num_blocks, key, iv);
    cbc_decrypt(ciphertext, decryptedtext, num_blocks, key, iv);
    printf("Decrypted CBC: %s\n", decryptedtext);
    printf("\nCFB Mode:\n");
    cfb_encrypt(plaintext, ciphertext, num_blocks * BLOCK_SIZE, key, iv);
    cfb_decrypt(ciphertext, decryptedtext, num_blocks * BLOCK_SIZE, key, iv);
    printf("Decrypted CFB: %s\n", decryptedtext);

    return 0;
}
