#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16

void pad(unsigned char* input, int inputLen, unsigned char* output, int blockSize) {
    int paddingLen = blockSize - (inputLen % blockSize);
    memcpy(output, input, inputLen);
    for (int i = 0; i < paddingLen; i++) {
        output[inputLen + i] = (i == 0) ? 0x80 : 0x00;
    }
}

void dummy_encrypt(unsigned char* input, unsigned char* output, int length) {
    memcpy(output, input, length);
}

void encryptECB(unsigned char* plaintext, unsigned char* ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        dummy_encrypt(plaintext + i, ciphertext + i, BLOCK_SIZE);
    }
}

void encryptCBC(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* iv, int length) {
    unsigned char temp[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plaintext[i + j] ^ iv[j];
        }
        dummy_encrypt(temp, ciphertext + i, BLOCK_SIZE);
        memcpy(iv, ciphertext + i, BLOCK_SIZE);
    }
}

void encryptCFB(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* iv, int length) {
    unsigned char temp[BLOCK_SIZE];
    int numBlocks = length / BLOCK_SIZE;

    for (int i = 0; i < numBlocks; i++) {
        dummy_encrypt(iv, temp, BLOCK_SIZE);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i * BLOCK_SIZE + j] = plaintext[i * BLOCK_SIZE + j] ^ temp[j];
        }
        memcpy(iv, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = "simplekey12345";   // 15 characters plus null terminator fits in 16
    unsigned char iv[BLOCK_SIZE] = "initialvector12";   // 15 characters plus null terminator fits in 16
    unsigned char plaintext[] = "This is a test message. It will be padded.";
    unsigned char paddedText[64];
    unsigned char ciphertext[64];
    int plaintextLen = strlen((char*)plaintext);

    pad(plaintext, plaintextLen, paddedText, BLOCK_SIZE);

    printf("ECB Mode Encryption:\n");
    encryptECB(paddedText, ciphertext, sizeof(paddedText));
    for (int i = 0; i < sizeof(paddedText); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    printf("CBC Mode Encryption:\n");
    memcpy(iv, "initialvector12", BLOCK_SIZE);
    encryptCBC(paddedText, ciphertext, iv, sizeof(paddedText));
    for (int i = 0; i < sizeof(paddedText); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    printf("CFB Mode Encryption:\n");
    memcpy(iv, "initialvector12", BLOCK_SIZE);
    encryptCFB(paddedText, ciphertext, iv, sizeof(paddedText));
    for (int i = 0; i < sizeof(paddedText); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

