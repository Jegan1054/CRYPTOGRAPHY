#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int e, int phi) {
    int t = 0, newT = 1;
    int r = phi, newR = e;
    
    while (newR != 0) {
        int quotient = r / newR;
        int temp = newT;
        newT = t - quotient * newT;
        t = temp;
        
        temp = newR;
        newR = r - quotient * newR;
        r = temp;
    }
    
    if (r > 1) return -1;
    if (t < 0) t += phi;
    
    return t;
}

int modPow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int encrypt(int message, int e, int n) {
    return modPow(message, e, n);
}

int decrypt(int ciphertext, int d, int n) {
    return modPow(ciphertext, d, n);
}

int main() {
    int p = 61;
    int q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 17;
    int d = modInverse(e, phi);
    
    if (d == -1) {
        printf("Modular inverse could not be calculated.\n");
        return 1;
    }
    
    int message = 4;
    
    int ciphertext = encrypt(message, e, n);
    printf("Encrypted message: %d\n", ciphertext);
    
    int decryptedMessage = decrypt(ciphertext, d, n);
    printf("Decrypted message: %d\n", decryptedMessage);
    
    return 0;
}

