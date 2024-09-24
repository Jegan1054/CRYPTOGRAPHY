#include <stdio.h>
#include <stdint.h>
#define LEFT_SHIFT_1(x) (((x) << 1) | ((x) >> (28 - 1)))
int S_BOX[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
};
int permutation[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};
int expansion[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};
uint64_t plaintext = 0x123456ABCD132536;
uint64_t key = 0xAABB09182736CCDD;
uint32_t permute(uint32_t input, int* table, int n) {
    uint32_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (32 - table[i])) & 0x01;
    }
    return output;
}
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    uint32_t left = (plaintext >> 32) & 0xFFFFFFFF;
    uint32_t right = plaintext & 0xFFFFFFFF;

    for (int round = 0; round < 16; round++) {
        uint32_t expanded_right = permute(right, expansion, 48);  
        uint32_t subkey = key ^ expanded_right;                   
        uint32_t substituted = 0;                                
        for (int i = 0; i < 8; i++) {
            int row = ((subkey >> (6 * (7 - i))) & 0x20) | ((subkey >> (6 * (7 - i))) & 0x01);
            int col = (subkey >> (6 * (7 - i) + 1)) & 0x0F;
            substituted <<= 4;
            substituted |= S_BOX[i][row][col];
        }
        uint32_t permuted_substitution = permute(substituted, permutation, 32); 
        uint32_t new_right = left ^ permuted_substitution;
        left = right;
        right = new_right;
    }
    uint64_t ciphertext = ((uint64_t)right << 32) | left;
    return ciphertext;
}

int main() {
    printf("Plaintext: %016lx\n", plaintext);
    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: %016lx\n", ciphertext);

    return 0;
}

