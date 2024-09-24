#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define IV 0x0123456789ABCDEF
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    return plaintext ^ key; 
}
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    return ciphertext ^ key; 
}
uint64_t triple_des_encrypt(uint64_t plaintext, uint64_t key1, uint64_t key2, uint64_t key3) {
    uint64_t block = des_encrypt(plaintext, key1);
    block = des_decrypt(block, key2);
    block = des_encrypt(block, key3);
    return block;
}
uint64_t triple_des_decrypt(uint64_t ciphertext, uint64_t key1, uint64_t key2, uint64_t key3) {
    uint64_t block = des_decrypt(ciphertext, key3);
    block = des_encrypt(block, key2);
    block = des_decrypt(block, key1);
    return block;
}
void cbc_encrypt(uint64_t *plaintext, uint64_t *ciphertext, uint64_t num_blocks, uint64_t key1, uint64_t key2, uint64_t key3, uint64_t iv) {
    uint64_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint64_t xor_block = plaintext[i] ^ prev_block;
        ciphertext[i] = triple_des_encrypt(xor_block, key1, key2, key3);
        prev_block = ciphertext[i];
    }
}
void cbc_decrypt(uint64_t *ciphertext, uint64_t *plaintext, uint64_t num_blocks, uint64_t key1, uint64_t key2, uint64_t key3, uint64_t iv) {
    uint64_t prev_block = iv;
    for (int i = 0; i < num_blocks; i++) {
        uint64_t decrypted_block = triple_des_decrypt(ciphertext[i], key1, key2, key3);
        plaintext[i] = decrypted_block ^ prev_block;
        prev_block = ciphertext[i];
    }
}

int main() {
    uint64_t plaintext[] = {0x0123456789ABCDEF, 0x23456789ABCDEF01};
    uint64_t ciphertext[2];
    uint64_t decryptedtext[2];
    uint64_t num_blocks = 2;
    uint64_t key1 = 0x133457799BBCDFF1;
    uint64_t key2 = 0x1F1F1F1F0E0E0E0E;
    uint64_t key3 = 0x0A0A0A0A4E4E4E4E;
    uint64_t iv = IV;
    cbc_encrypt(plaintext, ciphertext, num_blocks, key1, key2, key3, iv);
    printf("Ciphertext:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", ciphertext[i]);
    }
    cbc_decrypt(ciphertext, decryptedtext, num_blocks, key1, key2, key3, iv);
    printf("Decrypted text:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%016lx\n", decryptedtext[i]);
    }
    return 0;
}
