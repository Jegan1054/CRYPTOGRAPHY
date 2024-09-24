#include <stdio.h>
#include <stdlib.h>
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
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}

long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int p = 61, q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 17;
    
    int d = modInverse(e, phi);

    if (d == -1) {
        printf("Error in key generation\n");
        return 1;
    }

    printf("Public Key: {e: %d, n: %d}\n", e, n);
    printf("Private Key: {d: %d, n: %d}\n", d, n);

    int message = 89;
    long long encrypted = powerMod(message, e, n);
    printf("Encrypted message: %lld\n", encrypted);

    long long decrypted = powerMod(encrypted, d, n);
    printf("Decrypted message: %lld\n", decrypted);

    return 0;
}

