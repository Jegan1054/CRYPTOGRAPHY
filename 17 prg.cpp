#include <stdio.h>
#include <stdint.h>
uint64_t permute(uint64_t input, const int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}
uint32_t f(uint32_t r, uint64_t k) {
    static const int E[] = {
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    };
    static const int S_BOX[8][4][16] = {
        {
            {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
            { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
            { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
            {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
        },
    };
    static const int P[] = {
        16,  7, 20, 21, 29, 12, 28, 17,
         1, 15, 23, 26,  5, 18, 31, 10,
         2,  8, 24, 14, 32, 27,  3,  9,
        19, 13, 30,  6, 22, 11,  4, 25
    };
    uint64_t expanded_r = permute(r, E, 48);
    uint64_t xor_result = expanded_r ^ k;
    uint32_t sbox_result = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((xor_result >> (42 - 6 * i)) & 0x20) | ((xor_result >> (42 - 6 * i)) & 1);
        int col = (xor_result >> (43 - 6 * i)) & 0x1E;
        sbox_result <<= 4;
        sbox_result |= S_BOX[i][row][col];
    }   
    return permute(sbox_result, P, 32);
}
void generate_keys(uint64_t key, uint64_t keys[16]) {
    static const int PC1[] = {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };
    static const int PC2[] = {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };
    static const int shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    uint64_t permuted_key = permute(key, PC1, 56);
    uint32_t left = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t right = permuted_key & 0xFFFFFFF;   
    for (int i = 0; i < 16; i++) {
        left = ((left << shifts[i]) | (left >> (28 - shifts[i]))) & 0xFFFFFFF;
        right = ((right << shifts[i]) | (right >> (28 - shifts[i]))) & 0xFFFFFFF;
        uint64_t combined = ((uint64_t)left << 28) | right;
        keys[i] = permute(combined, PC2, 48);
    }
}
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    static const int IP[] = {
        58, 50, 42, 34, 26, 18, 10,  2,
        60, 52, 44, 36, 28, 20, 12,  4,
        62, 54, 46, 38, 30, 22, 14,  6,
        64, 56, 48, 40, 32, 24, 16,  8,
        57, 49, 41, 33, 25, 17,  9,  1,
        59, 51, 43, 35, 27, 19, 11,  3,
        61, 53, 45, 37, 29, 21, 13,  5,
        63, 55, 47, 39, 31, 23, 15,  7
    };
    static const int IP_INV[] = {
        40,  8, 48, 16, 56, 24, 64, 32,
        39,  7, 47, 15, 55, 23, 63, 31,
        38,  6, 46, 14, 54, 22, 62, 30,
        37,  5, 45, 13, 53, 21, 61, 29,
        36,  4, 44, 12, 52, 20, 60, 28,
        35,  3, 43, 11, 51, 19, 59, 27,
        34,  2, 42, 10, 50, 18, 58, 26,
        33,  1, 41,  9, 49, 17, 57, 25
    };
    uint64_t permuted_text = permute(ciphertext, IP, 64);
    uint32_t left = (permuted_text >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_text & 0xFFFFFFFF;
    uint64_t keys[16];
    generate_keys(key, keys);
    for (int i = 15; i >= 0; i--) {
        uint32_t new_right = left ^ f(right, keys[i]);
        left = right;
        right = new_right;
    }
    uint64_t pre_output = ((uint64_t)right << 32) | left;
    return permute(pre_output, IP_INV, 64);
}
int main() {
    uint64_t ciphertext = 0x85E813540F0AB405;
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t plaintext = des_decrypt(ciphertext, key);   
    printf("Decrypted plaintext: %016lx\n", plaintext);
    return 0;
}
