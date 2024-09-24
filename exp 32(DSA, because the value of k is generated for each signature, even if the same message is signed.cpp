#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void rsa_sign(const char *message, char *signature) {
    sprintf(signature, "RSA_SIGNATURE_OF(%s)", message);
}

void dsa_sign(const char *message, char *signature) {
    int k = rand() % 100;
    sprintf(signature, "DSA_SIGNATURE_OF(%s)_k(%d)", message, k);
}

int main() {
    const char *message = "Hello, this is a test message.";
    char rsa_signature[256];
    char dsa_signature1[256];
    char dsa_signature2[256];

    srand(time(NULL));

    rsa_sign(message, rsa_signature);
    printf("RSA Signature: %s\n", rsa_signature);

    dsa_sign(message, dsa_signature1);
    dsa_sign(message, dsa_signature2);
    
    printf("DSA Signature 1: %s\n", dsa_signature1);
    printf("DSA Signature 2: %s\n", dsa_signature2);

    return 0;
}

