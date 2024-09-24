#include <stdio.h>
#include <string.h>
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_inv[] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[] = {2, 4, 3, 1};
int S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
int S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
int permute(int bits, int* table, int n) {
    int permuted = 0;
    for (int i = 0; i < n; i++) {
        permuted <<= 1;
        permuted |= (bits >> (8 - table[i])) & 1;
    }
    return permuted;
}
int sbox(int bits, int sbox[4][4]) {
    int row = ((bits >> 3) & 2) | (bits & 1);
    int col = (bits >> 1) & 3;
    return sbox[row][col];
}
int f(int right, int sk) {
    int ep = permute(right, EP, 8);
    int xor_out = ep ^ sk;
    int left_sbox = sbox((xor_out >> 4) & 0xF, S0);
    int right_sbox = sbox(xor_out & 0xF, S1);
    int sbox_out = (left_sbox << 2) | right_sbox;
    return permute(sbox_out, P4, 4);
}
int sdes_encrypt(int plaintext, int sk1, int sk2) {
    int permuted = permute(plaintext, IP, 8);
    int left = permuted >> 4;
    int right = permuted & 0xF;
    int temp = f(right, sk1) ^ left;
    left = right;
    right = temp;
    temp = f(right, sk2) ^ left;
    left = right;
    right = temp;
    int combined = (right << 4) | left;
    return permute(combined, IP_inv, 8);
}
int sdes_decrypt(int ciphertext, int sk1, int sk2) {
    return sdes_encrypt(ciphertext, sk2, sk1);
}
void generate_subkeys(int key, int* sk1, int* sk2) {
    int permuted = permute(key, P10, 10);
    int left = (permuted >> 5) & 0x1F;
    int right = permuted & 0x1F;
    left = ((left << 1) | (left >> 4)) & 0x1F;
    right = ((right << 1) | (right >> 4)) & 0x1F;
    *sk1 = permute((left << 5) | right, P8, 8);
    left = ((left << 2) | (left >> 3)) & 0x1F;
    right = ((right << 2) | (right >> 3)) & 0x1F;
    *sk2 = permute((left << 5) | right, P8, 8);
}
void cbc_encrypt(int* plaintext_blocks, int* ciphertext_blocks, int num_blocks, int iv, int sk1, int sk2) {
    int previous = iv;
    for (int i = 0; i < num_blocks; i++) {
        int block = plaintext_blocks[i] ^ previous;
        ciphertext_blocks[i] = sdes_encrypt(block, sk1, sk2);
        previous = ciphertext_blocks[i];
    }
}
void cbc_decrypt(int* ciphertext_blocks, int* plaintext_blocks, int num_blocks, int iv, int sk1, int sk2) {
    int previous = iv;
    for (int i = 0; i < num_blocks; i++) {
        int block = sdes_decrypt(ciphertext_blocks[i], sk1, sk2);
        plaintext_blocks[i] = block ^ previous;
        previous = ciphertext_blocks[i];
    }
}
void print_binary(int value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf(" ");
}
int main() {
    int iv = 0b10101010;
    int plaintext_blocks[] = {0b00000001, 0b00100011};
    int num_blocks = 2;
    int key = 0b0111111101;
    int sk1, sk2;
    generate_subkeys(key, &sk1, &sk2);
    int ciphertext_blocks[num_blocks];
    printf("Encrypting...\n");
    cbc_encrypt(plaintext_blocks, ciphertext_blocks, num_blocks, iv, sk1, sk2);
    printf("Ciphertext: ");
    for (int i = 0; i < num_blocks; i++) {
        print_binary(ciphertext_blocks[i], 8);
    }
    printf("\n");
    int decrypted_blocks[num_blocks];
    printf("Decrypting...\n");
    cbc_decrypt(ciphertext_blocks, decrypted_blocks, num_blocks, iv, sk1, sk2);
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < num_blocks; i++) {
        print_binary(decrypted_blocks[i], 8);
    }
    printf("\n");
    return 0;
}
