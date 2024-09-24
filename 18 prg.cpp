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
void generate_keys(uint64_t key, uint64_t keys[16]) {
    static const int PC1_LEFT[] = {
        57, 49, 41, 33, 25, 17, 9, 
         1, 58, 50, 42, 34, 26, 18, 
        10, 2, 59, 51, 43, 35, 27, 
        19, 11, 3, 60, 52, 44, 36
    };   
    static const int PC1_RIGHT[] = {
        63, 55, 47, 39, 31, 23, 15, 
         7, 62, 54, 46, 38, 30, 22, 
        14, 6, 61, 53, 45, 37, 29, 
        21, 13, 5, 28, 20, 12, 4
    };
    static const int PC2[] = {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48
    };
    static const int shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    uint64_t left_half = permute(key, PC1_LEFT, 28);
    uint64_t right_half = permute(key, PC1_RIGHT, 28);
    for (int i = 0; i < 16; i++) {
        left_half = ((left_half << shifts[i]) | (left_half >> (28 - shifts[i]))) & 0xFFFFFFF;
        right_half = ((right_half << shifts[i]) | (right_half >> (28 - shifts[i]))) & 0xFFFFFFF;
        uint64_t combined = ((uint64_t)left_half << 28) | right_half;
        keys[i] = permute(combined, PC2, 48);
    }
}
int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t keys[16];
    generate_keys(key, keys);
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: %012lx\n", i + 1, keys[i]);
    }
    return 0;
}