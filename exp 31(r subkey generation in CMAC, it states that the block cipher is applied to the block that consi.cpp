#include <stdio.h>
#include <stdint.h>
#define BLOCK_SIZE 128 
uint8_t K0[16] = {0}; 
uint8_t K1[16];
uint8_t K2[16];
void left_shift(uint8_t *input, uint8_t *output) {
    uint8_t carry = 0;
    for (int i = 0; i < 16; i++) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) >> 7; 
    }
    if (carry) {
        uint8_t constant = (BLOCK_SIZE == 128) ? 0x87 : 0x1B;
        output[15] ^= constant; 
    }
}
void generate_subkeys() {
    left_shift(K0, K1);
    left_shift(K1, K2);
}

void print_key(const uint8_t *key) {
    for (int i = 0; i < 16; i++) {
        printf("%02X", key[i]);
    }
    printf("\n");
}

int main() {
    printf("K1: ");
    generate_subkeys();
    print_key(K1);
    printf("K2: ");
    print_key(K2);
    return 0;
}

